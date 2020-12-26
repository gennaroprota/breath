// ===========================================================================
//                     Copyright 2017-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns a human readable name for its type argument.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_e0aZnjL0UZmNVTa9XkUU1WypgFnHm24u
#define BREEZE_GUARD_e0aZnjL0UZmNVTa9XkUU1WypgFnHm24u

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      readable_type_name():
//      =====================
//
//!     \return
//!         A human readable name for the type \c T.
// ---------------------------------------------------------------------------
template< typename T >
std::string         readable_type_name() ;

//      readable_type_name():
//      =====================
//
//!     \return
//!         A human readable name for the type of the object to which \c
//!         ref refers. If \c T is a polymorphic class type, the name is
//!         that of the type of the most derived object (i.e. the \e
//!         dynamic type), otherwise it is that of the static type (i.e.
//!         the name of \c T).
// ---------------------------------------------------------------------------
template< typename T >
std::string         readable_type_name( T const & ref ) ;

}

#include "brz/readable_type_name.tpp"
#endif
