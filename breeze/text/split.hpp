// ===========================================================================
//                     Copyright 2011-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Splits a `std::string` into a `std::vector` of
//!            `std::string`s.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_V50EdenEkFY3WA0JCnjok8aia0tACes8
#define BREEZE_GUARD_V50EdenEkFY3WA0JCnjok8aia0tACes8

#include "breeze/top_level_namespace.hpp"
#include <string>
#include <vector>

namespace breeze_ns {

//      split():
//      ========
//
//!     \copybrief split.hpp
//!
//!     \return
//!         A vector of strings obtained by splitting `s` at each
//!         character present in `separators`, in order.
//!
//!         Consecutive separators, or separators as first or last
//!         character in `s`, lead to an empty string in the resulting
//!         vector. The size of the vector is always one plus the number
//!         of separators in `s`.
//!
//!     \note
//!         This should probably use `set_of_chars`.
// ---------------------------------------------------------------------------
std::vector< std::string >
                    split( std::string const & s,
                           std::string const & separators ) ;

//      split_if():
//      ===========
//
//!     \copybrief split.hpp
//!
//!     \return
//!         A vector of strings obtained by splitting `s` at each
//!         character which satisfies the predicate `pred`, in order.
//!
//!         A character which satisfies `pred` is called a \e separator
//!         in the following.
//!
//!         Consecutive separators, or separators as first or last
//!         character in `s`, lead to an empty string in the resulting
//!         vector. The size of the vector is always one plus the number
//!         of separators in `s`.
//!
//!     \note
//!         This should probably use `set_of_chars`.
// ---------------------------------------------------------------------------
template< typename UnaryPredicate >
std::vector< std::string >
                    split_if( std::string const & s,
                              UnaryPredicate      pred ) ;

}

#include "brz/split.tpp"
#endif
