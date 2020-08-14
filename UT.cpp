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


#include "UT/UT.h"

ut *ut::reg_ = nullptr;

int main(int argc, char **argv)
{
  ut::runAll();
  return 0;
}

ut::ut(std::function<void()> fn, const char *name) :
  name_(name),
  fn_(fn),
  next_(nullptr)
{
  this->next_ = ut::reg_;
  ut::reg_ = this;
}

void ut::runAll()
{
  ut *node = ut::reg_;
  while (node) {
    std::cout << "Test " << node->name_ << ":" << std::endl;
    node->fn_();
    std::cout << "  OK" << std::endl;
    node = node->next_;
  }
}