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

#include "breeze/text/printable_string.hpp"
#include "breeze/mathematics/ceiling_of_quotient.hpp"
#include <climits>
#include <iomanip>
#include <ios>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace breeze_ns {

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

std::string
printable_string::to_string() const
{
    if ( ! m_value.is_valid() ) {
        return "(null)" ;
    }

    std::ostringstream  oss ;

    oss.setf( std::ios_base::hex, std::ios_base::basefield ) ;
    oss.setf( std::ios_base::right, std::ios_base::adjustfield ) ;
    oss.unsetf( std::ios_base::showbase ) ;
    oss.fill( '0' ) ;

    oss << '\"' ;
    std::string const & s = m_value.value() ;
    for ( char const c : s ) {
        switch ( c ) {
        case '\\':
            oss << "\\\\" ;
            break ;

        case '\"':
            oss << "\\\"" ;
            break ;

        case '\?':
            oss << "\\\?" ;
            break ;

        case '\a':
            oss << "\\a" ;
            break ;

        case '\b':
            oss << "\\b" ;
            break ;

        case '\f':
            oss << "\\f" ;
            break ;

        case '\n':
            oss << "\\n" ;
            break ;

        case '\r':
            oss << "\\r" ;
            break ;

        case '\t':
            oss << "\\t" ;
            break ;

        case '\v':
            oss << "\\v" ;
            break ;

        default:
            // Note: if you change these values, keep the documentation
            //       in sync.
            // ---------------------------------------------------------------
            char const      printable_min = 0x20 ;
            char const      printable_max = 0x7e ;
            if ( printable_min <= c && c <= printable_max ) {
                oss << c ;
            }  else {
                int const       bits_per_hex_digit = 4 ;
                int const       width = breeze::ceiling_of_quotient(
                                            CHAR_BIT, bits_per_hex_digit ) ;
                oss << "\\x"
                     << std::setw( width )
                     << static_cast< unsigned int >(
                         static_cast< unsigned char >( c ) ) ;
            }
            break ;
        }
    }
    oss << '\"' ;

    if ( oss.fail() ) {
        throw std::runtime_error(
            "error in printable_string::to_string()" ) ;
    }

    return oss.str() ;
}

std::ostream &
operator <<( std::ostream & dest, printable_string const & ps )
{
    return dest << ps.to_string() ;
}


}
