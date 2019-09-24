// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include "breath/counting/count.hpp"
#include <climits>
#include <cstddef>
#include <type_traits>

namespace breath {

template< typename InputIter, typename OutputIter >
void
base64_to_binary( InputIter begin, InputIter end, OutputIter out )
{
    //      Table generated by 'generate_inverse_base64_table': see the
    //      extra/ subdirectory.
    // -----------------------------------------------------------------------
    static int const    table[] =
    {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
        -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
        -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    } ;

    static_assert( ( UCHAR_MAX == count( table ) - 1 ) &&
       ( std::is_same< typename InputIter::value_type, char >::value
      || std::is_same< typename InputIter::value_type, unsigned char >::value ),
                   "" ) ;
    static char const   error_message[] = "invalid input to base64_to_binary()" ;
    int const           not_to_be_translated = -1 ;
    unsigned            block = 0 ;
    std::size_t         num_bits = 0 ;
    int const           block_length = 6 ;
    int const           char_bit = CHAR_BIT ;
    bool                equals_seen = false ;
    for ( InputIter curr( begin ) ; curr != end ; ++ curr ) {
        auto                x = static_cast< unsigned char >( *curr ) ;
        auto                value = table[ x ] ;

        //      Once we've seen an equal sign, only equal signs and
        //      newlines can follow; otherwise the input is ill-formed.
        // -------------------------------------------------------------------
        if ( x == '=' ) {
            equals_seen = true ;
        }
        if ( x != '=' && x != '\n' && equals_seen ) {
            throw exception( error_message ) ;
        }
        if ( value == not_to_be_translated ) {
            if ( x != '\n' && x != '=' ) {
                throw exception( error_message ) ;
            }
        } else {
            block = ( block << block_length ) | value ;
            num_bits += block_length ;
            if ( num_bits >= char_bit ) {
                num_bits -= char_bit ;
                *out ++ = static_cast< unsigned char>( block >> num_bits ) ;
                block &= ( ( 1 << num_bits ) - 1 ) ;
            }

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
