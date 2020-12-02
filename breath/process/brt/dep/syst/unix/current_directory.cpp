// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2015-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/process/current_directory.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include "breath/memory/auto_array.hpp"
#include <errno.h>
#include <unistd.h>
#include <string>

namespace breath {

std::string
current_directory()
{
    std::size_t         sz = 512 ;
    auto_array< char >  aa ;

    char const *        p = nullptr ;
    do {
        sz *= 2 ;
        aa.reset( new char[ sz ] ) ;
        p = getcwd( aa.get(), sz ) ;
    } while ( p == nullptr && errno == ERANGE ) ;

    if ( p == nullptr ) {
        throw last_api_error( "getcwd() failed" ) ;
    }
    return std::string( p ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
