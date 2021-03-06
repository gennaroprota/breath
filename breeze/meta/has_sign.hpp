// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns whether a type accepts negative values.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_hGv2WKy8LgUcETfMmcRpTRLRUQlhUJSH
#define BREEZE_GUARD_hGv2WKy8LgUcETfMmcRpTRLRUQlhUJSH

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/constant.hpp"
#include "breeze/meta/unqualify.hpp"

namespace breeze_ns {

//      has_sign:
//      =========
//
//!\brief
//!     A `constant` yielding whether a type allows negative values.
// ---------------------------------------------------------------------------
template< typename T >
class has_sign
    //      The natural form here would be "T( -1 ) < 0"; but GCC, and
    //      possibly other compilers, would warn when instantiating the
    //      template with T being an unsigned type. Of course it also
    //      warns if using "!( T( -1 ) >= 0 )".
    //
    //      The use of unqualify is also to avoid a warning: MSVC's
    //      C4197.
    // -----------------------------------------------------------------------
    :   public constant< bool, ! ( typename unqualify< T >::type( -1 ) > 0 ) >
{
} ;

//!\cond implementation
//
//      The specialization here is logically unnecessary but silences
//      compiler warnings.
// ---------------------------------------------------------------------------
template<>
class has_sign< bool >
    :   public constant< bool, false >
{
} ;
//!\endcond

}

#endif
