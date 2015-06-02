//  -*- coding:utf-8-unix; -*-
/*
 * containers_darray.c
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

#include "containers_darray.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_DARRAY_SIZE 100

typedef struct DArray
{
  unsigned int max;
  unsigned int len;
  void **data;
} DArray;

DArray *darray_new(unsigned int max)
{
  DArray *array = malloc(sizeof(DArray));
  array->max = 0;
  array->len = 0;

  if (max == 0)
    darray_expand_size(array, DEFAULT_DARRAY_SIZE);
  else
    darray_expand_size(array, max);

  return array;
}

void darray_destroy(DArray *array, void *(*free_fn)(void *))
{
  darray_clear(array, free_fn);
  free(array->data);
  free(array);
}

void darray_clear(DArray *array, void *(*free_fn)(void *))
{
  for(unsigned int i = 0; i < array->len; ++i)
  {
    if (free_fn != NULL)
      free_fn(array->data[i]);
    else
      free(array->data[i]);

    array->data[i] = NULL;
  }

  array->len = 0;
}

unsigned int darray_max(DArray *array)
{
  return array->max;
}

unsigned int darray_size(DArray *array)
{
  return array->len;
}

void *darray_get(DArray *array, unsigned int i)
{
  return (i >= array->len) ? NULL : array->data[i];
}

void darray_set(DArray *array, unsigned int i, void *value)
{
  // increase array size
  while (i >= array->max)
    darray_expand_size(array, array->max);

  array->data[i] = value;

  if (i >= array->len)
    array->len = i+1;
}

void darray_append(DArray *array, void *value)
{
  // increase array size
  if (array->len == array->max)
    darray_expand_size(array, array->max);

  darray_set(array, array->len, value);
}

void darray_expand_size(DArray *array, unsigned int size)
{
  unsigned int start, end;

  if (array->max == 0)
  {
    array->data = calloc(size, sizeof(void*));
    array->max = size;
    start = 0;
    end = size - 1;
  }
  else
  {
    array->data = realloc(array->data, (array->max + size) * sizeof(void*));
    start = array->max;
    array->max += size;
    end = array->max - 1;
  }

  for (; start != end; ++start)
    array->data[start] = NULL;
}

void darray_expand_times(DArray *array, unsigned int times)
{
  darray_expand_size(array, array->max * times);
}

void darray_shrink(DArray *array)
{
  if (array->len == 0)
    return;

  array->data = realloc(array->data, array->len * sizeof(void*));
  array->max = array->len;
}

void darray_sort(DArray *array, int (*compare_fn)(const void *, const void *))
{
  qsort(array->data, array->len, sizeof(void*), compare_fn);
}
