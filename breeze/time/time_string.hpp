// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A thin wrapper around \c std::strftime(), plus some
//!            predefined format strings.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_wR9yYhDtICLHOJ6c2LmBkhMWoYoaeVkS
#define BREEZE_GUARD_wR9yYhDtICLHOJ6c2LmBkhMWoYoaeVkS

#include "breeze/top_level_namespace.hpp"
#include "breeze/vocabulary/maybe.hpp"
#include <string>

namespace breeze_ns {

//      Predefined format strings:
//      ==========================
//
//!     These variables allow using meaningful names in combination with
//!     \c time_string(); e.g. you can write
//!
//!     \code
//!         time_string( iso8601_extended_date ) ;
//!     \endcode
//!
//!     Only a small number of format strings are provided.
//!
//!     \note
//!         These are not <code>std::string</code>s, to avoid any order
//!         of initialization issues. But this means that e.g.
//!         concatening their values may be a bit less straightforward.
// ---------------------------------------------------------------------------

//!     Gives a calendar date in the format \c YYYYMMDD.
// ---------------------------------------------------------------------------
extern char const   iso8601_basic_date[] ;

//!     Gives a calendar date in the format \c YYYY-MM-DD.
// ---------------------------------------------------------------------------
extern char const   iso8601_extended_date[] ;

//!     Gives a time of the day in the format \c hhmmss.
// ---------------------------------------------------------------------------
extern char const   iso8601_basic_time[] ;

//!     Gives a time of the day in the format \c hh:mm:ss.
// ---------------------------------------------------------------------------
extern char const   iso8601_extended_time[] ;


//      time_string_zone:
//      =================
//
//!     \brief
//!         The type of timezone (UTC/local) in which the time must be
//!         represented by time_string().
// ---------------------------------------------------------------------------
class time_string_zone
{
public:
    enum zone
    {
        utc,
        local
    } ;

} ;


//      time_string():
//      ==============
//
//!     \return
//!         The current (date or) time formatted according to \c format,
//!         interpreted as if passed to the \c strftime() standard
//!         function. See also: time_string_zone.
//!
//!     This is a simple tool for simple and quick formatting needs.
//!     You should use a more complete solution for more complex needs
//!     (but don't underestimate the good old \c strftime() ;-)).
//!
//!     NOTE:
//!         this function is thread-safe and reentrant.
// ---------------------------------------------------------------------------
maybe< std::string >
                    time_string( std::string const & format,
                                 time_string_zone::zone =
                                                    time_string_zone::utc ) ;

}

#endif
