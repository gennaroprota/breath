// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Base class template to provide equality operators (`==`
//!            and `!=`) for a derived class.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_FVjQpxOUioJICCQIoTK5TmuA8UEe4UzI
#define BREEZE_GUARD_FVjQpxOUioJICCQIoTK5TmuA8UEe4UzI

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {
namespace adl_shield {

//      equality_comparison:
//      ====================
//
//!     \copybrief equality_comparison.hpp
//!
//!     The class template `equality_comparison` provides `operator
//!     ==()` and `operator !=()` as namespace-scope functions whose
//!     name is associated "on demand" (i.e. at instantiation) to class
//!     `T`, via ADL.
//!
//!     \par Usage
//!
//!      - Provide an %is_equal() function for your class `C`, as a \e
//!        public and \e const member function.
//!
//!      - Add `equality_comparison< C >` as a private base class of
//!        `C`.
//!
//!     As a result, `==` and `!=` will be available too for class `C`
//!     and defined in terms of is_equal().
//!
//!     \par ADL protection
//!
//!     Even though this uses the Barton-Nackman trick and relies on its
//!     standard-conforming, ADL-based, mechanics (no friend injection),
//!     it is protected from ADL in namespace `breeze` in a way which
//!     allows only the provided operator functions to be found.
//!
//!     This means that the user can safely derive their own type from
//!     any of its instantiations \e without risk of ADL picking up
//!     anything \e unintended in namespace `breeze`. Example:
//!
//!         Example TODO:
//!
//!     \par Naming rationale
//!
//!     The name of the class template indicates the kind of comparison
//!     that its target will support. This leads to a noun-based name
//!     (as opposed, for instance, to "equality_comparable"),
//!     consistently with the general naming style of the Breeze
//!     components.
// ---------------------------------------------------------------------------
template< typename T >
class equality_comparison
{
    // [FUTURE], [C++17], [gps]:
    //      These are all candidates for [[ nodiscard ]]
    //
    //!     \return
    //!         lhs.is_equal( rhs )
    // -----------------------------------------------------------------------
    friend bool         operator ==( T const & lhs, T const & rhs )
    {
        return lhs.is_equal( rhs ) ;
    }

    //!     \return
    //!         ! lhs.is_equal( rhs )
    // -----------------------------------------------------------------------
    friend bool         operator !=( T const & lhs, T const & rhs )
    {
        return ! lhs.is_equal( rhs ) ;
    }

protected:
    //!     Protected constructor, to enforce the usage as a base.
    //!
    //!     This used to be a protected destructor, but if a
    //!     user-declared destructor---even a defaulted one---exists,
    //!     the generation of a copy constructor is deprecated. Thus, we
    //!     switched to use a constructor, instead.
    // -----------------------------------------------------------------------
                        equality_comparison() noexcept = default ;
} ;

}

using breeze::adl_shield::
                    equality_comparison ;
}

#endif
