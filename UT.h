/* Copyright (C) 2020 David Sloan
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __UT_H
#define __UT_H

#include <functional>
#include <iostream>

#define UT(func)                  \
void func();                      \
ut ut_var_##func(func, #func);  \
void func()

#define UT_ASSERT(value) ut_assert((value), #value, __FILE__, __LINE__)

#define UT_EXCEPT(type, code) ({                                    \
  bool _has_err_ = false;                                           \
  try {                                                             \
    code;                                                           \
  } catch (const type & err) {                                      \
    _has_err_ = true;                                               \
  }                                                                 \
  ut_assert(_has_err_, "Excpected Exception", __FILE__, __LINE__);  \
})

class ut {
  public:
    ut(std::function<void()> fn, const char *name);
    static void runAll();
  private:
    static ut *reg_;

    const char *name_;
    std::function<void()> fn_;
    ut *next_;
};

static inline void ut_assert(bool val, const char *expression, const char* file, int line)
{
  if (!val) {
    std::cout << "Failed UT_ASSERT(" << expression << ") " << file << ":" << line << std::endl;
    exit(1);
  }
}

#endif
