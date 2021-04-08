// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Typedefs for built-in integer types of user-specified
//!            width.
//!
//!     As for the various `std::[u]intN_t` from `<cstdint>`, there's no
//!     guarantee that the typedefs are provided for any given width.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4
#define BREEZE_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/select.hpp"
#include "breeze/meta/width.hpp"

namespace breeze_ns {

//!\cond implementation
namespace integer_by_width_private {

//      This could be elegantly implemented via type lists or maps, but
//      we chose to keep metaprogramming (and dependencies) to a
//      minimum.
// ---------------------------------------------------------------------------
template< typename IntType, int index > struct types ;

//      "List" of unsigned types.
//
template<> struct types< unsigned, 0 > { typedef unsigned char      type ; } ;
template<> struct types< unsigned, 1 > { typedef unsigned short     type ; } ;
template<> struct types< unsigned, 2 > { typedef unsigned int       type ; } ;
template<> struct types< unsigned, 3 > { typedef unsigned long      type ; } ;
template<> struct types< unsigned, 4 > { typedef unsigned long long type ; } ;

//      "List" of signed types.
//
template<> struct types< signed,   0 > { typedef signed char        type ; } ;
template<> struct types< signed,   1 > { typedef signed short       type ; } ;
template<> struct types< signed,   2 > { typedef signed int         type ; } ;
template<> struct types< signed,   3 > { typedef signed long        type ; } ;
template<> struct types< signed,   4 > { typedef signed long long   type ; } ;

template< int width,
          typename IntType,
          int n >
class selector
{
    typedef types< IntType, n > candidate ;
    enum { found = breeze::width< typename candidate::type >::value == width } ;

public:
    typedef typename select_< found,
                              candidate,
                              selector< width, IntType, 1 + n >
                            >::type s ;

    typedef typename s::type type ;
} ;

}
//!\endcond

//      integer_by_width:
//      =================
//
//!     \brief
//!         Provides, if possible, a typedef to a built-in integer type
//!         with width `width`.
//!
//!     If a (signed or unsigned, according to `T`) type with width
//!     `width` is available, a public member typedef `type` is provided
//!     that names that type; otherwise, the program is ill-formed.
//!
//!     Differently from `std::[u]intN_t`, the named type may have
//!     padding; until C++20, it may also use a representation different
//!     from two's complement (if it allows negative values at all).
//!
//!     \par Type requirements
//!         `T` shall be either `signed int` or `unsigned int`.
// ---------------------------------------------------------------------------
template< int width, typename T >
class integer_by_width
{
public:
    typedef typename integer_by_width_private
                         ::selector< width, T, 0 >::type type ;
} ;

//      signed_integer_by_width:
//      ========================
//
//!     \brief
//!         Equivalent to `integer_by_width< width, signed >`.
// ---------------------------------------------------------------------------
template< int width >
class signed_integer_by_width
{
public:
    typedef typename integer_by_width< width, signed >::type
                        type ;
} ;

//      unsigned_integer_by_width:
//      ==========================
//
//!     \brief
//!         Equivalent to `integer_by_width< width, unsigned >`.
// ---------------------------------------------------------------------------
template< int width >
class unsigned_integer_by_width
{
public:
    typedef typename integer_by_width< width, unsigned >::type
                        type ;
} ;

}

#endif
