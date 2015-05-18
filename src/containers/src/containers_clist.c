//  -*- coding:utf-8-unix; -*-
/*
 * containers_clist.c
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

#include <stdlib.h>
//#include "containers_clist.h"

typedef struct CListNode
{
  void *value;
  struct CListNode *next;
} CListNode;

typedef struct CList
{
  struct CListNode *first;
  struct CListNode *last;
} CList;

CList *clist_new()
{
  CList *list = malloc(sizeof(CList));
  list->first = NULL;
  list->last = NULL;

  return list;
}

void clist_destroy(CList *list, void *(*free_fn)(void *))
{
  CListNode *node = list->first;

  while (node != NULL)
  {
    if (free_fn != NULL)
      node->value = free_fn(node->value);
    else
      free(node->value);

    CListNode *next = node->next;
    free(node);
    node = next;
  }

  free(list);
}

void clist_push(CList *list, void *value)
{
  CListNode *node = malloc(sizeof(CListNode));
  node->value = value;
  node->next = NULL;

  if (list->first == NULL)
  {
    list->first = node;
    list->last = node;
  }
  else
  {
    node->next = list->first;
    list->first = node;
  }
}

void clist_append(CList *list, void *value)
{
  CListNode *node = malloc(sizeof(CListNode));
  node->value = value;
  node->next = NULL;

  if (list->first == NULL)
  {
    list->first = node;
    list->last = node;
  }
  else
  {
    list->last->next = node;
    list->last = node;
  }
}

void *clist_peek(CList *list)
{
  if (list->first)
    return list->first->value;
  else
    return NULL;
}

void *clist_peek_last(CList *list)
{
  if (list->last)
    return list->last->value;
  else
    return NULL;
}

void *clist_nth(CList *list, unsigned int index)
{
  CListNode *node = list->first;

  while ((node) && (index > 0))
    node = node->next;

  if ((node) && (index == 0))
    return node->value;
  else
    return NULL;
}

void *clist_pop(CList *list)
{
  CListNode *node = list->first;

  if (node)
  {
    void *value = node->value;
    CListNode *next = node->next;

    list->first = next;
    if (list->first == NULL)
      list->last = NULL;

    free(node);
    return value;
  }
  else
    return NULL;
}

void *clist_remove_last(CList *list)
{
  CListNode *node = list->first;

  // no element
  if (!node)
    return NULL;

  //only one element
  if (list->first == list->last)
    return clist_pop(list);

  while ((node->next != NULL) && (node->next != list->last))
    node = node->next;

  CListNode *old_last = node->next;
  void *value = old_last->value;
  node->next = NULL;
  list->last = node;
  free(old_last);

  return value;
}
