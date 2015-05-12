// -*- coding:utf-8-unix; -*-
/*
 * consio_input.c
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

#include <stdio.h>
#include <string.h>
#include "consio_input.h"


#ifdef WINDOWS
#include <conio.h>

int getch()
{
  return _getch();
}

int getche()
{
  return _getche();
}

#endif

int getch_restrict_e(const char *valid_chars, bool echo)
{
  int c;

  do
  {
    c = getch();
  } while (!strchr(valid_chars, c));

  if (echo)
    printf("%c", c);

  return c;
}
