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

#include "consio_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_TERMIOS_H
#include <termios.h>
#endif

void handle_getopt_err(int opt_status, int opt_value)
{
  if (opt_status == ':')
  {
    fprintf (stderr, "ERROR: Option `-%c' requires an argument.\n", opt_value);
    fprintf(stderr, "Try `--help` for usage information.\n");
    exit(1);
  }
  else if (opt_status == '?')
  {
    fprintf (stderr, "ERROR: Unrecognized option: `-%c'.\n", opt_value);
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

#if defined(HAVE_GETCH)
// do nothing; function already available
#elif defined(HAVE_CONIO_H) && !defined(HAVE_GETCH)
int getch()
{
  return _getch();
}

int getche()
{
  return _getche();
}
#elif !defined(HAVE_CONIO_H) && defined(HAVE_TERMIOS_H)
static struct termios old, new;

void initTermios(int echo)
{
  tcgetattr(0, &old);
  new = old;
  new.c_lflag &= ~ICANON; // disable io buffer
  new.c_lflag &= echo ? ECHO : ~ECHO; // enable/disable echo mode
  tcsetattr(0, TCSANOW, &new);
}

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

int getch()
{
  return getch_(0);
}

int getche()
{
  return getch_(1);
}
#else
#error getch / getche not implemented
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
