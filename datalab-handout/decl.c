#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "bits.h"

test_rec test_set[] = {
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
 {"dl10", (funct_t) dl10, (funct_t) test_dl10, 2,
    " ~ & + << ", 12, 3,
  {{0, 31},{0,31},{TMin,TMax}}},
 {"dl11", (funct_t) dl11, (funct_t) test_dl11, 2, "& ~", 5, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl12", (funct_t) dl12, (funct_t) test_dl12, 2, "& ~", 8, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl13", (funct_t) dl13, (funct_t) test_dl13, 1, " ! & ^  >>", 20, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl14", (funct_t) dl14, (funct_t) test_dl14, 2, "& ~", 14, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
{"dl15", (funct_t) dl15, (funct_t) test_dl15, 3,
     "! ~ & ^ | + << >>", 25, 2,
    {{TMin, TMax},{0,3},{0,3}}},
 {"dl16", (funct_t) dl16, (funct_t) test_dl16, 3, "! ~ & ^ | << >>", 16, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl17", (funct_t) dl17, (funct_t) test_dl17, 1,
    "! ~ & ^ | + << >>", 5, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl18", (funct_t) dl18, (funct_t) test_dl18, 2,
    "! ~ & ^ | + << >>", 15, 2,
  {{TMin, TMax},{0,30},{TMin,TMax}}},
 {"dl19", (funct_t) dl19, (funct_t) test_dl19, 0,
    " | <<", 6, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl1", (funct_t) dl1, (funct_t) test_dl1, 1, "! ~ & ^ | + << >>", 10, 4,
  {{-TMax, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl20", (funct_t) dl20, (funct_t) test_dl20, 1,
    "! ~ & + << >>", 12, 3,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl21", (funct_t) dl21, (funct_t) test_dl21, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
 {"dl22", (funct_t) dl22, (funct_t) test_dl22, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
 {"dl23", (funct_t) dl23, (funct_t) test_dl23, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
 {"dl24", (funct_t) dl24, (funct_t) test_dl24, 1, "! ~ & ^ | + << >>", 90, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl2", (funct_t) dl2, (funct_t) test_dl2, 2,
    "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl3", (funct_t) dl3, (funct_t) test_dl3, 1,
    "! ~ & ^ | + << >>", 12, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl4", (funct_t) dl4, (funct_t) test_dl4, 1,
    "! ~ & ^ | + << >>", 12, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl5", (funct_t) dl5, (funct_t) test_dl5, 1,
    "! ~ &  | + << >>", 10, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl6", (funct_t) dl6, (funct_t) test_dl6, 1,
    "! & | >>", 10, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl7", (funct_t) dl7, (funct_t) test_dl7, 1,
    "~ & ^ | + << >>", 10, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl8", (funct_t) dl8, (funct_t) test_dl8, 2, "| ~", 8, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dl9", (funct_t) dl9, (funct_t) test_dl9, 1, "& | + << >>", 38, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
  {"", NULL, NULL, 0, "", 0, 0,
   {{0, 0},{0,0},{0,0}}}
};
