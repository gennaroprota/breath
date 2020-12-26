// ===========================================================================
//                     Copyright 2016-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Tells if an integer is a power of two.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_33316YlRoQ2LToi0iu44YByR2XFvlCOy
#define BREEZE_GUARD_33316YlRoQ2LToi0iu44YByR2XFvlCOy

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      is_power_of_2():
//      ================
//
//!     \return
//!         \c true if an only if \c x is a power of two.
//!
//!     \note
//!         C++20 has \c std::has_single_bit(), which can replace this
//!         one (but only works with unsigned types and, on most
//!         implementations, qualified versions thereof).
// ---------------------------------------------------------------------------
template< typename T >
constexpr bool      is_power_of_2( T x ) noexcept ;

}

#include "brz/is_power_of_2.tpp"
#endif
