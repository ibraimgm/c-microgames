//  -*- coding:utf-8-unix; -*-
/*
 * consio_input.h
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

#ifndef CONSIO_INPUT_H
#define CONSIO_INPUT_H

#include "consio_config.h"
#include <stdbool.h>

#ifndef HAVE_GETOPT_H
#include "getopt.h"
#else
#include <getopt.h>
#endif

#ifdef HAVE_CONIO_H
#include <conio.h>
#endif

// handle getopt erros and exit
void handle_getopt_err(int opt_status, int opt_value);

// raise a getopt error and exit
void raise_getopt_err(char *message);

#ifndef HAVE_GETCH
// reads a character without buffering
int getche();

// reads a character without buffering and without echo
int getch();
#endif

// reads a character from a restricted subset
int getch_restrict_e(const char *valid_chars, bool echo);
#define getche_restrict(valid_chars) getch_restrict_e(valid_chars, true)
#define getch_restrict(valid_chars) getch_restrict_e(valid_chars, false)

#endif /* CONSIO_INPUT_H */
