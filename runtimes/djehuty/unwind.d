/*
 * unwind.d
 *
 * This module implements the D runtime unwind functions which serve to
 * process exceptions and backtraces.
 *
 */

module runtime.unwind;

import runtime.common;

extern(C):

void _d_throw(Object obj) {
}

