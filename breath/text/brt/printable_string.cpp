// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//                         Copyright 2000 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/printable_string.hpp"
#include "breath/stream/format_saver.hpp"
#include <climits>
#include <iomanip>
#include <ios>
#include <ostream>

namespace breath {

printable_string::printable_string( char const * p )
{
    if ( p != nullptr ) {
        m_value = std::string( p ) ;
    }
}

printable_string::printable_string( std::string const & s )
    :   m_value( s )
{
}

std::ostream &
operator <<( std::ostream & dest, printable_string const & ps )
{
    if ( ! ps.m_value.is_valid() ) {
        return dest << "(null)" ;
    }

    format_saver const  saver( dest ) ;
    dest.setf( std::ios_base::hex, std::ios_base::basefield ) ;
    dest.fill( '0' ) ;

    dest << '\"' ;
    std::string const & s = ps.m_value.value() ;
    for ( char const c : s ) {
        switch ( c ) {
        case '\\':
            dest << "\\\\" ;
            break ;

        case '\"':
            dest << "\\\"" ;
            break ;

        case '\?':
            dest << "\\\?" ;
            break ;

        case '\a':
            dest << "\\a" ;
            break ;

        case '\b':
            dest << "\\b" ;
            break ;

        case '\f':
            dest << "\\f" ;
            break ;

        case '\n':
            dest << "\\n" ;
            break ;

        case '\r':
            dest << "\\r" ;
            break ;

        case '\t':
            dest << "\\t" ;
            break ;

        case '\v':
            dest << "\\v" ;
            break ;

        default:
            // Note: if you change this values, keep the documentation
            //       in sync.
            // -------------------------------------------------------------
            char const      printable_min = 0x20 ;
            char const      printable_max = 0x7e ;
            if ( printable_min <= c && c <= printable_max ) {
                dest << c ;
            }  else {
                static_assert( CHAR_BIT == 8, "please, adjust the setw()"
                                                                    " below") ;
                dest << "\\x"
                     << std::setw( 2 )
                     << static_cast< unsigned int >(
                         static_cast< unsigned char>( c ) ) ;
            }
            break ;
        }
    }
    dest << '\"' ;
    return dest ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
