// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Macros for a single check within unit tests.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_EFlfreUFA16SG5tXxNJpWtUHWTCfIjaD
#define BREEZE_GUARD_EFlfreUFA16SG5tXxNJpWtUHWTCfIjaD

#include "breeze/testing/test_failure.hpp"

#define BREEZE_CHECK( condition )                                   \
    do {                                                            \
        if ( ! ( condition ) ) {                                    \
            throw breeze::test_failure( # condition,                \
                                        __FILE__, __LINE__ ) ;      \
        }                                                           \
    } while ( false )                                            /**/


#define BREEZE_CHECK_THROWS( exception_type, expression )           \
    do {                                                            \
        bool threw_as_expected = false ;                            \
        bool threw_but_wrong_type = false ;                         \
        try {                                                       \
            static_cast< void >( expression ) ;                     \
        } catch ( exception_type const & ) {                        \
            threw_as_expected = true ;                              \
        } catch ( ... ) {                                           \
            threw_but_wrong_type = true ;                           \
        }                                                           \
        BREEZE_CHECK( ! threw_but_wrong_type ) ;                    \
        BREEZE_CHECK( threw_as_expected ) ;                         \
    } while ( false )                                            /**/

#endif
