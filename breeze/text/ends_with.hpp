// ===========================================================================
//                     Copyright 2013-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns whether a string ends with another one.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_FXhivw6tI6cV0C3govXyzZBmNCWa1e2o
#define BREEZE_GUARD_FXhivw6tI6cV0C3govXyzZBmNCWa1e2o

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//!     \return
//!         Whether \c str ends with \c with. If \c with is empty, the
//!         result is always \c true.
//!
//!     \note
//!         [FUTURE] C++20 will have
//!           <code>std::basic_string::ends_with()</code> and
//!           <code>std::basic_string_view::ends_with()</code>
//!         for this.
//!
//!     \see
//!         begins_with()
// ---------------------------------------------------------------------------
bool                ends_with( std::string const & str,
                               std::string const & with ) noexcept ;

}

#endif
