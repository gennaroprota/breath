// =========================================================================
//                    Copyright 2013-2018 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/text/ends_with.hpp"
#include <algorithm>
#include <string>

namespace breath {

//      Note: if 'with' is empty this always returns true. (See the
//            analogous comment in begins_with.cpp.)
// -------------------------------------------------------------------------
bool
ends_with( std::string const & str, std::string const & with ) noexcept
{
    auto const          sz( with.size() ) ;
    return str.size() >= sz
        && std::equal( with.cbegin(), with.cend(), str.cend() - sz ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
