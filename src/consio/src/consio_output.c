// -*- coding:utf-8-unix; -*-
/*
 * consio_output.c
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

#include "consio_output.h"

#ifdef USE_WINDOWS_CONSOLE_API
#include <windows.h>
#endif

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// Values and offsets according to ANSI
#define LAYER_FOREGROUND 30
#define LAYER_BACKGROUND 40

#define INTENSITY_DULL 0
#define INTENSITY_VIVID 60

#define COLOR_BLACK   0
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_MAGENTA 5
#define COLOR_CYAN    6
#define COLOR_WHITE   7

const int COLOR_UNCHANGED = -1;

const int DULL_BLACK   = INTENSITY_DULL + COLOR_BLACK;
const int DULL_RED     = INTENSITY_DULL + COLOR_RED;
const int DULL_GREEN   = INTENSITY_DULL + COLOR_GREEN;
const int DULL_YELLOW  = INTENSITY_DULL + COLOR_YELLOW;
const int DULL_BLUE    = INTENSITY_DULL + COLOR_BLUE;
const int DULL_MAGENTA = INTENSITY_DULL + COLOR_MAGENTA;
const int DULL_CYAN    = INTENSITY_DULL + COLOR_CYAN;
const int DULL_WHITE   = INTENSITY_DULL + COLOR_WHITE;

const int VIVID_BLACK   = INTENSITY_VIVID + COLOR_BLACK;
const int VIVID_RED     = INTENSITY_VIVID + COLOR_RED;
const int VIVID_GREEN   = INTENSITY_VIVID + COLOR_GREEN;
const int VIVID_YELLOW  = INTENSITY_VIVID + COLOR_YELLOW;
const int VIVID_BLUE    = INTENSITY_VIVID + COLOR_BLUE;
const int VIVID_MAGENTA = INTENSITY_VIVID + COLOR_MAGENTA;
const int VIVID_CYAN    = INTENSITY_VIVID + COLOR_CYAN;
const int VIVID_WHITE   = INTENSITY_VIVID + COLOR_WHITE;

#ifdef USE_WINDOWS_CONSOLE_API
static HANDLE hconsole = 0;
static WORD last_bg;
static WORD last_fg;
static WORD saved_attributes;

// make sure we have a valid handle
static HANDLE get_console_handle()
{
  if (!hconsole)
  {
    CONSOLE_SCREEN_BUFFER_INFO info;

    hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hconsole, &info);
    saved_attributes = info.wAttributes;

    last_bg = 0;
    last_bg |= (saved_attributes & BACKGROUND_RED)       ? BACKGROUND_RED       : 0;
    last_bg |= (saved_attributes & BACKGROUND_GREEN)     ? BACKGROUND_GREEN     : 0;
    last_bg |= (saved_attributes & BACKGROUND_BLUE)      ? BACKGROUND_BLUE      : 0;
    last_bg |= (saved_attributes & BACKGROUND_INTENSITY) ? BACKGROUND_INTENSITY : 0;

    last_fg = 0;
    last_fg |= (saved_attributes & FOREGROUND_RED)       ? FOREGROUND_RED       : 0;
    last_fg |= (saved_attributes & FOREGROUND_GREEN)     ? FOREGROUND_GREEN     : 0;
    last_fg |= (saved_attributes & FOREGROUND_BLUE)      ? FOREGROUND_BLUE      : 0;
    last_fg |= (saved_attributes & FOREGROUND_INTENSITY) ? FOREGROUND_INTENSITY : 0;
  }

  return hconsole;
}

// translate colors to windows constants
static WORD ansi_to_wincolor(int color)
{
  WORD attr;
  bool vivid = false;
  bool bg = false;

  // first, determine the 'extended' attributes of the color
  if (color >= INTENSITY_VIVID)
  {
    vivid = true;
    color -= INTENSITY_VIVID;
  }
  else
    color -= INTENSITY_DULL;

  if (color >= LAYER_BACKGROUND)
  {
    bg = true;
    color -= LAYER_BACKGROUND;
  }
  else
    color -= LAYER_FOREGROUND;

  // now, we should have the 'pure' color value.
  switch (color)
  {
    case COLOR_BLACK:
      attr = 0;
      break;

    case COLOR_RED:
      attr = bg ? BACKGROUND_RED : FOREGROUND_RED;
      break;

    case COLOR_GREEN:
      attr = bg ? BACKGROUND_GREEN : FOREGROUND_GREEN;
      break;

    case COLOR_YELLOW:
      attr = bg
        ? BACKGROUND_RED | BACKGROUND_GREEN
        : FOREGROUND_RED | FOREGROUND_GREEN;
      break;

    case COLOR_BLUE:
      attr = bg ? BACKGROUND_BLUE : FOREGROUND_BLUE;
      break;

    case COLOR_MAGENTA:
      attr = bg
        ? BACKGROUND_RED | BACKGROUND_BLUE
        : FOREGROUND_RED | FOREGROUND_BLUE;
      break;

    case COLOR_CYAN:
      attr = bg
        ? BACKGROUND_GREEN | BACKGROUND_BLUE
        : FOREGROUND_GREEN | FOREGROUND_BLUE;
      break;

    case COLOR_WHITE:
      attr = bg
        ? BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
        : FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
      break;
  }

  // last, but not least, we add the intensity
  if (vivid)
    attr |= bg ? BACKGROUND_INTENSITY : FOREGROUND_INTENSITY;

  return attr;
}

void resetSGR()
{
  SetConsoleTextAttribute(get_console_handle(), saved_attributes);
}

void setSGR(int foreground, int background)
{
  WORD fg = foreground == COLOR_UNCHANGED ? last_fg : ansi_to_wincolor(foreground + LAYER_FOREGROUND);
  WORD bg = background == COLOR_UNCHANGED ? last_bg : ansi_to_wincolor(background + LAYER_BACKGROUND);

  SetConsoleTextAttribute(get_console_handle(), fg | bg);
  last_fg = fg;
  last_bg = bg;
}

void gotoxy(unsigned int x, unsigned int y)
{
  COORD c;
  c.X = x;
  c.Y = y;

  SetConsoleCursorPosition(get_console_handle(), c);
}

void clearscreen()
{
  HANDLE h = get_console_handle();
  CONSOLE_SCREEN_BUFFER_INFO info;
  COORD start = {0, 0};
  DWORD chars_written;

  GetConsoleScreenBufferInfo(h, &info);
  FillConsoleOutputCharacter(h, ' ', info.dwSize.X * info.dwSize.Y, start, &chars_written);
  SetConsoleCursorPosition(h, start);
}

void set_cursor_visibility(bool visible)
{
  CONSOLE_CURSOR_INFO cursor;

  cursor.dwSize = 1;
  cursor.bVisible = visible;
  SetConsoleCursorInfo(get_console_handle(), &cursor);
}
#else
void resetSGR()
{
  printf("\x1b[0m");
}

void setSGR(int foreground, int background)
{
  if (foreground != COLOR_UNCHANGED)
    printf("\x1b[%dm", foreground + LAYER_FOREGROUND);

  if (background != COLOR_UNCHANGED)
    printf("\x1b[%dm", background + LAYER_BACKGROUND);
}

void clearscreen()
{
  printf("\x1b[2J");
  gotoxy(0, 0);
}

void gotoxy(unsigned int x, unsigned int y)
{
  printf("\x1b[%d;%dH", y, x);
}

void set_cursor_visibility(bool visible)
{
  printf("\x1b[?25%c", visible ? 'h' : 'l');
}
#endif
