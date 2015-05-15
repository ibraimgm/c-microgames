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
#include <stdlib.h>
#include <ctype.h>
#include "config.h"
#include "consio.h"

#define MAX_NUMBER 100

static struct option long_options[] =
{
  {"version", no_argument, NULL, 'v'},
  {"help", no_argument, NULL, 'h'},
  {"max", required_argument, NULL, 'm'},
  {0, 0, 0, 0}
};

int main(int argc, char **argv)
{
  // parse command line options
  bool show_version = false, show_help = false;
  int max = MAX_NUMBER;

  opterr = 0;
  int opt, long_index = 0;
  while ((opt = getopt_long(argc, argv, ":vhm:", long_options, &long_index)) != -1)
    switch (opt)
    {
      case 'v': show_version = true; break;
      case 'h': show_help = true; break;

      case 'm':
        max = atoi(optarg);
        if (max <= 0)
          raise_getopt_err("maximum number must be greater than 0.");
        break;

      default: handle_getopt_err(opt, optopt);
    };

  // display version
  if (show_version)
  {
    printf(APP_HEADER);
    return 0;
  }

  // display usage
  if (show_help)
  {
    printf(APP_DISPLAY_NAME " - " APP_SHORT_DESCRIPTION "\n");
    printf("Usage: %s [OPTIONS]\n", APP_CANONICAL_NAME);
    printf("Options:\n");
    printf("  --version Display version information and exit.\n");
    printf("            (Short: `-v`)\n");
    printf("  --help    Display this help text.\n");
    printf("            (Short: `-h`)\n");
    printf("  --max [N] Set the maximum number to guess to N (default = %d).\n", MAX_NUMBER);
    printf("            (Short: `-m`)\n");
    return 0;
  }

  // from now on, everything looks ok!
  int min = 0;
  int guess; char answer;

  atexit(resetSGR);

  do
  {
    guess = min + (max - min) / 2;

    printf("Did you choose ");
    setFG(VIVID_WHITE);  printf("%d", guess);
    resetSGR();          printf("? (");
    setFG(VIVID_RED);    printf(">");
    resetSGR();          printf(", ");
    setFG(VIVID_YELLOW); printf("<");
    resetSGR();          printf(", ");
    setFG(VIVID_CYAN);   printf("=");
    resetSGR();          printf(") ");
    fflush(stdout);

    setFG(VIVID_MAGENTA);
    answer = getche_restrict("<>=");
    resetSGR();
    printf("\n");

    if (answer == '>')
      min = guess + 1;
    else if (answer == '<')
      max = guess - 1;
  } while ((answer != '=') && (max >= min));

  if (answer == '=')
  {
    setFG(VIVID_GREEN);
    printf("Yep, I guessed the number: %d!\n", guess);
  }
  else if (max < min)
  {
    setFG(VIVID_RED);
    printf("Hey! You cheated!\n");
  }

  return 0;
}
