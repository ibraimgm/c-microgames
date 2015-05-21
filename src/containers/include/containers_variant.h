//  -*- coding:utf-8-unix; -*-
/*
 * containers_variant.h
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
#ifndef CONTAINERS_VARIANT_H
#define CONTAINERS_VARIANT_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum VariantType
{
  varUnassigned,
  varInt,
  varUInt,
  varLong,
  varULong,
  varDouble,
  varPtr
} VariantType;

typedef struct Variant Variant;

#define GEN_VAL_TO_VAR(type, name) Variant *name##tovar(type value);
#define GEN_VAR_TO_VAL_DEF(type, name) type varto##name##def(Variant *value, type default_value);
#define GEN_VAR_SET(type, name) void varset##name(Variant *var, type value);
#define GEN_VAR_IS(name) bool varis##name(Variant *value);

GEN_VAL_TO_VAR(int, int)
GEN_VAL_TO_VAR(unsigned int, uint)
GEN_VAL_TO_VAR(long, long)
GEN_VAL_TO_VAR(unsigned long, ulong)
GEN_VAL_TO_VAR(double, double)
GEN_VAL_TO_VAR(void *,ptr)

GEN_VAR_TO_VAL_DEF(int, int)
GEN_VAR_TO_VAL_DEF(unsigned int, uint)
GEN_VAR_TO_VAL_DEF(long, long)
GEN_VAR_TO_VAL_DEF(unsigned long, ulong)
GEN_VAR_TO_VAL_DEF(double, double)
GEN_VAR_TO_VAL_DEF(void *,ptr)

GEN_VAR_SET(int, int)
GEN_VAR_SET(unsigned int, uint)
GEN_VAR_SET(long, long)
GEN_VAR_SET(unsigned long, ulong)
GEN_VAR_SET(double, double)
GEN_VAR_SET(void *,ptr)

GEN_VAR_IS(int)
GEN_VAR_IS(uint)
GEN_VAR_IS(long)
GEN_VAR_IS(ulong)
GEN_VAR_IS(double)
GEN_VAR_IS(ptr)

Variant *varEmpty();
void varClear(Variant *value);
VariantType vartype(Variant *value);
bool varassigned(Variant *value);

#define vartoint(v) vartointdef(v, 0)
#define vartouint(v) vartouintdef(v, 0)
#define vartolong(v) vartolongdef(v, 0)
#define vartoulong(v) vartoulongdef(v, 0)
#define vartodouble(v) vartodoubledef(v, 0)
#define vartoptr(v) vartoptrdef(v, NULL)
#define varfree(v) free(v)

#undef GEN_VAL_TO_VAR
#undef GEN_VAR_TO_VAL_DEF
#undef GEN_VAR_SET
#undef GEN_VAR_IS

#endif /* CONTAINERS_VARIANT_H */
