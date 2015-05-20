//  -*- coding:utf-8-unix; -*-
/*
 * containers_primptr.h
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

#ifndef CONTAINERS_PRIMPTR_H
#define CONTAINERS_PRIMPTR_H

int *iptr(int value);
unsigned int *uiptr(unsigned int value);
long *lptr(long value);
unsigned long *ulptr(unsigned long value);
char *cptr(char value);
double *dptr(double value);

#endif /* CONTAINERS_PRIMPTR_H */
