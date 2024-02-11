/**
 * Virtual Rendering Library
 *
 * Functions' prefixes:
 *  - 'vr': virtual rendering
 *  - 'm': max arguments
 *  - 'n': newline?
 *  - 'v': values (do not use pointers for virtual coords)
 *
 */
#ifndef VRENDER_H
#define VRENDER_H

#include <ncurses.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * @brief Prints a string to a specified window, considering virtualized coordinates.
 *
 * This function prints the input string to the given window using virtualized
 * coordinates. It supports automatic newline and moves to the next line when
 * reaching the end of the screen.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param maxY Maximum Y-coordinate of the window.
 * @param maxX Maximum X-coordinate of the window.
 * @param autonl If true, enables automatic newline at the end of the max
 *               y-coordinate of the window.
 * @param str The string to be printed.
 */
void vrmn_mvwaddstr(WINDOW *win, int *virY, int *virX, int maxY, int maxX, bool autonl, const char *str);

/**
 * @brief Prints a string to a specified window, considering virtualized
 *        coordinates, with automatic newline.
 *
 * This function is a wrapper for vrmn_mvwaddstr with autonl set to true.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param maxY Maximum Y-coordinate of the window.
 * @param maxX Maximum X-coordinate of the window.
 * @param str The string to be printed.
 */
void vrm_mvwaddstr(WINDOW *win, int *virY, int *virX, int maxY, int maxX, const char *str);

/**
 * @brief Prints a formatted string to a specified window, considering
 *        virtualized coordinates.
 *
 * This function is a wrapper for vrmn_mvwaddstr with a formatted string to output.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param maxY Maximum Y-coordinate of the window.
 * @param maxX Maximum X-coordinate of the window.
 * @param autonl If true, enables automatic newline at the end of the max
 *               y-coordinate of the window.
 * @param str The string to be printed.
 */
void vrmn_mvwprintw(WINDOW *win, int *virY, int *virX, int maxY, int maxX, bool autonl, const char *__format, ...);

/**
 * @brief Prints a formatted string to a specified window, considering
 *        virtualized coordinates and using va_list.
 *
 * This function is a wrapper for vrmn_mvwaddstr with the formatted string
 * obtained using a va_list.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param maxY Maximum Y-coordinate of the window.
 * @param maxX Maximum X-coordinate of the window.
 * @param autonl If true, enables automatic newline at the end of the max
 *               y-coordinate of the window.
 * @param __format The format string.
 * @param __args The va_list containing the format arguments.
 */
void vrmn_mvvwprintw(WINDOW *win, int *virY, int *virX, int maxY, int maxX, bool autonl, const char *__format, va_list __args);

/**
 * @brief Prints a formatted string to a specified window considering
 *        virtualized coordinates
 *
 * This function is a wrapper for vrmn_mvvwprintw with autonl set to true.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param maxY Maximum Y-coordinate of the window.
 * @param maxX Maximum X-coordinate of the window.
 * @param __format The format string.
 * @param ... Additional arguments for the format string.
 */
void vrm_mvwprintw(WINDOW *win, int *virY, int *virX, int maxY, int maxX, const char *__format, ...);

/**
 * @brief Prints a formatted string to a specified window using a va_list and
 *        automatic newline.
 *
 * This function is a wrapper for vrmn_mvvwprintw with autonl set to true.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param maxY Maximum Y-coordinate of the window.
 * @param maxX Maximum X-coordinate of the window.
 * @param __format The format string.
 * @param __args The va_list containing the format arguments.
 */
void vrm_mvvwprintw(WINDOW *win, int *virY, int *virX, int maxY, int maxX, const char *__format, va_list __args);

/**
 * @brief Prints a formatted string to a specified window with virtualized
 *        coordinates.
 *
 * This function is a wrapper for vrmn_mvvwprintw with the format arguments
 * obtained using additional arguments.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param autonl If true, enables automatic newline at the end of the max
 *               y-coordinate of the window.
 * @param __format The format string.
 * @param ... Additional arguments for the format string.
 */
void vrn_mvwprintw(WINDOW *win, int *virY, int *virX, bool autonl, const char *__format, ...);

/**
 * @brief Prints a formatted string to a specified window with virtualized
 *        coordinates, and the format arguments obtained with va_list.
 *
 * This function is a wrapper for vrmn_mvvwprintw using va_list for
 * format arguments.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param autonl If true, enables automatic newline at the end of the max
 *               y-coordinate of the window.
 * @param __format The format string.
 * @param __args The va_list containing the format arguments.
 */
void vrn_mvvwprintw(WINDOW *win, int *virY, int *virX, bool autonl, const char *__format, va_list __args);

/**
 * @brief Prints a formatted string to a specified window with virtualized
 *        coordinates.
 *
 * This function is a wrapper for vrn_mvvwprintw with autonl set to true.
 *
 * @param win The target window.
 * @param virY Pointer to the virtual Y-coordinate.
 * @param virX Pointer to the virtual X-coordinate.
 * @param __format The format string.
 * @param ... Additional arguments for the format string.
 */
void vr_mvwprintw(WINDOW *win, int *virY, int *virX, const char *__format, ...);

/**
 * @brief Prints a formatted string to a specified window, considering
 *        virtualized coordinates (not pointers) and using va_list.
 *
 * This function is a wrapper for vrmn_mvwaddstr with the formatted string
 * obtained using a va_list.
 *
 * @param win The target window.
 * @param virY The virtual Y-coordinate.
 * @param virX The virtual X-coordinate.
 * @param maxY Maximum Y-coordinate of the window.
 * @param maxX Maximum X-coordinate of the window.
 * @param autonl If true, enables automatic newline at the end of the max
 *               y-coordinate of the window.
 * @param __format The format string.
 * @param __args The va_list containing the format arguments.
 */
void vrmnv_mvvwprintw(WINDOW *win, int virY, int virX, int maxY, int maxX, bool autonl, const char *__format, va_list __args);

/**
 * @brief Prints a formatted string to a specified window with virtualized
 *        coordinates without using virtual pointers.
 *
 * @param win The target window.
 * @param virY The virtual Y-coordinate.
 * @param virX The virtual X-coordinate.
 * @param __format The format string.
 * @param ... Additional arguments for the format string.
 */
void vrv_mvwprintw(WINDOW *win, int virY, int virX, const char *__format, ...);

#endif // VRENDER_H
