// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns an object given its textual representation.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_Q6sxk1RUMey9fbjLvtacucg61F39I6ob
#define BREEZE_GUARD_Q6sxk1RUMey9fbjLvtacucg61F39I6ob

#include "breeze/top_level_namespace.hpp"
#include "breeze/vocabulary/maybe.hpp"
#include <locale>
#include <string>

namespace breeze_ns {

//      from_string():
//      ==============
//
//!     \brief Tries to form an object of type \c T given its textual
//!            representation.
//!
//!     \par Type requirements
//!         \c T shall be <tt>DefaultConstructible</tt> and <tt>
//!         MoveConstructible</tt>. Furthermore it shall be <tt>input
//!         streamable</tt> from a \c std::istream, meaning that an
//!         <code>operator &gt;&gt;()</code> function may be called that
//!         takes an instance of \c std::istream as first argument and
//!         an instance of \c T as second argument.
//!
//!     \note
//!         \c s and \c T being equal, the result of this function will,
//!         in general, also depend on the \c locale argument.
// ---------------------------------------------------------------------------
template< typename T >
maybe< T >          from_string( std::string const & s,
                                 std::locale const & loc = std::locale() ) ;

//      from_string():
//      ==============
//
//!     \brief Specialization for <code>std::string</code>s.
//!
//!     \return
//!         An (always valid) \c maybe object containing a string which
//!         compares equal to \c s.
//!
//!     \note
//!         This specialization is not just an optimization: it ensures
//!         that e.g. " test " converts to " test " and not "test".
//!
//!         Also, the \c locale argument isn't actually used for this
//!         specialization.
// ---------------------------------------------------------------------------
template<>
maybe< std::string> from_string< std::string >( std::string const & s,
                                                std::locale const & ) ;

}

#include "brz/from_string.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
