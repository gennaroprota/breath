// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breeze_ns {

template< typename Device >
timer< Device >::timer( start_mode mode )
    :   m_device()
{
    if ( mode == auto_start) {
        start() ;
    }
}

template< typename Device >
void
timer< Device >::start()
{
    return m_device.start() ;
}

template< typename Device >
typename timer< Device >::duration_type
timer< Device>::elapsed() const
{
    return m_device.elapsed() ;
}

template< typename Device >
typename timer< Device >::duration_type
timer< Device >::resolution() const
{
    return m_device.resolution() ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
