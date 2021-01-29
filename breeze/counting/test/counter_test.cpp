// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/counting/counter.hpp"
#include "breeze/testing/testing.hpp"
#include <limits>

int                 test_counter() ;

namespace {

template< typename T >
void
do_check()
{
    using breeze::counter ;

    {
        counter< T >        c( 0 ) ;
        BREEZE_CHECK( c.value() == 0 ) ;

        ++ c ;
        BREEZE_CHECK( c.value() == 1 ) ;

        -- c ;
        BREEZE_CHECK( c.value() == 0 ) ;

        c = counter< T >( 15 ) ;
        BREEZE_CHECK( c.value() == 15 ) ;
    }

    {
        T const             max = std::numeric_limits< T >::max() ;
        counter< T >        c( max ) ;
        -- c ;
        BREEZE_CHECK( c.value() == ( max - 1 ) ) ;
        ++ c ;
        BREEZE_CHECK( c.value() == max ) ;
    }

    {
        counter< T >        c( 100 ) ;

        counter< T > const  old = c ++ ;
        BREEZE_CHECK( old.value() == 100 ) ;
        BREEZE_CHECK( c.value() == 101 ) ;
    }

    {
        counter< T >        c( 100 ) ;

        counter< T > const  old = c -- ;
        BREEZE_CHECK( old.value() == 100 ) ;
        BREEZE_CHECK( c.value() == 99 ) ;
    }

    {
        counter< T > const  c1( 1 ) ;
        counter< T > const  c2( 2 ) ;

        BREEZE_CHECK( c1 < c2 ) ;
        BREEZE_CHECK( c2 > c1 ) ;

        counter< T > const  copy( c1 ) ;
        BREEZE_CHECK( copy == c1 ) ;
        BREEZE_CHECK( copy <  c2 ) ;
        BREEZE_CHECK( c2 > copy ) ;
    }
}

void
counter_checks_for_errors()
{
    {
        BREEZE_CHECK_THROWS( breeze::assert_failure,
            breeze::counter< int >( -1 ) ) ;
    }

    {
        breeze::counter< int >
                            min( 0 ) ;
        BREEZE_CHECK_THROWS( breeze::assert_failure, -- min ) ;
    }

    {
        int const           int_max = std::numeric_limits< int >::max() ;
        breeze::counter< int >
                            max( int_max ) ;
        BREEZE_CHECK_THROWS( breeze::assert_failure, ++ max ) ;
    }
}

}

int
test_counter()
{
    return breeze::test_runner::instance().run(
        "counter",
        { do_check< signed char >,
          do_check< unsigned char >,
          do_check< int >,
          do_check< unsigned int >,

          counter_checks_for_errors } ) ;
}


