// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "private/gcd_lcm_common.hpp"
#include "breeze/preprocessing/prevent_macro_expansion.hpp"
#include <limits>
#include <type_traits>

namespace breeze_ns {

template< typename T >
constexpr T
gcd( T a, T b )
{
    static_assert( std::is_integral< T >::value, "T must be integral" ) ;
    using gcd_lcm_private::absolute_value ;

    T const             min = std::numeric_limits< T >::min
                            BREEZE_PREVENT_MACRO_EXPANSION () ;

    if ( a < 0 && b < 0 && (
                ( a == min && b == -1  ) ||
                ( a == -1  && b == min )
            )
       )
    {
        return 1 ;
    }

    while ( true ) {

        if ( a == 0 ) {
            return absolute_value( b ) ;
        }
        b %= a ;

        if ( b == 0 ) {
            return absolute_value( a ) ;
        }
        a %= b ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
