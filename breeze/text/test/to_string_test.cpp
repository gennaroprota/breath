// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/to_string.hpp"
#include "breeze/testing/testing.hpp"

int                 test_to_string() ;

namespace {

void do_tests()
{
    BREEZE_CHECK( breeze::to_string( 12 ) == "12" ) ;
    BREEZE_CHECK( breeze::to_string( " hello, world " ) == " hello, world " ) ;
    BREEZE_CHECK( breeze::to_string( "" ) == "" ) ;
    BREEZE_CHECK( breeze::to_string( 'a' ) == "a" ) ;

    //      Conversion from double. Note that these are not the same
    //      results as std::to_string().
    // -----------------------------------------------------------------------
    BREEZE_CHECK( breeze::to_string( 12.34 ) == "12.34" ) ;
    BREEZE_CHECK( breeze::to_string( 1e-10 ) == "1e-10" ) ;
    BREEZE_CHECK( breeze::to_string( 1e+50 ) == "1e+50" ) ;
    BREEZE_CHECK( breeze::to_string( 1e-50 ) == "1e-50" ) ;
    BREEZE_CHECK( breeze::to_string( 123456789.0 ) == "1.23457e+08" ) ;
}

}

int
test_to_string()
{
    return breeze::test_runner::instance().run( "to_string()", { do_tests } ) ;
}
