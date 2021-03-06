// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/stream/stream_equivalent.hpp"
#include "breeze/testing/testing.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <locale>
#include <ostream>
#include <sstream>

int                 test_stream_equivalent() ;

namespace {

void
check_good_streams()
{
    using breeze::stream_equivalent ;

    std::stringstream   str ;

    str.tie( &std::cout ) ;
    str.imbue( std::locale::classic() ) ;
    str.exceptions( std::ios_base::badbit ) ;

    {
        stream_equivalent< std::stringstream >
                            equiv( str ) ;
        std::iostream &     dest = equiv.get() ;

        dest.setf( std::ios_base::hex, std::ios_base::basefield ) ;
        dest.fill( '0' ) ;
        dest << std::setw( 2 ) << 15 ;
        BREEZE_CHECK( str.str() == "0f" ) ;
    }

    BREEZE_CHECK( str.rdstate() == std::ios_base::goodbit ) ;

    BREEZE_CHECK( ( str.flags() & std::ios::hex ) == 0 ) ;
    BREEZE_CHECK( str.fill() == ' ' ) ;
    BREEZE_CHECK( str.width() == 0 ) ;

    BREEZE_CHECK( str.tie() == &std::cout ) ;
    BREEZE_CHECK( str.getloc() == std::locale::classic() ) ;
    BREEZE_CHECK( str.exceptions() == std::ios_base::badbit ) ;
}

void
check_non_good_streams()
{
    using breeze::stream_equivalent ;

    std::fstream        fs ;
    fs.clear( std::ios_base::failbit ) ;

    fs.tie( &std::cout ) ;
    fs.imbue( std::locale::classic() ) ;
    try {
        fs.exceptions( std::ios_base::failbit ) ;
    } catch ( std::ios_base::failure & ) {
    }

    {
        stream_equivalent< std::fstream >
                            equiv( fs ) ;
        std::iostream &     dest = equiv.get() ;

        fs.clear( std::ios_base::eofbit ) ;

        dest.setf( std::ios_base::hex, std::ios_base::basefield ) ;
        dest.fill( '*' ) ;
        int const           dummy_not_actually_output = 1 ;
        dest << std::setw( 256 ) << dummy_not_actually_output ;
        BREEZE_CHECK( dest.width() == 256 ) ;
    }

    BREEZE_CHECK( fs.rdstate() == ( std::ios_base::failbit |
                                    std::ios_base::eofbit    ) ) ;

    BREEZE_CHECK( ( fs.flags() & std::ios_base::hex ) == 0 ) ;
    BREEZE_CHECK( fs.fill() == ' ' ) ;
    BREEZE_CHECK( fs.width() == 0 ) ;

    BREEZE_CHECK( fs.tie() == &std::cout ) ;
    BREEZE_CHECK( fs.getloc() == std::locale::classic() ) ;
    BREEZE_CHECK( fs.exceptions() == std::ios_base::failbit ) ;
}

void
check_input_or_output_only_streams()
{
    using breeze::stream_equivalent ;

    std::istream        is( std::cin.rdbuf() ) ;
    {
        stream_equivalent< std::istream >
                            equiv( is ) ;
        std::iostream const &
                            dest = equiv.get() ;
        static_cast< void >( dest ) ;
    }

    std::ostream        os( std::cout.rdbuf() ) ;
    {
        stream_equivalent< std::ostream >
                            equiv( os ) ;
        std::iostream const &
                            dest = equiv.get() ;
        static_cast< void >( dest ) ;
    }
}

}

int
test_stream_equivalent()
{
    return breeze::test_runner::instance().run(
        "stream_equivalent",
        { check_good_streams,
          check_non_good_streams,
          check_input_or_output_only_streams } ) ;
}
