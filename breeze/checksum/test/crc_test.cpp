// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2016-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/checksum/crc.hpp"
#include "breeze/mathematics/ceiling_of_quotient.hpp"
#include "breeze/testing/testing.hpp"
#include <climits>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

int                 test_crc() ;

namespace {

//      Returns the value of t. Useful when T is a character type, to
//      output t as a number, not as a character.
// ---------------------------------------------------------------------------
template< typename T >
auto as_number( T t ) -> decltype( + t )
{
    return t ;
}

//      crc12_umts:
//      ===========
//
//      Traits for CRC-12/UMTS (aka CRC-12/3GPP).
//
//      This is an academic CRC created in 2009.
//
//      I didn't feel like exposing its traits in crc.hpp, but it allows
//      testing our implementation for the unusual case reflect_in =
//      false and reflect_out = true (the opposite of invented_crc, used
//      below).
// ---------------------------------------------------------------------------
struct crc12_umts
{
    typedef std::uint16_t   value_type ;

    static int        const width       = 12    ;
    static value_type const poly        = 0x80F ;
    static value_type const init        = 0     ;
    static bool       const reflect_in  = false ;
    static bool       const reflect_out = true  ;
    static value_type const xor_out     = 0     ;

    static value_type const check       = 0xDAF ;
} ;

//      invented_crc:
//      =============
//
//      Since (AFAIK) there's no CRC in actual use which has reflect_in
//      = true and reflect_out = false, we make up these parameters, in
//      order to test the implementation.
//
//      The result has been verified with:
//
//        <http://zorc.breitbandkatze.de/crc.html>;
//
//      this should be taken with a grain of salt, but the fact that two
//      independent implementations get the same results is a good sign.
// -----------------------------------------------------------------------
struct invented_crc
{
    typedef unsigned        value_type ;

    static int        const width       = 13     ;
    static value_type const poly        = 0xABD  ;
    static value_type const init        = 0x16EF ;
    static bool       const reflect_in  = true   ;
    static bool       const reflect_out = false  ;
    static value_type const xor_out     = 0x123  ;

    static value_type const check       = 0x197C ;
} ;

//      TODO: in theory, this test should be doable at compile time,
//      with a static_assert in the code of crc< Traits >; but that
//      isn't particularly easy to do (or I'm missing something
//      obvious).
// ---------------------------------------------------------------------------
template< typename CrcTraits >
void
check_value_from_traits()
{
    char const          input[] = "123456789" ;
    int  const          len     = sizeof input - 1 ;

    BREEZE_CHECK( breeze::crc< CrcTraits >( input, input + len ).value() ==
        CrcTraits::check ) ;

    //      Now check in multiple steps.
    // -----------------------------------------------------------------------
    int const           step1_len = len / 2 ;
    breeze::crc< CrcTraits >
                        crc ;
    crc.accumulate( input, input + step1_len ) ;
    crc.accumulate( input + step1_len, input + len - 1 ) ;
    crc.accumulate( input[ len - 1 ] ) ;
    BREEZE_CHECK( crc.value() == CrcTraits::check ) ;

    //      Also check with iterators that are not to bytes.
    // -----------------------------------------------------------------------
    std::vector< int > const
                        int_input( input, input + len ) ;

    BREEZE_CHECK(
        breeze::crc< CrcTraits >( int_input.cbegin(), int_input.cend() ).value()
            == CrcTraits::check ) ;

    //      And, for the moment, also make a simple stream insertion
    //      test, until we figure out a clean way to test the stream
    //      inserter with various formatting flags.
    // -----------------------------------------------------------------------
    std::ostringstream  oss ;
    oss << crc ;
    std::string const   output = oss.str() ;

    oss.str( "" ) ;
    oss.fill( '0' ) ;
    oss.setf( std::ios::uppercase ) ;
    oss.setf( std::ios::hex, std::ios::basefield ) ;
    int const           digit_count =
        breeze::ceiling_of_quotient( CrcTraits::width, 4 ) ;
    oss << std::setw( digit_count ) << as_number( crc.value() ) ;

    std::string const   expected = oss.str() ;

    BREEZE_CHECK( output == expected ) ;
}

void
check_known_crc8_autosars()
{
    struct
    {
        std::string         text ;
        unsigned long       crc32 ;
    } const             known[] =
    {
        //      Following test vectors verified with:
        //
        //        <https://sourceforge.net/projects/crccheck/>.
        //
        //      Like for invented_crc (see above), take this with a
        //      grain of salt.
        // -------------------------------------------------------------------
        { "",                                                 0    },
        { "Just a test",                                      0x34 },
        { "A single man in the possession of a good fortune", 0x60 },
        { "Quel ramo del lago di Como",                       0xC1 }
    } ;

    for ( auto const & k : known ) {
        BREEZE_CHECK( breeze::crc< breeze::crc8_autosar >(
            k.text.cbegin(), k.text.cend() ).value() == k.crc32 ) ;
    }
}

void
check_known_crc8_bluetooths()
{
    struct
    {
        std::string         text ;
        unsigned long       crc32 ;
    } const             known[] =
    {
        //      Following test vectors verified with:
        //
        //        <https://sourceforge.net/projects/crccheck/>.
        //
        //      Like for invented_crc (see above), take this with a
        //      grain of salt.
        // -------------------------------------------------------------------
        { "",                                                 0    },
        { "Just a test",                                      0x62 },
        { "A single man in the possession of a good fortune", 0x59 },
        { "Quel ramo del lago di Como",                       0x79 }
    } ;

    for ( auto const & k : known ) {
        BREEZE_CHECK( breeze::crc< breeze::crc8_bluetooth >(
            k.text.cbegin(), k.text.cend() ).value() == k.crc32 ) ;
    }
}

void
check_known_crc32s()
{
    struct
    {
        std::string         text ;
        unsigned long       crc32 ;
    } const             known[] =
    {
        { "",                                            0          },

        //      Following test vectors verified with:
        //
        //        <https://www.lammertbies.nl/comm/info/crc-calculation.html>.
        //
        //      Like for invented_crc (see above), take this addito
        //      salis grano.
        // -------------------------------------------------------------------
        { "The quick brown fox jumps over the lazy dog", 0x414FA339 },
        { "breeze",                                      0xDD00B60C },
        { " ",                                           0xE96CCF45 },
        { "A",                                           0xD3D99E8B },
        { "ABC",                                         0xA3830348 },
        { "Nel mezzo del cammin di nostra vita",         0x5BFBCBF8 }
    } ;

    for ( auto const & k : known ) {
        BREEZE_CHECK( breeze::crc< breeze::crc32 >(
            k.text.cbegin(), k.text.cend() ).value() == k.crc32 ) ;
    }
}

void
out_of_range_values_cannot_be_accumulated()
{
    breeze::crc< breeze::crc32 >
                        crc ;

    {
        std::vector< int > const
                            v = { 0, UCHAR_MAX + 1 } ;
        BREEZE_CHECK_THROWS( breeze::assert_failure,
            crc.accumulate( v.cbegin(), v.cend() ) ) ;
    }
    {
        std::vector< int > const
                            v = { -1, 0 } ;
        BREEZE_CHECK_THROWS( breeze::assert_failure,
            crc.accumulate( v.cbegin(), v.cend() ) ) ;
    }
}

}

int
test_crc()
{
    return breeze::test_runner::instance().run(
        "crc",
        { check_value_from_traits< breeze::crc16 >,
          check_value_from_traits< breeze::crc32 >,
          check_value_from_traits< breeze::crc16_ibm3740 >,
          check_value_from_traits< breeze::crc8_autosar >,
          check_value_from_traits< breeze::crc8_bluetooth >,
          check_value_from_traits< crc12_umts >,
          check_value_from_traits< invented_crc >,
          check_known_crc8_autosars,
          check_known_crc8_bluetooths,
          check_known_crc32s,
          out_of_range_values_cannot_be_accumulated } ) ;
}
