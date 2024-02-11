#include "vrender.h"
#include <ncurses.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

void vrmn_mvwaddstr(WINDOW *win, int *virY, int *virX, int maxY, int maxX, bool autonl, const char *str)
{
  // print string
  int begX = *virX;
  int begY = *virY;
  int actualMaxX;
  int actualMaxY;
  getmaxyx(stdscr, actualMaxY, actualMaxX);

  // print char by char until null character
  for (char *ch = (char *)str; (*ch) != '\0'; ch++)
  {
    // print char on the actual screen if it is within bounds
    if ((*virY) < maxY && (*virX) < maxX && (*virY) < actualMaxY && (*virX) < actualMaxX)
    {
      mvaddch(*virY, *virX, *ch);
    }

    (*virX)++;

    // if at the end of screen BUT does not support auto newline
    // then move on
    if (!autonl && (*virX) == maxX)
    {
      continue;
    }

    // if ch is newline, go down
    // if at the end of screen, go down
    if ((*virX) == maxX || (*ch) == '\n' || (*ch) == '\r')
    {
      // remove carriage return if newline is '\n\r'
      if ((*ch) == '\n' && (*(ch + 1)) == '\r')
      {
        ch++;
      }

      *virX = begX;
      (*virY)++;
    }
  }

  // synchronize actual X and Y with the virtual ones (if possible)
  move(*virY, *virX);
}

void vrm_mvwaddstr(WINDOW *win, int *virY, int *virX, int maxY, int maxX, const char *str)
{
  vrmn_mvwaddstr(win, virY, virX, maxY, maxX, true, str);
}

void vrmn_mvwprintw(WINDOW *win, int *virY, int *virX, int maxY, int maxX, bool autonl, const char *__format, ...)
{
  // get formatted string to buffer
  char *buffer;
  va_list args;
  // get final string size and put format string to buffer
  va_start(args, __format);
  buffer = malloc(vsnprintf(NULL, 0, __format, args) + 1); // +1 for null char
  va_end(args);
  va_start(args, __format);
  vsprintf(buffer, __format, args);
  va_end(args);

  vrmn_mvwaddstr(win, virY, virX, maxY, maxX, autonl, buffer);
}

void vrmn_mvvwprintw(WINDOW *win, int *virY, int *virX, int maxY, int maxX, bool autonl, const char *__format, va_list __args)
{
  // get formatted string to buffer
  char *buffer;
  va_list args;
  va_copy(args, __args);
  // get final string size and put format string to buffer
  buffer = malloc(vsnprintf(NULL, 0, __format, __args) + 1); // +1 for null char
  vsprintf(buffer, __format, args);
  va_end(args);

  vrmn_mvwaddstr(win, virY, virX, maxY, maxX, autonl, buffer);
}

void vrm_mvwprintw(WINDOW *win, int *virY, int *virX, int maxY, int maxX, const char *__format, ...)
{
  // get format arguments
  va_list args;
  va_start(args, __format);
  vrmn_mvvwprintw(win, virY, virX, maxY, maxX, true, __format, args);
  va_end(args);
}

void vrm_mvvwprintw(WINDOW *win, int *virY, int *virX, int maxY, int maxX, const char *__format, va_list __args)
{
  vrmn_mvvwprintw(win, virY, virX, maxY, maxX, true, __format, __args);
}

void vrn_mvwprintw(WINDOW *win, int *virY, int *virX, bool autonl, const char *__format, ...)
{
  // get format arguments
  va_list args;
  va_start(args, __format);

  int maxX;
  int maxY;
  getmaxyx(win, maxY, maxX);

  vrmn_mvvwprintw(win, virY, virX, maxY, maxX, autonl, __format, args);
  va_end(args);
}

void vrn_mvvwprintw(WINDOW *win, int *virY, int *virX, bool autonl, const char *__format, va_list __args)
{
  int maxX;
  int maxY;
  getmaxyx(win, maxY, maxX);
  vrmn_mvvwprintw(win, virY, virX, maxY, maxX, autonl, __format, __args);
}

void vr_mvwprintw(WINDOW *win, int *virY, int *virX, const char *__format, ...)
{
  // get format arguments
  va_list args;
  va_start(args, __format);
  vrn_mvvwprintw(win, virY, virX, true, __format, args);
  va_end(args);
}
