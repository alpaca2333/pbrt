#pragma once

#include <cstdio>
#include <cstdlib>

#define DEBUG
#define nullable
#define notnull

// assert in debug mode
inline void __replacement_assert(const char *__condition)
{
#ifdef DEBUG
  std::printf("Assertion '%s' failed.\n", __condition);
  exit(1);
#endif
}

#define unlikely(x) __builtin_expect(!!(x), 0)
#define likely(x) __builtin_expect(!!(x), 1)