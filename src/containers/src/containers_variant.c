//  -*- coding:utf-8-unix; -*-
/*
 * containers_variant.c
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

#include "containers_variant.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Variant
{
  VariantType type;

  union
  {
    char charval;
    int intval;
    unsigned int uintval;
    long longval;
    unsigned long ulongval;
    double doubleval;
    void *ptrval;
  } data;
} Variant;

#define GEN_VAL_TO_VAR(atype, name, vtype) Variant *name##tovar(atype value) \
  {\
  Variant *v = varEmpty();\
  varset##name(v, value);\
  return v;\
  }

#define GEN_VAR_TO_VAL_DEF(atype, name, vtype) atype varto##name##def(Variant *value, atype default_value) \
  {\
  return (value->type == vtype) ? value->data.name##val : default_value;\
  }

#define GEN_VAR_SET(atype, name, vtype) void varset##name(Variant *var, atype value) \
  {\
  var->type = vtype;\
  var->data.name##val = value;\
  }

#define GEN_VAR_IS(name, vtype) bool varis##name(Variant *value)\
  {\
  return value->type == vtype;\
  }

GEN_VAL_TO_VAR(char, char, varChar)
GEN_VAL_TO_VAR(int, int, varInt)
GEN_VAL_TO_VAR(unsigned int, uint, varUInt)
GEN_VAL_TO_VAR(long, long, varLong)
GEN_VAL_TO_VAR(unsigned long, ulong, varULong)
GEN_VAL_TO_VAR(double, double, varDouble)
GEN_VAL_TO_VAR(void *,ptr, varPtr)

GEN_VAR_TO_VAL_DEF(char, char, varChar)
GEN_VAR_TO_VAL_DEF(int, int, varInt)
GEN_VAR_TO_VAL_DEF(unsigned int, uint, varUInt)
GEN_VAR_TO_VAL_DEF(long, long, varLong)
GEN_VAR_TO_VAL_DEF(unsigned long, ulong, varULong)
GEN_VAR_TO_VAL_DEF(double, double, varDouble)
GEN_VAR_TO_VAL_DEF(void *,ptr, varPtr)

GEN_VAR_SET(char, char, varChar)
GEN_VAR_SET(int, int, varInt)
GEN_VAR_SET(unsigned int, uint, varUInt)
GEN_VAR_SET(long, long, varLong)
GEN_VAR_SET(unsigned long, ulong, varULong)
GEN_VAR_SET(double, double, varDouble)
GEN_VAR_SET(void *,ptr, varPtr)

GEN_VAR_IS(char, varChar)
GEN_VAR_IS(int, varInt)
GEN_VAR_IS(uint,varUInt)
GEN_VAR_IS(long, varLong)
GEN_VAR_IS(ulong, varULong)
GEN_VAR_IS(double, varDouble)
GEN_VAR_IS(ptr, varPtr)

Variant *varEmpty()
{
  Variant *v = malloc(sizeof(Variant));
  varClear(v);
  return v;
}

void varClear(Variant *value)
{
  value->type = varUnassigned;
  value->data.ptrval = NULL;
}

VariantType vartype(Variant *value)
{
  return value->type;
}

bool varassigned(Variant *value)
{
  return value->type != varUnassigned;
}

#undef GEN_VAL_TO_VAR
#undef GEN_VAR_TO_VAL_DEF
#undef GEN_VAR_SET
#undef GEN_VAR_IS
