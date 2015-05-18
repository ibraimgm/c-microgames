//  -*- coding:utf-8-unix; -*-
/*
 * containers_clist.h
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

#ifndef CONTAINERS_CLIST_H
#define CONTAINERS_CLIST_H

typedef struct CList CList;

CList *clist_new();
void clist_destroy(CList *list, void *(*free_fn)(void *));

void clist_push(CList *list, void *value);
void clist_add(CList *list, void *value);
void *clist_peek(CList *list);
void *clist_peek_last(CList *list);
void *clist_nth(CList *list, unsigned int index);
void *clist_pop(CList *list);
void *clist_remove_last(CList *list);

#endif /* CONTAINERS_CLIST_H */
