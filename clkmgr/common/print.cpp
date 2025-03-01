/* SPDX-License-Identifier: BSD-3-Clause
   SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation. */

/** @file
 * @brief Utility functions for printing
 *
 * @author Christopher Hall <christopher.s.hall@intel.com>
 * @copyright © 2024 Intel Corporation.
 *
 */

#include "common/print.hpp"

#include <cstdio>
#include <cstring>

__CLKMGR_NAMESPACE_USE;

using namespace std;

enum LogLevel { DEBUG, INFO, ERROR };
static LogLevel currentLogLevel = INFO;

void clkmgr::_PrintError(string msg, uint16_t line,
    const char *file, const char *func,
    errno_type errnum)
{
    fprintf(stderr, "*** Error: %s %s at line %u in %s: %s\n",
        msg.c_str(),
        errnum != (errno_type)(-1) ? strerror(errnum) : "",
        line, file, func);
    fflush(stderr);
}

void clkmgr::_PrintDebug(string msg, uint16_t line,
    const char *file, const char *func)
{
    if(currentLogLevel <= DEBUG) {
        fprintf(stderr, "*** Debug: %s at line %u in %s: %s\n",
            msg.c_str(), line, file, func);
        fflush(stderr);
    }
}

void clkmgr::_PrintInfo(string msg, uint16_t line, const char *file,
    const char *func)
{
    if(currentLogLevel <= INFO) {
        fprintf(stderr, "* Info: %s at line %u in %s: %s\n",
            msg.c_str(), line, file, func);
        fflush(stderr);
    }
}

#define HEX_DIGITS_PER_LINE 16
void clkmgr::_DumpOctetArray(string msg, const uint8_t *arr,
    size_t length, uint16_t line, const char *file, const char *func)
{
    if(currentLogLevel > DEBUG)
        return;
    fprintf(stderr, "*   Info: %s at line %u in %s:%s",
        msg.c_str(), line, file, func);
    for(size_t i = 0; i < length; i++)
        fprintf(stderr, "%s0x%.2x", i % HEX_DIGITS_PER_LINE ? " " : "\n", arr[i]);
    fprintf(stderr, "\n");
    fflush(stderr);
}
