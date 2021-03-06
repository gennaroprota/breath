// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/environment/get_all_environment_variables.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include "breeze/process/program.hpp"
#undef UNICODE          // it seems impossible to directly call
                        // GetEnvironmentStringsA(), so undefine UNICODE
#include <Windows.h>    // and use the normal name
#include <cstddef>
#include <utility>

namespace breeze_ns {
namespace           {

void
do_free( char * p ) noexcept
{
    using               breeze::program ;
    if ( FreeEnvironmentStrings( p ) == 0 ) {
        program::instance().declare_error( program::warning,
            "FreeEnvironmentStrings() failed" ) ; //gps
    }
}

}

std::map< std::string, std::string >
get_all_environment_variables()
{
    typedef std::map< std::string, std::string >
                        result_type ;

    char * const        start = GetEnvironmentStrings() ;
    if ( start == nullptr ) {
        throw last_api_error( "GetEnvironmentStrings() failed" ) ;
    }

    result_type         result ;
    try {
        char const *        curr = start ;
        while ( *curr != '\0' ) {
            std::string const   single = curr ;
            std::size_t const   pos = single.find( '=' ) ;
            std::string const   name = single.substr( 0, pos ) ;

            //      On my system, the string pointed to by start begins
            //      with "=::=::\", hence the test on empty(). Note that
            //      this makes things consistent, because
            //      get_environment_variable( "" ) fails (at least in my
            //      tests).
            // ---------------------------------------------------------------
            if ( ! name.empty() ) {
                std::string const   value = pos != single.npos
                                                ? single.substr( pos + 1 )
                                                : ""
                                                ;
                result.insert( result_type::value_type(
                                    name,
                                    value
                                ) ) ;
            }
            curr += ( single.length() + 1 ) ;
        }
    } catch ( ... ) {
        do_free( start ) ;
        throw ;
    }
    do_free( start ) ;
    return result ;
}

}
