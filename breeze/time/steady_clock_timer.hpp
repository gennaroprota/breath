// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A timer using `std::chrono::steady_clock`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_nLtyKWctWF4nTnEMJ4Y66pLLeGE7RNze
#define BREEZE_GUARD_nLtyKWctWF4nTnEMJ4Y66pLLeGE7RNze

#include "breeze/top_level_namespace.hpp"
#include "breeze/time/timer.hpp"
#include <chrono>

namespace breeze_ns {

//      steady_clock_policy:
//      ====================
//
//!     \brief A policy for our `timer` template using
//!            `std::chrono::steady_clock`.
//!
//!     \note
//!         This policy does not provide the `resolution()` member.
// ---------------------------------------------------------------------------
class steady_clock_policy
{
public:
    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        steady_clock_policy( steady_clock_policy const & ) =
                                                                        delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    steady_clock_policy &
                        operator =(          steady_clock_policy const & ) =
                                                                        delete ;

    //!     A typedef for `std::chrono::steady_clock::duration`.
    // -----------------------------------------------------------------------
    typedef std::chrono::steady_clock::duration
                        duration_type ;

    //!     Leaves this object in an undefined state. The only action
    //!     that can be performed on a just constructed policy object is
    //!     to call start().
    //!
    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
                        steady_clock_policy() ;

    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    void                start() noexcept ;

    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const noexcept ;

private:
    std::chrono::steady_clock::time_point
                        m_start_time ;
} ;

typedef timer< steady_clock_policy >
                        steady_clock_timer ;

}

#endif
