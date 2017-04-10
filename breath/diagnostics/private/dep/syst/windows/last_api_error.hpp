// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include <iosfwd>

namespace breath {

//!     Represents the last error encountered in an API call. It
//!     corresponds to GetLastError() under Windows and errno under
//!     Unix.
//!
//!     The idea is that after an unsuccessful API call you write:
//!     <code>
//!         throw last_api_error( "<APIName> failed" ) ;
//!     </code>
//!     and you're done with error handling.
//!
//!     The class is OutputStreamable, so you can also use
//!     \c breath::as_string, which gives more information than the
//!     member \c what(), but may throw.
// -------------------------------------------------------------------------
class last_api_error
    :   public exception
{
public:
    explicit            last_api_error( char const * ) noexcept ;
                        last_api_error( last_api_error const & other ) noexcept ;
                        ~last_api_error() noexcept ;
    unsigned long       code() const noexcept ;
    virtual char const *
                        what() const noexcept override ;

    void                operator =( last_api_error const & ) = delete ;

private:
    friend std::ostream &
                        operator <<( std::ostream &, last_api_error const & ) ;

    unsigned long       m_last_error ;
    char                m_message[ 10 * 1024 - 1 ] ;
} ;

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
