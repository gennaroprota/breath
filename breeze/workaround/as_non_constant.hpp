// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Makes an expression non-constant.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_X1oIFdvnzv4TfQy0Ool638J3eUJJRKJ3
#define BREEZE_GUARD_X1oIFdvnzv4TfQy0Ool638J3eUJJRKJ3

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      as_non_constant():
//      ==================
//
//!     \copybrief as_non_constant.hpp
//!
//!     Just returns a copy of \c value.
//!
//!     Used to workaround warnings from compilers or static analyzers,
//!     for instance Visual Studio /analyze warnings C6286 and C6326.
//!
//!     \return
//!         value
// ---------------------------------------------------------------------------
template< typename T >
T                   as_non_constant( T value ) ;

}

#include "brz/as_non_constant.tpp"
#endif
