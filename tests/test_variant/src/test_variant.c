//  -*- coding:utf-8-unix; -*-
/*
 * test_variant.c
 * Copyright 2015 Rafael Ibraim <ibraim.gm@gmail.com>
 *
 * This file is part of C Microgames.
 *
 * C Microgames is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * C Microgames is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with C Microgames.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "minunit.h"
#include "containers.h"

MU_TEST(test_variant_empty)
{
  Variant *v = varEmpty();
  mu_check(!varassigned(v));
  mu_check(vartoint(v) == 0);
  mu_check(vartouint(v) == 0);
  mu_check(vartolong(v) == 0);
  mu_check(vartoulong(v) == 0);
  mu_check(vartodouble(v) == 0);
  mu_check(vartoptr(v) == NULL);

  varsetint(v, 1);
  mu_check(varassigned(v));

  varfree(v);
}

MU_TEST(test_variant_conversions)
{
  Variant *v = inttovar(5);
  mu_check(varisint(v));
  mu_check(vartoint(v) == 5);

  varsetdouble(v, 10.3);
  mu_check(varisdouble(v));
  mu_check(vartodouble(v) == 10.3);

  int i = 10;
  varsetptr(v, &i);
  mu_check(varisptr(v));
  mu_check(vartoptr(v) != NULL);
  mu_check(ptri(vartoptr(v)) == 10);

  i = 20;
  mu_check(ptri(vartoptr(v)) == 20);

  varClear(v);
  mu_check(!varassigned(v));

  varfree(v);
}

MU_TEST_SUITE(test_suite_variant)
{
  MU_RUN_TEST(test_variant_empty);
  MU_RUN_TEST(test_variant_conversions);
}

int main(int argc, char **argv)
{
  MU_RUN_SUITE(test_suite_variant);

  return minunit_fail > 0 ? 1 : 0;
}
