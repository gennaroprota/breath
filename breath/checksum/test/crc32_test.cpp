// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/checksum/crc32.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/testing/check.hpp"
#include "breath/testing/console_reporter.hpp"
#include "breath/testing/test_runner.hpp"
#include <iostream>
#include <ostream>
#include <string>

void
check_known()
{
    struct
    {
        std::string text ;
        unsigned long crc32 ;
    } const             known[] =
    {
        { "",                                            0x0        },

        // Following test vectors verified with:
        //   <https://www.lammertbies.nl/comm/info/crc-calculation.html>
        //
        { "The quick brown fox jumps over the lazy dog", 0x414FA339 },
        { "123456789",                                   0xCBF43926 },
        { "breath",                                      0x3A3B4FE3 },
        { " ",                                           0xE96CCF45 },
        { "A",                                           0xD3D99E8B },
        { "ABC",                                         0xA3830348 },
        { "Nel mezzo del cammin di nostra vita",         0x5BFBCBF8 }
      } ;

    for ( auto it = breath::cbegin( known ) ; it != breath::cend( known ) ; ++ it ) {
        BREATH_CHECK( breath::crc32( it->text.begin(), it->text.end() ) == it->crc32 ) ;
    }
}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check_known } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
