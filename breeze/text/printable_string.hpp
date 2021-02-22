// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//                         Copyright 2000 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A string with non-printable chars escaped.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_03plpMI2VjgMEb2QhWRYStxFLQ2UshCk
#define BREEZE_GUARD_03plpMI2VjgMEb2QhWRYStxFLQ2UshCk

#include "breeze/top_level_namespace.hpp"
#include "breeze/vocabulary/maybe.hpp"
#include <iosfwd>
#include <string>

namespace breeze_ns {

//      printable_string:
//      =================
//
//!     \copybrief printable_string.hpp
//!
//!     Represents a string that prints to an \c ostream without
//!     non-printable characters.
//!
//!     If a character has a corresponding simple-escape-sequence (such
//!     as <code>\\a</code>), it is displayed using that escape
//!     sequence. Otherwise, if it is in the range <code>[0x20, 0x7e]
//!     </code>, it is displayed directly. Otherwise an escape sequence
//!     of the form <tt>\\x...</tt> is used. The goal is, for instance,
//!     to send the output to a log and then read it from another
//!     machine. The number of digits in any hexadecimal escape sequence
//!     is the ceiling of the quotient between \c CHAR_BIT and \c 4
//!     (they are left-padded with zeroes); note that this is different
//!     from character and string literals, where there's no limit to
//!     the number of hexadecimal digits, and that e.g. <code>\0</code>
//!     is represented, when <tt>CHAR_BIT == 8</tt>, as <code>\\x00
//!     </code>. In general, to read a \c %printable_string
//!     unambiguously you need to know the value of \c CHAR_BIT on the
//!     source machine.
//!
//!     A \c %printable_string can be constructed "from a non-string"
//!     (i.e. from a null pointer): this is useful for debugging purposes.
//!     In this special case, only, the \c %printable_string outputs
//!     without quotes. Otherwise, it is always enclosed in double
//!     quotes and a double quote character in the string is escaped,
//!     as is usual in C++.
//!
//!     Instances of this class maintain a copy of the string, so the
//!     user does not have to worry about the lifetime of the object
//!     given to the constructor.
// ---------------------------------------------------------------------------
class printable_string
{
public:
    explicit            printable_string( char const * ) ;
    explicit            printable_string( std::string const & ) ;

    std::string         to_string() const ;

private:
    friend std::ostream &
                    operator <<( std::ostream & dest,
                                 printable_string const & ) ;

    maybe< std::string >
                        m_value ;
} ;

}

#endif
