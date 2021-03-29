// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Wrapper for an "equivalent" of a stream.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_th2bAe1w4u2MisZE4yyhiRJdCIC2yncU
#define BREEZE_GUARD_th2bAe1w4u2MisZE4yyhiRJdCIC2yncU

#include "breeze/top_level_namespace.hpp"
#include <istream>

namespace breeze_ns {

//      stream_equivalent:
//      ==================
//
//!     \copybrief stream_equivalent.hpp
//!
//!     This is a replacement for `basic_format_saver`, which was
//!     removed from the library, since it was impossible to implement
//!     in its generality (i.e. making it also save and restore the
//!     `iword()`/`pword()` info---see its source code comments from
//!     Git's history).
//!
//!     The idea was suggested to me by Peter Sommerlad. Basically, it
//!     constructs a stream which is equivalent to a given one, i.e.
//!
//!      - is attached to the same stream buffer
//!
//!      - is constructed with the same rdstate()
//!
//!      - gets a `copyfmt()` from the original stream,
//!
//!     and propagates any changes to `rdstate()` back to the original
//!     stream, when it (the equivalent) is destroyed.
//!
//!     This allows writing e.g.:
//!
//!     ```
//!         std::ostream &
//!         operator <<( std::ostream & original_os, my_type const & m )
//!         {
//!             stream_equivalent< std::ostream > equiv( original_os ) ;
//!             std::ostream & os = equiv.get() ;
//!
//!             // OK, just use 'os' from now on.
//!             ...
//!
//!             return original_os ; // NOTA BENE: see the documentation of
//!                                                the get() member.
//!         }
//!     ```
//!
//!     and change formatting flags (including those allocated via
//!     `iword()` or `pword()`), precision, fill character, exception
//!     mask, stream locale (but not the stream buffer one) or
//!     synchronized output stream, without affecting the original
//!     stream.
//!
//!     \par Credits
//!
//!     Peter Sommerlad suggested the key idea of this template, when I
//!     was stuck with `basic_format_saver`. James Kanze gave, as usual,
//!     excellent feedback on `basic_format_saver`, in particular about
//!     locales and `imbue()`.
// ---------------------------------------------------------------------------
template< typename Stream >
class stream_equivalent
{
public:

    //!     The type of the equivalent stream. Note that this is not the
    //!     same as `Stream`, because `Stream` might not allow to
    //!     replace the stream buffer (file streams, for instance, are
    //!     like that).
    //!
    //!     This means that, for instance, if you have a
    //!     `std::stringstream`, you will get an equivalent but you
    //!     can't call the `str()` member on that equivalent. This is
    //!     not a limitation in practice, because you can call `str()`
    //!     on the original stream, instead.
    // -----------------------------------------------------------------------
    typedef std::basic_iostream<
        typename Stream::char_type,
        typename Stream::traits_type >
                        stream_type ;

    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        stream_equivalent( stream_equivalent const & )
                                                                = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    stream_equivalent & operator =( stream_equivalent const & ) = delete ;

    //!     Constructs a stream equivalent for `original` (see the
    //!     class-level documentation).
    // -----------------------------------------------------------------------
    explicit            stream_equivalent( Stream & original ) ;

    //!     Turns on the `rdstate()` bits that are on in the equivalent,
    //!     in the original stream, too, without emitting an
    //!     `std::ios_base::failure`, and destroys the object.
    // -----------------------------------------------------------------------
                        ~stream_equivalent() noexcept ;

    //!     \return
    //!         A reference to a stream equivalent to that passed to the
    //!         first constructor. This is the stream that must be used
    //!         to do the actual output.
    //!
    //!     \warning
    //!         Use the stream equivalent to do the actual output \e but
    //!         do not return a reference to it from the inserter!
    //!         Return a reference to the original stream, instead.
    //!
    //!         Example:
    //!
    //!         ```
    //!             std::ostream &
    //!             operator <<( std::ostream & original_stream,
    //!                          my_type const & m )
    //!             {
    //!                 stream_equivalent< std::ostream >
    //!                                     equiv( original_stream ) ;
    //!                 std::ostream &      os = equiv.get() ;
    //!
    //!                 /* do output through 'os' */
    //!
    //!                 // Do not write: return os!
    //!                 //
    //!                 return original_stream ;
    //!             }
    //!         ```
    //!
    //!         Note that this may occur if you "adapt" an existing
    //!         inserter which didn't use `stream_equivalent`, by simply
    //!         renaming the stream parameter from `os` to
    //!         `original_stream` and "reusing" the old parameter name
    //!         for the stream equivalent: this will also leave the
    //!         return statement intact, returning a reference to a
    //!         sub-object of the local variable `equiv`.
    // -----------------------------------------------------------------------
    stream_type &       get() noexcept ;

private:
    Stream &            m_original ;
    stream_type         m_equivalent ;
} ;

}

#include "brz/stream_equivalent.tpp"
#endif
