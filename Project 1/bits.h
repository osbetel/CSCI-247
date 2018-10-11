/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
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
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
int dl10(int, int);
int test_dl10(int, int);
int dl11(int, int);
int test_dl11(int, int);
int dl12(int, int);
int test_dl12(int, int);
int dl13(int);
int test_dl13(int);
int dl14(int, int);
int test_dl14(int, int);
int dl15(int, int, int);
int test_dl15(int, int, int);
int dl16(int, int, int);
int test_dl16(int, int, int);
int dl17(int);
int test_dl17(int);
int dl18(int, int);
int test_dl18(int, int);
int dl19();
int test_dl19();
int dl1(int);
int test_dl1(int);
int dl20(int);
int test_dl20(int);
unsigned dl21(unsigned);
unsigned test_dl21(unsigned);
unsigned dl22(int);
unsigned test_dl22(int);
unsigned dl23(unsigned);
unsigned test_dl23(unsigned);
int dl24(int);
int test_dl24(int);
int dl2(int, int);
int test_dl2(int, int);
int dl3();
int test_dl3();
int dl4();
int test_dl4();
int dl5();
int test_dl5();
int dl6();
int test_dl6();
int dl7(int);
int test_dl7(int);
int dl8(int, int);
int test_dl8(int, int);
int dl9(int);
int test_dl9(int);
