// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/preprocessing/prevent_macro_expansion.hpp"
#include <limits>

namespace breath {

template< typename Int>
counter< Int >::counter()
    :   m_count( 0 )
{
}

template< typename Int>
counter< Int >::counter( Int n )
    :   m_count( (BREATH_ASSERT( n >= 0 ), n) )
{
}

template< typename Int >
counter< Int > &
counter< Int >::operator ++() &
{
    BREATH_ASSERT( m_count < (std::numeric_limits< 
                                Int >::max BREATH_PREVENT_MACRO_EXPANSION) () ) ;
    ++ m_count ;
    return *this ;
}

template< typename Int >
counter< Int >
counter< Int >::operator ++( int ) &
{
    auto const          temp( *this ) ;
    ++ *this ;
    return temp ;
}

template< typename Int >
counter< Int > &
counter< Int >::operator --() &
{
    BREATH_ASSERT( m_count > 0 ) ;
    -- m_count ;
    return *this ;
}

template< typename Int >
counter< Int >
counter< Int >::operator --( int ) &
{
    auto const          temp( *this ) ;
    -- *this ;
    return temp ;
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
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
