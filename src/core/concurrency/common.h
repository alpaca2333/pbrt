// Created by alpaca

#pragma once

#include <cstdio>


#define synchronized(lock) for (std::unique_lock<std::recursive_mutex> __lock_for__##lock(lock); \
                                __lock_for__##lock; __lock_for__##lock.unlock())
