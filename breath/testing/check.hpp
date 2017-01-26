// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Macros for a single check within a unit test.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_EFlfreUFA16SG5tXxNJpWtUHWTCfIjaD
#define BREATH_GUARD_EFlfreUFA16SG5tXxNJpWtUHWTCfIjaD

#include "breath/testing/test_exception.hpp"
#include "breath/diagnostics/assert.hpp"

#define BREATH_CHECK( condition )                                           \
            do {                                                            \
                if ( ! (condition) )                                        \
                    throw breath::test_exception( __FILE__, __LINE__ ) ;    \
            } while ( false )                                            /**/


#define BREATH_CHECK_THROW( expression )                                    \
            do {                                                            \
                try {                                                       \
                    expression ;                                            \
                    BREATH_ASSERT( false && "BREATH_CHECK_THROW failed" ) ; \
                } catch ( ... ) {                                           \
                }                                                           \
            } while ( false )                                            /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
