// ===========================================================================
//                     Copyright 2007-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A description of the operating system.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_vUmfBUe7uRgM2lw3OI5BLE0BSMMDnzDS
#define BREEZE_GUARD_vUmfBUe7uRgM2lw3OI5BLE0BSMMDnzDS

#include "breeze/top_level_namespace.hpp"
#include <iosfwd>
#include <string>

namespace breeze_ns {

//      operating_system_name:
//      ======================
//
//!     A streamable description of the operating system.
// ---------------------------------------------------------------------------
class operating_system_name
{
public:
    std::string         to_string() const ;
} ;

//!     Stream inserter for \c operating_system_name. Outputs a
//!     description of the operating system.
// ---------------------------------------------------------------------------
std::ostream &      operator <<( std::ostream &,
                                 operating_system_name const & ) ;

}

#endif
