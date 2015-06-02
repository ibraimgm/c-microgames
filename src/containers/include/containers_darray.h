//  -*- coding:utf-8-unix; -*-
/*
 * containers_darray.h
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
#ifndef CONTAINERS_DARRAY_H
#define CONTAINERS_DARRAY_H

typedef struct DArray DArray;

DArray *darray_new(unsigned int max);
void darray_destroy(DArray *array, void *(*free_fn)(void *));
void darray_clear(DArray *array, void *(*free_fn)(void *));

unsigned int darray_max(DArray *array);
unsigned int darray_size(DArray *array);

void *darray_get(DArray *array, unsigned int i);
void darray_set(DArray *array, unsigned int i, void *value);
void darray_append(DArray *array, void *value);

void darray_expand_size(DArray *array, unsigned int size);
void darray_expand_times(DArray *array, unsigned int times);
#define darray_expand(array) darray_expand_times(array, 1)
void darray_shrink(DArray *array);

void darray_sort(DArray *array, int (*compare_fn)(const void *, const void *));

#endif /* CONTAINERS_DARRAY_H */
