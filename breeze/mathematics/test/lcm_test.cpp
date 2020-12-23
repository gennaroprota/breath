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

#include "breeze/mathematics/lcm.hpp"
#include "breeze/testing/testing.hpp"

int                 test_lcm() ;

namespace {

void
check_int()
{
    struct
    {
        int a ;
        int b ;
        int lcm ;
    } const             table[] = {
        {  0,  0,  0 },
        { -1,  0,  0 },
        { -3,  0,  0 },
        {  18, 24, 72 },
        { -12, 10, 60 },
        {  12,-10, 60 },
        { -12,-10, 60 },
        { 23 * 5, 12 * 5, 23 * 12 * 5 },
        { 31 * 7, 7 * 2,  31 * 7 * 2 }
    } ;

    for ( auto const & t : table ) {
        BREEZE_CHECK( breeze::lcm( t.a, t.b ) == t.lcm ) ;
        BREEZE_CHECK( breeze::lcm( t.b, t.a ) == t.lcm ) ;
    }
}

void
check_mixed_types()
{
    {
        signed char const   a = -80 ;
        unsigned int const  b = 32768 ;

        BREEZE_CHECK( breeze::lcm( a, b ) == 163840 ) ;
        BREEZE_CHECK( breeze::lcm( b, a ) == 163840 ) ;
    }
}

void
check_constexpr()
{
    constexpr int       n = breeze::lcm( 10, 14 ) ;
    int                 array[ n ] = {} ;
    static_cast< void >( array ) ;
}

}

int
test_lcm()
{
    using namespace breeze ;

    return test_runner::instance().run( "lcm()", { check_int,
                                                   check_mixed_types,
                                                   check_constexpr } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
