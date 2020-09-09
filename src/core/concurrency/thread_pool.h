/**
 * 一个任意参数的线程池实现。
 *
 * @author  qwertysun
 * @date    01/19/2019
 */

#pragma once

#include <future>
#include <queue>
#include <vector>
#include <condition_variable>

#include "common.h"

class ThreadPool
{
public:
  typedef std::function<void()> Job;

  ThreadPool() = delete;

  explicit ThreadPool(uint32_t capacity);

  bool AddJob(const Job& job);

  /* 多少毫秒后触发这个 Job */
  bool OnTimeOut(const Job& job, time_t timeout);

  template <class Func, class... Args>
  bool AddJob(Func &&func, Args &&... args);

  /* 返回一个 future 指针。如果添加任务失败，返回 nullptr */
  template <class Func, class... Args>
  auto AddJobWithRet(Func &&func, Args &&... args)
  -> std::unique_ptr<std::future<decltype(func(args...))>>;

  virtual ~ThreadPool();

public:
  void SetJobQueueCapacity(uint32_t capacity) { job_queue_capacity_ = capacity; }
  uint32_t GetJobQueueCapacity() { return job_queue_capacity_; }

  // 获取当前正在运行的线程数量
  [[nodiscard]] uint32_t GetThreadCount() const { return thread_count_; }

  // 获取任务队列长度
  [[nodiscard]] size_t GetJobCount() const { return job_queue_.size(); }

  [[nodiscard]] uint32_t GetCapacity() const { return thread_capacity_; }

protected:
  uint32_t job_queue_capacity_ = 10000;

  uint32_t thread_capacity_ = 1000;

private:
  std::queue<Job> job_queue_;
  std::recursive_mutex mutex_for_job_queue_;

  std::vector<std::thread> threads_;
  std::atomic<bool> run_flag_;
  std::condition_variable cv_;

  std::atomic<uint32_t> thread_count_;
};

//-------------------implementations----------------

template <class Func, class... Args>
bool ThreadPool::AddJob(Func &&func, Args &&... args)
{
  return AddJobWithRet(std::forward<Func>(func), std::forward<Args>(args)...);
}

template <class Func, class... Args>
auto ThreadPool::AddJobWithRet(Func &&func, Args &&... args)
-> std::unique_ptr<std::future<decltype(func(args...))>>
{
  using ResType = decltype(func(args...));
  if (!run_flag_)
    return nullptr;
  synchronized(mutex_for_job_queue_)
  {
    if (job_queue_.size() >= job_queue_capacity_)
      return nullptr;
  }
  auto pJob = std::make_shared<std::packaged_task<ResType()>>(
      std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

  std::unique_ptr<std::future<ResType>> p_res(new std::future<ResType>(pJob->get_future()));

  synchronized(mutex_for_job_queue_)
  {
    if (job_queue_.size() >= job_queue_capacity_)
      return nullptr;
    job_queue_.push(
        [pJob]() -> void {
          (*pJob)();
        });
  }
  // 唤醒一个线程
  cv_.notify_one();
  return p_res;
}
