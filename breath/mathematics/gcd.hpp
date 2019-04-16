// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The greatest common divisor of two integers.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_7TolwuFfch2xrqOdKkP8IrjIejdJYQxs
#define BREATH_GUARD_7TolwuFfch2xrqOdKkP8IrjIejdJYQxs

#include <type_traits>

namespace breath {

//      gcd():
//      ======
//
//!     This function follows the C++ Library Fundamental TS v2, as of
//!     May 14, 2016. (It adds, as allowed, a noexcept specification.)
//!
//!     If either \c M or \c N is not an integral type the program is
//!     ill-formed. If |m| is not representable as a value of type M
//!     or |n| is not representable as a value of type N, the behavior
//!     is undefined.
//!
//!     \return
//!         If both \c m and \c n are zero, returns zero. Otherwise it
//!         returns the greatest common divisor of |m| and |n|.
// -------------------------------------------------------------------------
template< typename M, typename N >
constexpr std::common_type_t< M, N >
                    gcd( M m, N n ) noexcept ;

}

#include "brt/gcd.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
