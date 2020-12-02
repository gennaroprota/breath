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

#ifndef BREATH_GUARD_EFlfreUFA16SG5tXxNJpWtUHWTCfIjaD
#define BREATH_GUARD_EFlfreUFA16SG5tXxNJpWtUHWTCfIjaD

#include "breath/diagnostics/assert.hpp"
#include "breath/testing/test_exception.hpp"

#define BREATH_CHECK( condition )                                             \
            do {                                                              \
                if ( ! ( condition ) ) {                                      \
                    throw breath::test_exception( __FILE__, __LINE__ ) ;      \
                }                                                             \
            } while ( false )                                              /**/


// For PVS-Studio:
// -V:BREATH_CHECK_THROW:565
// ---------------------------------------------------------------------------
#define BREATH_CHECK_THROW( exception_type, expression )                      \
            do {                                                              \
                bool threw_as_expected = false ;                              \
                bool threw_but_wrong_type = false ;                           \
                try {                                                         \
                    expression ;                                              \
                } catch ( exception_type const & ) {                          \
                    threw_as_expected = true ;                                \
                } catch ( ... ) {                                             \
                    threw_but_wrong_type = true ;                             \
                }                                                             \
                BREATH_CHECK( ! threw_but_wrong_type ) ;                      \
                BREATH_CHECK( threw_as_expected ) ;                           \
            } while ( false )                                              /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
