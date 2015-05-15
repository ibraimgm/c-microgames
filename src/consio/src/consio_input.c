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
#include <stdlib.h>
#include <string.h>
#include "consio_input.h"


void handle_getopt_err(int opt)
{
  if (opt == ':')
  {
    fprintf (stderr, "ERROR: Option `-%c' requires an argument.\n", optopt);
    fprintf(stderr, "Try `--help` for usage information.\n");
    exit(1);
  }
  else if (opt == '?')
  {
    fprintf (stderr, "ERROR: Unrecognized option: `-%c'.\n", optopt);
    fprintf(stderr, "Try `--help` for usage information.\n");
    exit(1);
  }
}

void raise_getopt_err(char *message)
{
  fprintf(stderr, "ERROR: %s\n", message);
  fprintf(stderr, "Try `--help` for usage information.\n");
  exit(1);
}


#if defined(HAVE_CONIO_H) && !defined(HAVE_GETCH)
int getch()
{
  return _getch();
}

int getche()
{
  return _getche();
}
#elsif !defined(HAVE_CONIO_H)
#error getch() / getche() not implemented
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
