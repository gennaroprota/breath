// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A unit test descriptor.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_R3D9wTLwfq8uQKxez4dTpXq0jrHzBXkC
#define BREEZE_GUARD_R3D9wTLwfq8uQKxez4dTpXq0jrHzBXkC

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      test_descriptor:
//      ================
//
class test_descriptor
{
public:
    typedef      void( &test_function )() ;

    //!     Constructs the descriptor for a test having a given name and
    //!     running the given function. Intentionally not explicit to
    //!     allow our typical usage:
    //!
    //!     ```
    //!         test_runner::instance().run( "description...",
    //!                                      { func1, func2... funcN } ) ;
    //!     ```
    // -----------------------------------------------------------------------
                        test_descriptor( test_function,
                                         char const * name = "" ) ;

    //      Declare this explicitly, since, due to the user-declared
    //      copy assignment below, the implicit definition of the copy
    //      constructor as defaulted is deprecated.
    // -----------------------------------------------------------------------
                        test_descriptor( test_descriptor const & ) = default ;

    //      Declare this explicitly to avoid Visual C++ C4626 (and
    //      C5027).
    // -----------------------------------------------------------------------
    void                operator =( test_descriptor const & ) = delete ;

    test_function       function() const noexcept ;
    std::string         name() const ;

private:
    test_function       m_function ;
    std::string         m_name ;
} ;

}

#endif
