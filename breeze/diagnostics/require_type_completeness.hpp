// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Ensures that a type is complete at the point of
//!            instantiation.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_zosglTB4b62CILKxpxWmmQwQ28EfOH6T
#define BREEZE_GUARD_zosglTB4b62CILKxpxWmmQwQ28EfOH6T

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      require_type_completeness():
//      ============================
//
//!     To be used to ensure that \c T is a complete type at the point
//!     of instantiation. If \c T is incomplete then the expression
//!
//!     \code
//!         require_type_completeness< T >()
//!     \endcode
//!
//!     renders the program \e ill-formed.
//!
//!     This template has a \c noexcept specifier so that it can be used
//!     in other \c noexcept functions (typically, destructors), without
//!     warnings from compilers and static analyzers.
// ---------------------------------------------------------------------------
template< typename T >
void
require_type_completeness() noexcept
{
    static_cast< void >( sizeof( T ) ) ;
}

}

#endif
