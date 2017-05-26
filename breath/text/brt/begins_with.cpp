// =========================================================================
//                    Copyright 2013-2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/text/begins_with.hpp"
#include <algorithm>
#include <string>

namespace breath {

//      Note: if with.length() == 0 this always returns true.
// -------------------------------------------------------------------------
bool
begins_with( std::string const & str, std::string const & with )
{
    return str.size() >= with.size()
        && std::equal( with.cbegin(), with.cend(), str.cbegin() ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
