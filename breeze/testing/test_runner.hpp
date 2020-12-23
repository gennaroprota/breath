// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief An object to run unit tests.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_ljsq7ok4MwSNNxMyfe6xf8RevjbF8jrE
#define BREEZE_GUARD_ljsq7ok4MwSNNxMyfe6xf8RevjbF8jrE

#include "breeze/top_level_namespace.hpp"
#include "breeze/process/exit_code.hpp"
#include "breeze/testing/test_descriptor.hpp"
#include "breeze/testing/test_exception.hpp"
#include "breeze/testing/test_reporter.hpp"
#include <initializer_list>

namespace breeze_ns {

class test_runner
{
public:
    //!     Deleted copy constructor (this class is a singleton).
    // -----------------------------------------------------------------------
                    test_runner( test_runner const & ) = delete ;

    //!     Deleted copy assignment operator (this class is a singleton).
    // -----------------------------------------------------------------------
    test_runner &   operator =(  test_runner const & ) = delete ;

private:
                    test_runner() ;

public:
    static test_runner &
                    instance() ;
    void            attach_reporter( test_reporter & ) ;
    template< typename TestDescriptorIterator >
    int             run( char const * group_description,
                         TestDescriptorIterator begin,
                         TestDescriptorIterator end ) ;
    int             run( char const * group_description,
                         std::initializer_list< test_descriptor > list ) ;

private:
    test_reporter * m_reporter ;
} ;

template< typename TestDescriptorIterator >
int
test_runner::run( char const * group_description,
                  TestDescriptorIterator begin,
                  TestDescriptorIterator end )
{
    int                 exit_code = breeze::exit_success ;
    int                 test_number = 1 ;
    m_reporter->on_all_tests_begin( group_description ) ;
    for ( ; begin != end ; ++ begin, ++ test_number ) {
        try {
            m_reporter->on_test_begin( test_number ) ;
            ( begin->function() )() ;
            m_reporter->on_test_passed( test_number ) ;
        } catch ( test_exception const & ex ) {
            exit_code = breeze::exit_failure ;
            m_reporter->on_test_failed( test_number, ex ) ;
        } catch ( std::exception const & ex ) {
            exit_code = breeze::exit_failure ;
            m_reporter->on_unexpected_exception( test_number, ex ) ;
        } catch ( ... ) {
            exit_code = breeze::exit_failure ;
            m_reporter->on_unexpected_exception( test_number ) ;
        }
    }
    m_reporter->on_all_tests_end() ;
    return exit_code ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
