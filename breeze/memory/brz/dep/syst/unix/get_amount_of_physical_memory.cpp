// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/memory/get_amount_of_physical_memory.hpp"

#include <unistd.h>

namespace breeze_ns {

long long
get_amount_of_physical_memory()
{
    long const          pages = sysconf( _SC_PHYS_PAGES ) ;
    long const          page_size = sysconf( _SC_PAGESIZE ) ;

    return static_cast< long long >( pages ) *
           static_cast< long long >( page_size ) / 1024 ;
}

}
