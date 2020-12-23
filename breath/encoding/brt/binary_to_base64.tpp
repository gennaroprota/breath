// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/counting/signed_count.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/mathematics/integer_log2.hpp"
#include "breath/mathematics/is_power_of_2.hpp"
#include "breath/mathematics/lcm.hpp"
#include "breath/mathematics/rounded_up_quotient.hpp"
#include <climits>
#include <type_traits>

namespace breath_ns {

template< typename InputIter, typename OutputIter >
void
binary_to_base64( InputIter begin, InputIter end,
                  OutputIter out, int wrap_column )
{
    static_assert( CHAR_BIT == 8 &&
       ( std::is_same< typename InputIter::value_type, char >::value
      || std::is_same< typename InputIter::value_type, unsigned char >::value ),
                   "" ) ;

    static char const   alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "0123456789+/" ;
    auto const          base = breath::signed_count( alphabet ) - 1 ;

    static_assert( breath::is_power_of_2( base ), "" ) ;

    int const           bits_per_output_char = breath::integer_log2( base ) ;
    int const           char_bit = CHAR_BIT ;
    int const           bits_per_quantum = breath::lcm( bits_per_output_char,
                                                        char_bit ) ;
    int const           bytes_per_quantum = bits_per_quantum / char_bit ;

    BREATH_ASSERT( wrap_column >= 0 ) ;

    int                 column = 0 ;

    auto                do_output = [ &out, &column, &wrap_column ]( char c )
    {
        *out = c ;
        ++ out ;
        ++ column ;
        if ( column == wrap_column ) {
            *out = '\n' ;
            ++ out ;
            column = 0 ;
        }
    } ;

    unsigned            accum = 0 ;
    int                 accum_bit_count = 0 ;
    auto                curr = begin ;
    int                 count = 0 ;

    while ( curr != end ) {
        accum = accum << char_bit | static_cast< unsigned char >( *curr ) ;
        accum_bit_count += char_bit ;
        ++ count ;
        count %= bytes_per_quantum ;

        while ( accum_bit_count >= bits_per_output_char ) {
            int const       next = accum_bit_count - bits_per_output_char ;
            auto            c = static_cast< unsigned char >( accum >> next ) ;
            do_output( alphabet[ c ] ) ;
            accum &= ( ( 1 << next ) - 1 ) ;
            accum_bit_count = next ;
        }

        ++ curr ;
    }

    if ( accum_bit_count != 0 ) {
        accum <<= ( bits_per_output_char - accum_bit_count ) ;
        do_output( alphabet[ accum ] ) ;
    }

    if ( count != 0 ) {
        int const           pad_count =
         bits_per_quantum / bits_per_output_char -
         breath::rounded_up_quotient( count * char_bit, bits_per_output_char ) ;
        for ( int i = 0 ; i < pad_count ; ++ i ) {
            do_output( '=' );
        }
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
