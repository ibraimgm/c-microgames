//  -*- coding:utf-8-unix; -*-
/*
 * consio_output.h
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

#ifndef CONSIO_OUTPUT_H
#define CONSIO_OUTPUT_H

#include <stdbool.h>

extern const int COLOR_UNCHANGED;

extern const int DULL_BLACK;
extern const int DULL_RED;
extern const int DULL_GREEN;
extern const int DULL_YELLOW;
extern const int DULL_BLUE;
extern const int DULL_MAGENTA;
extern const int DULL_CYAN;
extern const int DULL_WHITE;

extern const int VIVID_BLACK;
extern const int VIVID_RED;
extern const int VIVID_GREEN;
extern const int VIVID_YELLOW;
extern const int VIVID_BLUE;
extern const int VIVID_MAGENTA;
extern const int VIVID_CYAN;
extern const int VIVID_WHITE;

void resetSGR();
void setSGR(int foreground, int background);
#define setFG(foreground) setSGR(foreground, COLOR_UNCHANGED);
#define setBG(background) setSGR(background, COLOR_UNCHANGED);

void clearscreen();
void gotoxy(unsigned int x, unsigned int y);

void set_cursor_visibility(bool visible);
#define hidecursor() set_cursor_visibility(false);
#define showcursor() set_cursor_visibility(true);

#endif /* CONSIO_OUTPUT_H */
