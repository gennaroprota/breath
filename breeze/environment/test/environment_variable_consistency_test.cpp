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

#include "breeze/environment/get_environment_variable.hpp"
#include "breeze/environment/get_all_environment_variables.hpp"
#include "breeze/testing/testing.hpp"

int                 test_environment_variable_consistency() ;

namespace {

//      This isn't really a conclusive test: we can't know what
//      environment variables are defined on the system. But, at least,
//      we check that our two functions return consistent results.
// ---------------------------------------------------------------------------
void
check_consistency()
{
    std::map< std::string, std::string > const &
                        map = breeze::get_all_environment_variables() ;

    for ( auto const & from_map : map )
    {
        breeze::maybe< std::string > const
                            from_get_single = breeze::get_environment_variable(
                                                  from_map.first ) ;

        BREEZE_CHECK( from_get_single.is_valid() ) ;

        //      Give up on testing PATH, because, under Cygwin, the
        //      paths may be Windows-style or Unix-style according to
        //      whether we use get_all_enviroment_variables() or
        //      get_environment_variable().
        // -------------------------------------------------------------------
        if ( from_map.first != "PATH" )
        {
            BREEZE_CHECK( from_get_single.value() == from_map.second ) ;
        }
    }
}

}

int
test_environment_variable_consistency()
{
    return breeze::test_runner::instance().run(
        "Environment variable consistency",
        { check_consistency } ) ;
}
