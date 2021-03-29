// ===========================================================================
//                     Copyright 2006-2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breeze_ns {

template< typename Clock >
timer< Clock >::timer( start_mode mode )
{
    if ( mode == auto_start) {
        start() ;
    }
}

template< typename Clock >
void
timer< Clock >::start()
{
    m_start_time = Clock::now() ;
}

template< typename Clock >
typename timer< Clock >::duration
timer< Clock >::elapsed() const
{
    return Clock::now() - m_start_time ;
}

template< typename Clock >
typename timer< Clock >::duration
timer< Clock >::resolution()
{
    return Clock::resolution() ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
