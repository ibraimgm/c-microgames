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
#include "containers.h"

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

// extra members needed for use with printc, etc.
static int DEFAULT_FOREGROUND = INTENSITY_DULL + COLOR_WHITE;
static int DEFAULT_BACKGROUND = INTENSITY_DULL + COLOR_BLACK;
static int CURRENT_FOREGROUND = INTENSITY_DULL + COLOR_WHITE;
static int CURRENT_BACKGROUND = INTENSITY_DULL + COLOR_BLACK;

typedef struct ColorPair
{
  int fg;
  int bg;
} ColorPair;

// definitios to use with the win32 console API
#ifdef USE_WINDOWS_CONSOLE_API
static HANDLE hconsole = 0;
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
#endif

void set_default_colors(int foreground, int background)
{
  if (foreground != COLOR_UNCHANGED)
    DEFAULT_FOREGROUND = foreground;

  if (background != COLOR_UNCHANGED)
    DEFAULT_BACKGROUND = background;

  setSGR(DEFAULT_FOREGROUND, DEFAULT_BACKGROUND);
}

void resetSGR()
{
#ifdef USE_WINDOWS_CONSOLE_API
  SetConsoleTextAttribute(get_console_handle(), saved_attributes);
#else
  printf("\x1b[0m");
#endif

  CURRENT_FOREGROUND = DEFAULT_FOREGROUND;
  CURRENT_BACKGROUND = DEFAULT_BACKGROUND;
}

void setSGR(int foreground, int background)
{
#ifdef USE_WINDOWS_CONSOLE_API
  WORD fg = foreground == COLOR_UNCHANGED
    ? ansi_to_wincolor(CURRENT_FOREGROUND + LAYER_FOREGROUND)
    : ansi_to_wincolor(foreground + LAYER_FOREGROUND);
  WORD bg = background == COLOR_UNCHANGED
    ? ansi_to_wincolor(CURRENT_BACKGROUND + LAYER_BACKGROUND)
    : ansi_to_wincolor(background + LAYER_BACKGROUND);

  SetConsoleTextAttribute(get_console_handle(), fg | bg);
#else
  if (foreground != COLOR_UNCHANGED)
    printf("\x1b[%dm", foreground + LAYER_FOREGROUND);

  if (background != COLOR_UNCHANGED)
    printf("\x1b[%dm", background + LAYER_BACKGROUND);
#endif

  CURRENT_FOREGROUND = foreground != COLOR_UNCHANGED ? foreground : CURRENT_FOREGROUND;
  CURRENT_BACKGROUND = background != COLOR_UNCHANGED ? background : CURRENT_BACKGROUND;
}

void gotoxy(unsigned int x, unsigned int y)
{
#ifdef USE_WINDOWS_CONSOLE_API
  COORD c;
  c.X = x;
  c.Y = y;

  SetConsoleCursorPosition(get_console_handle(), c);
#else
  printf("\x1b[%d;%dH", y, x);
#endif
}

void clearscreen()
{
#ifdef USE_WINDOWS_CONSOLE_API
  HANDLE h = get_console_handle();
  CONSOLE_SCREEN_BUFFER_INFO info;
  COORD start = {0, 0};
  DWORD chars_written;

  GetConsoleScreenBufferInfo(h, &info);
  FillConsoleOutputCharacter(h, ' ', info.dwSize.X * info.dwSize.Y, start, &chars_written);
  SetConsoleCursorPosition(h, start);
#else
  printf("\x1b[2J");
  gotoxy(0, 0);
#endif
}

void set_cursor_visibility(bool visible)
{
#ifdef USE_WINDOWS_CONSOLE_API
  CONSOLE_CURSOR_INFO cursor;

  cursor.dwSize = 1;
  cursor.bVisible = visible;
  SetConsoleCursorInfo(get_console_handle(), &cursor);
#else
  printf("\x1b[?25%c", visible ? 'h' : 'l');
#endif
}

static int char_to_color(char c)
{
  switch (c)
  {
    case 'r': return DULL_RED;
    case 'g': return DULL_GREEN;
    case 'b': return DULL_BLUE;
    case 'c': return DULL_CYAN;
    case 'm': return DULL_MAGENTA;
    case 'y': return DULL_YELLOW;
    case 'k': return DULL_BLACK;
    case 'w': return DULL_WHITE;
    case 'R': return VIVID_RED;
    case 'G': return VIVID_GREEN;
    case 'B': return VIVID_BLUE;
    case 'C': return VIVID_CYAN;
    case 'M': return VIVID_MAGENTA;
    case 'Y': return VIVID_YELLOW;
    case 'K': return VIVID_BLACK;
    case 'W': return VIVID_WHITE;
    case '_': return COLOR_UNCHANGED;
    default: return 0;
  }
}

void printc(const char *format, ...)
{
  // start argument parsing
  va_list args;
  va_start(args, format);

  // get the needed buffer size
  int bsize = vsnprintf(NULL, 0, format, args);
#ifdef _MSC_VER
  char *buffer = malloc(sizeof(char) * (bsize + 1)); // C2466
#else
  char buffer[bsize + 1];
#endif

  // get teh data and finalize the arguments
  vsnprintf(buffer, bsize + 1, format, args);
  va_end(args);

  // the stack of colors to use
  CList *color_stack = clist_new();

  // parsing
  for (int i = 0; buffer[i] != '\0'; ++i)
  {
    char c0 = buffer[i];

    // we found 'begin' token!
    if (c0 == '$')
    {
      char c1 = buffer[i + 1];

      if (c1 == '\0') goto no_token;

      // if the next character is a '$' or '}', it's just a escape sequence
      if ((c1 == '$') || (c1 == '}'))
      {
        printf("%c", c1);
        ++i;
        continue;
      }

      // store the colors and the characters to be consumed
      int fg = char_to_color(c1);
      int bg = 0;
      int chars_to_skip = 0;

      // is this character a color?
      if (fg)
      {
        // let's see if the next character is also a color
        if (buffer[i + 2] == '\0') goto no_token;

        char ch2 = buffer[i + 2];
        bg = char_to_color(ch2);

        //if we found a color, we need to check the next character for '{'
        if (bg)
        {
          if (buffer[i + 3] == '\0') goto no_token;

          char ch3 = buffer[i + 3];
          chars_to_skip = ch3 == '{' ? 3 : 0;
        }
        // instead of a color, we found a '{'
        else if (ch2 == '{')
        {
          bg = COLOR_UNCHANGED;
          chars_to_skip = 2;
        }
        //not a color and not a '{'.
      }
      // not a fg color!

      // now, if we came this far, we need to consume the characters and
      // apply the colors. We do this maintaining a stack of the colors used
      if (chars_to_skip)
      {
        fg = fg == COLOR_UNCHANGED ? CURRENT_FOREGROUND : fg;
        bg = bg == COLOR_UNCHANGED ? CURRENT_BACKGROUND : bg;

        ColorPair *p = malloc(sizeof(ColorPair));
        p->fg = CURRENT_FOREGROUND;
        p->bg = CURRENT_BACKGROUND;
        clist_push(color_stack, p);

        setSGR(fg, bg);

        while ((chars_to_skip > 0) && (buffer[i] != '\0'))
        {
          ++i;
          --chars_to_skip;
        }

        continue;
      }
    }

    // we got an 'end' token, and we have colors to pop
    if ((c0 == '}') && clist_peek(color_stack))
    {
      ColorPair *p = clist_pop(color_stack);
      setSGR(p->fg, p->bg);

      free(p);
      continue;
    }

  no_token:
    // no token here...
    printf("%c", c0);
  } // for

  //now, the user may have forgot to close one or more of the control sequences.
  //in this case, we simply pop them all and apply the last one
  int fg = COLOR_UNCHANGED, bg = COLOR_UNCHANGED;

  while (clist_peek(color_stack))
  {
    ColorPair *p = clist_pop(color_stack);
    fg = p->fg;
    bg = p->bg;

    free(p);
  }

  setSGR(fg, bg);
  free(color_stack);
#ifdef _MSC_VER
  free(buffer);
#endif
}
