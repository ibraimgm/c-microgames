//  -*- coding:utf-8-unix; -*-
/*
 * test_clist.c
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

static CList *list = NULL;

static void *iptr(int i)
{
  int *p = malloc(sizeof(int));
  *p = i;
  return p;
}

MU_TEST(test_clist_new)
{
  list = clist_new();
  mu_check(list != NULL);
  mu_check(clist_peek(list) == NULL);
  mu_check(clist_peek_last(list) == NULL);
}

MU_TEST(test_clist_push_append)
{
  int *i;

  clist_push(list, iptr(5));
  clist_push(list, iptr(4));
  clist_push(list, iptr(3));

  i = clist_peek(list);
  mu_check(*i == 3);

  i = clist_peek_last(list);
  mu_check(*i == 5);

  clist_append(list, iptr(6));
  clist_append(list, iptr(7));

  i = clist_peek(list);
  mu_check(*i == 3);

  i = clist_peek_last(list);
  mu_check(*i == 7);
}

MU_TEST(test_clist_pop_remove)
{
  int *i;

  i = clist_pop(list);
  mu_check(*i == 3);
  free(i);

  i = clist_pop(list);
  mu_check(*i == 4);
  free(i);

  i = clist_remove_last(list);
  mu_check(*i == 7);
  free(i);

  i = clist_peek(list);
  mu_check(*i == 5);

  i = clist_peek_last(list);
  mu_check(*i == 6);
}

MU_TEST(test_clist_nth)
{
  int *i;

  clist_push(list, iptr(9));
  clist_append(list, iptr(4));

  i = clist_nth(list, 0);
  mu_check(*i == 9);

  i = clist_nth(list, 1);
  mu_check(*i == 5);

  i = clist_nth(list, 2);
  mu_check(*i == 6);

  i = clist_nth(list, 3);
  mu_check(*i == 4);

  i = clist_nth(list, 4);
  mu_check(i == NULL);
}

static void *just_sum_one(void *data)
{
  int *v = (int *) data;
  (*v)++;

  return NULL;
}

MU_TEST(test_clist_custom_destroy)
{
  CList *x = clist_new();
  int *i = iptr(4);

  clist_push(x, i);
  clist_destroy(x, just_sum_one);
  mu_check((*i * 3) == 15);
  free(i);
}

MU_TEST_SUITE(test_suite_clist)
{
  MU_RUN_TEST(test_clist_new);
  MU_RUN_TEST(test_clist_push_append);
  MU_RUN_TEST(test_clist_pop_remove);
  MU_RUN_TEST(test_clist_nth);
  MU_RUN_TEST(test_clist_custom_destroy);
  clist_destroy(list, NULL);
}

int runTestSuiteCList()
{
  MU_RUN_SUITE(test_suite_clist);

  return minunit_status;
}
