//  -*- coding:utf-8-unix; -*-
/*
 * containers_primptr.c
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

#include "containers_primptr.h"
#include <stdlib.h>

#define PRIMPTR_TEMPLATE(type, name) type *name(type value) {\
  type *p = malloc(sizeof(type));\
  *p = value;\
  return p;\
  }

PRIMPTR_TEMPLATE(int, iptr)
PRIMPTR_TEMPLATE(unsigned int, uiptr)
PRIMPTR_TEMPLATE(long, lptr)
PRIMPTR_TEMPLATE(unsigned long, ulptr)
PRIMPTR_TEMPLATE(char, cptr)
PRIMPTR_TEMPLATE(double, dptr)

#undef PRIMPTR_TEMPLATE
