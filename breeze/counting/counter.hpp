// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A counter providing only operations meaningful for a
//!            counter, plus overflow and underflow checking.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_igDqQSfWTOavMKrliVx0QKSbOMZ1k4kD
#define BREEZE_GUARD_igDqQSfWTOavMKrliVx0QKSbOMZ1k4kD

#include "breeze/top_level_namespace.hpp"
#include "breeze/operator/comparison.hpp"

namespace breeze_ns {

//      counter:
//      ========
//
//!     \copybrief counter.hpp
// ---------------------------------------------------------------------------
template< typename IntegralType >
class counter
    :   private comparison< counter< IntegralType > >
{
public:
    //!     Constructs a counter having internal value \c
    //!     IntegralType( 0 ).
    // -----------------------------------------------------------------------
                        counter() ;

    //!     Constructs a counter with internal value \c n.
    //!
    //!     \pre
    //!         n >= 0
    // -----------------------------------------------------------------------
    explicit            counter( IntegralType n ) ;

    //!     Pre-increments the counter. Can only be called on lvalues.
    // -----------------------------------------------------------------------
    counter &           operator ++() & ;

    //!     Post-increments the counter. Can only be called on
    //!     lvalues.
    // -----------------------------------------------------------------------
    counter             operator ++( int ) & ;

    //!     Pre-decrements the counter. Can only be called on lvalues.
    // -----------------------------------------------------------------------
    counter &           operator --() & ;

    //!     Post-decrements the counter. Can only be called on
    //!     lvalues.
    // -----------------------------------------------------------------------
    counter             operator --( int ) & ;

    //!     \return
    //!         The internal value of the counter.
    // -----------------------------------------------------------------------
    IntegralType        value() const ;

    //!     \return
    //!         \c true if an only if \c *this and \c other compare
    //!         equal (same internal value). Used by the base class.
    // -----------------------------------------------------------------------
    bool                is_equal( counter const & other ) const ;

    //!     Three-way comparison for counters. Used by the base class.
    // -----------------------------------------------------------------------
    int                 compare(  counter const & other ) const ;

private:
    IntegralType        m_count ;
} ;

}

#include "brz/counter.tpp"
#endif
