// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/replace_all.hpp"
#include "breeze/diagnostics/assert.hpp"
#include <cstddef>
#include <string>

namespace breeze_ns {

void replace_all(
    std::string & s,
    std::string const & from,
    std::string const & to )
{
    BREEZE_ASSERT( ! from.empty() ) ;

    std::size_t         pos = 0 ;

    //      Note that 'pos', below, may reach s.size(): this happens
    //      (only) when 's' is empty (pos == 0) or when a replacement
    //      occurs at the end of 's' (see the statement
    //
    //        'pos += to.length()'
    //
    //      ). This is fine, because find() has no preconditions and
    //      handles that case correctly.
    // -----------------------------------------------------------------------
    while ( (pos = s.find( from, pos )) != s.npos ) {
        s.replace( pos, from.length(), to ) ;
        pos += to.length() ;
    }
}

}
