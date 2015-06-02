//  -*- coding:utf-8-unix; -*-
/*
 * test_darray.c
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

static DArray *array = NULL;

MU_TEST(test_darray_new)
{
  array = darray_new(10);
  mu_check(array != NULL);
  mu_check(darray_max(array) == 10);
  mu_check(darray_size(array) == 0);
  mu_check(darray_get(array, 0) == NULL);
}

MU_TEST(test_darray_get_set)
{
  darray_set(array, 0, iptr(5));
  mu_check(darray_size(array) == 1);

  darray_set(array, 2, iptr(10));
  mu_check(darray_size(array) == 3);

  darray_append(array, iptr(7));
  darray_append(array, iptr(8));
  mu_check(darray_size(array) == 5);

  mu_check(ptri(darray_get(array, 0)) == 5);
  mu_check(darray_get(array, 1) == NULL);
  mu_check(ptri(darray_get(array, 2)) == 10);
  mu_check(ptri(darray_get(array, 3)) == 7);
  mu_check(ptri(darray_get(array, 4)) == 8);
  mu_check(darray_get(array, 5) == NULL);

  mu_check(darray_max(array) == 10);
  mu_check(darray_get(array, 999) == NULL);
}

MU_TEST(test_darray_expand_shrink)
{
  darray_expand(array);
  mu_check(darray_size(array) == 5);
  mu_check(darray_max(array) == 20);

  darray_expand_size(array, 20);
  mu_check(darray_size(array) == 5);
  mu_check(darray_max(array) == 40);

  darray_expand_times(array, 2);
  mu_check(darray_size(array) == 5);
  mu_check(darray_max(array) == 120);

  darray_shrink(array);
  mu_check(darray_size(array) == 5);
  mu_check(darray_max(array) == 5);

  darray_expand_times(array, 5);
  darray_set(array, 27, iptr(50));
  darray_shrink(array);
  mu_check(darray_size(array) == 28);
  mu_check(darray_max(array) == 28);
}

static int sort_asc(const void *a, const void *b)
{
  int ia = **((int**)a);
  int ib = **((int**)b);

  return (ia > ib) - (ia < ib);
}

MU_TEST(test_darray_clear_sort)
{
  mu_check(darray_size(array) != 0);
  mu_check(darray_max(array) != 0);

  darray_clear(array, NULL);
  mu_check(darray_size(array) == 0);

  darray_append(array, iptr(9));
  darray_shrink(array);
  mu_check(darray_size(array) == 1);
  mu_check(darray_max(array) == 1);

  darray_append(array, iptr(5));
  darray_append(array, iptr(8));

  mu_check(darray_size(array) == 3);
  mu_check(darray_max(array) == 4);

  darray_sort(array, sort_asc);
  mu_check(ptri(darray_get(array, 0)) == 5);
  mu_check(ptri(darray_get(array, 1)) == 8);
  mu_check(ptri(darray_get(array, 2)) == 9);
}

MU_TEST_SUITE(test_suite_darray)
{
  MU_RUN_TEST(test_darray_new);
  MU_RUN_TEST(test_darray_get_set);
  MU_RUN_TEST(test_darray_expand_shrink);
  MU_RUN_TEST(test_darray_clear_sort);
  darray_destroy(array, NULL);
}

int main(int argc, char **argv)
{
  MU_RUN_SUITE(test_suite_darray);

  return minunit_fail > 0 ? 1 : 0;
}
