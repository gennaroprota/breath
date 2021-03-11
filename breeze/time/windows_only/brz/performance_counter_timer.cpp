// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/time/windows_only/performance_counter_timer.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include <Windows.h>

namespace breeze_ns {
namespace           {

long long
query_count()
{
    LARGE_INTEGER       count ;
    if ( QueryPerformanceCounter( &count ) == 0 ) {
        throw last_api_error( "QueryPerformanceCounter() failed" ) ;
    }

    return count.QuadPart ;
}

}


performance_counter_policy::performance_counter_policy()
{
    //      Note that start() is not called here. It will be called by
    //      the timer template, if needed. Note that this causes the
    //      member m_start to be left uninitialized.
    // -----------------------------------------------------------------------
    LARGE_INTEGER       f ;
    if ( QueryPerformanceFrequency( &f ) == 0 ) {
        throw last_api_error( "QueryPerformanceFrequency() failed" ) ;
    }
    m_frequency = f.QuadPart ;
}

void
performance_counter_policy::start()
{
    m_start = query_count() ;
}

performance_counter_policy::duration_type
performance_counter_policy::elapsed() const
{
    long long const     now = query_count() ;
    return ( now - m_start ) * resolution() ;
}

performance_counter_policy::duration_type
performance_counter_policy::resolution() const
{
    return duration_type(
        duration_type::period::den /
            m_frequency /
            duration_type::period::num
        ) ;
}

}
