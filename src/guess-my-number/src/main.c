// -*- coding:utf-8-unix; -*-
/*
 * main.c
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
#include "config.h"

#define MAX_NUMBER 100

int main(int argc, char **argv)
{
  printf(APP_HEADER);
  int min = 0, max = MAX_NUMBER;
  int guess; char answer;

  do
  {
    guess = min + (max - min) / 2;
    printf("Did you choose %d? (>, <, =) ", guess);
    fflush(stdout);
    answer = getc(stdin); getc(stdin);

    if (answer == '>')
      min = guess + 1;
    else if (answer == '<')
      max = guess - 1;
  } while ((answer != '=') && (max >= min));

  if (answer == '=')
    printf("Yep, I guessed the number: %d!\n", guess);
  else if (max < min)
    printf("Hey! You cheated!");

  return 0;
}
