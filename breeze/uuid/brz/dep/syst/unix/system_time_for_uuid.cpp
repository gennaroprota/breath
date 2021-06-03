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

#include "breeze/top_level_namespace.hpp"

#include <sys/time.h>

#include <cstdint>

namespace breeze_ns {
namespace uuid_private {

int                 max_uuids_per_system_tick() ;
std::uint64_t       system_time_for_uuid() ;

//      I couldn't find any authoritative reference on the possible
//      resolutions of gettimeofday(), used below (note: keep in sync!).
//      So, let's be safe and only allow 1 UUID per tick.
// ---------------------------------------------------------------------------
int
max_uuids_per_system_tick()
{
    return 1 ;
}

std::uint64_t
system_time_for_uuid()
{
    //      gettimeofday() returns the time in seconds and microseconds
    //      since the UNIX epoch, i.e. January 1, 1970.
    //
    //      UUIDs use time in 100ns ticks since Oct 15, 1582.
    //
    //      The hex constant was taken RFC 4122, and I manually verified
    //      that it corresponds to the difference, which is:
    //
    //      17 days in Oct + 30 (Nov) + 31 (Dec) + (18 + 369) years and
    //      94 leap days, i.e. 141427 days.
    //
    //      Note: keep in sync with max_uuids_per_system_tick().
    // -----------------------------------------------------------------------
    timeval             tv ;
    gettimeofday( &tv, nullptr ) ;

    return   std::uint64_t( tv.tv_sec  ) * 10 * 1000 * 1000
           + std::uint64_t( tv.tv_usec ) * 10
           + 0x01B21DD213814000 ;
}

}
}
