//
// Created by qwertysun on 19-1-19.
//

#include <iostream>

#include "thread_pool.h"

using namespace std;

ThreadPool::ThreadPool(uint32_t capacity) : run_flag_(true)
{
  threads_.reserve(capacity);
  thread_capacity_ = capacity;
  auto thread_job = [this]() -> void {
    while (run_flag_)
    {
      // 当 run_flag 为 true 且 job_queue 为空时等待。
      mutex mutex_tmp;
      unique_lock<mutex> lock(mutex_tmp);

      cv_.wait(lock, [=] { return !run_flag_ || !job_queue_.empty(); });
      ++thread_count_;

      Job job;
      bool has_job = false;
      synchronized(mutex_for_job_queue_)
      {
        if (job_queue_.empty())
          break;
        has_job = true;
        job = job_queue_.front();
        job_queue_.pop();
      }
      if (has_job)
      {
        job();
      }

      --thread_count_;
    }
  };

  thread_count_ = 0;
  for (unsigned i = 0; i < capacity; ++i)
  {
    threads_.emplace_back(thread_job);
  }
}

ThreadPool::~ThreadPool()
{
  run_flag_ = false;

  cout << "Waiting for all running threads. There should be "
       << GetThreadCount() << " thread(s) running." << endl;

  cv_.notify_all();

  for (auto &thread : threads_)
  {
    if (thread.joinable())
    {
      thread.join();
    }
  }
}

bool ThreadPool::AddJob(Job job)
{
  synchronized(mutex_for_job_queue_)
  {
    if (job_queue_.size() >= job_queue_capacity_)
      return false;
    job_queue_.push(job);
  }
  cv_.notify_one();
  return true;
}

bool ThreadPool::OnTimeOut(ThreadPool::Job job, time_t timeout)
{
  auto delayed_job = [=] {
    this_thread::sleep_for(chrono::milliseconds(timeout));
    job();
  };
  // 如果线程池已经满了，就新建线程去做这件事，保证准时性。
  if (GetThreadCount() >= GetCapacity())
  {
    thread(delayed_job).detach();
  }
  else
  {
    AddJob(delayed_job);
  }
  return true;
}
