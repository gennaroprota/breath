// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"
#include "breeze/preprocessing/prevent_macro_expansion.hpp"
#include <limits>

namespace breeze_ns {

template< typename Int>
counter< Int >::counter( Int n )
    :   m_count( ( BREEZE_ASSERT( n >= 0 ), n ) )
{
}

template< typename Int >
counter< Int > &
counter< Int >::operator ++() &
{
    BREEZE_ASSERT( m_count < (std::numeric_limits<
                               Int >::max BREEZE_PREVENT_MACRO_EXPANSION) () ) ;
    ++ m_count ;
    return *this ;
}

template< typename Int >
counter< Int >
counter< Int >::operator ++( int ) &
{
    counter             result( *this ) ;
    operator ++() ;
    return result ;
}

template< typename Int >
counter< Int > &
counter< Int >::operator --() &
{
    BREEZE_ASSERT( m_count > 0 ) ;
    -- m_count ;
    return *this ;
}

template< typename Int >
counter< Int >
counter< Int >::operator --( int ) &
{
    counter             result( *this ) ;
    operator --() ;
    return result ;
}

template< typename Int >
bool
counter< Int >::is_equal( counter< Int > const & other ) const
{
    return m_count == other.m_count ;
}

template< typename Int >
int
counter< Int >::compare( counter< Int > const & other ) const
{
    return m_count < other.m_count
               ? -1
               : m_count == other.m_count
                   ? 0
                   : 1
               ;
}

template< typename Int >
Int
counter< Int >::value() const
{
    return m_count ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
