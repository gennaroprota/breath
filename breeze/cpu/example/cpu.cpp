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
//
//      Reference:
//          Intel(R) 64 and IA-32 Architectures Developer's Manual: Vol. 2A.
// ---------------------------------------------------------------------------

#include "breeze/cpu/get_cpuid_info.hpp"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>

namespace {

using namespace breeze ;

bool
has_processor_brand_string()
{
    std::uint32_t const mask = 0x8000'0000 ;
    cpuid_result const  r = get_cpuid_info( mask, 0 ) ;

    return (r.eax & mask) != 0 &&
        r.eax >= (mask + 4) ;
}

std::string
processor_brand_string()
{
    std::uint32_t const from = 0x8000'0002 ;
    std::uint32_t const to   = 0x8000'0004 ;

    std::size_t const   len = 16 * ( to - from + 1 ) ;
    char                brand_string[ len ] ;
    for ( std::uint32_t i = from ; i <= to ; ++ i ) {
        cpuid_result const  info = get_cpuid_info( i, 0 ) ;
        char * const        p = brand_string + 16 * ( i - from ) ;
        std::memcpy( p,      &info.eax, sizeof( info.eax ) ) ;
        std::memcpy( p + 4,  &info.ebx, sizeof( info.ebx ) ) ;
        std::memcpy( p + 8,  &info.ecx, sizeof( info.ecx ) ) ;
        std::memcpy( p + 12, &info.edx, sizeof( info.edx ) ) ;
    }

    return std::string( brand_string ) ;
}

std::string
cpu_vendor_id_string()
{
    cpuid_result const  info = get_cpuid_info( 0, 0 ) ;

    int const           len = 12 ;
    char                id_string[ len ] ;
    std::memcpy( id_string,     &info.ebx, sizeof( info.ebx ) ) ;
    std::memcpy( id_string + 4, &info.edx, sizeof( info.edx ) ) ;
    std::memcpy( id_string + 8, &info.ecx, sizeof( info.ecx ) ) ;

    return std::string( id_string, len ) ;
}

}

int
main()
{
    std::cout << "CPU vendor ID string:   " <<
                     cpu_vendor_id_string() << std::endl ;
    std::cout << "Processor brand string: " << ( has_processor_brand_string()
                                                    ? processor_brand_string()
                                                    : "<not available>" )
                                            << std::endl ;
}
