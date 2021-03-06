// ===========================================================================
//                     Copyright 2016-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A universally unique identifier.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_jjJFg8dCizQ6ClSYgT8Zsg2zo7zFYgfG
#define BREEZE_GUARD_jjJFg8dCizQ6ClSYgT8Zsg2zo7zFYgfG

#include "breeze/top_level_namespace.hpp"
#include "breeze/operator/equality_comparison.hpp"
#include <cstdint>
#include <iosfwd>

namespace breeze_ns {

//      uuid:
//      =====
//
//!     \copybrief uuid.hpp
// ---------------------------------------------------------------------------
class uuid
    :   private equality_comparison< uuid >
{
public:
    //!     A type to represent the variant of the uuid.
    // -----------------------------------------------------------------------
    enum variant_type { ncs, rfc_4122, microsoft, future } ;

    //!     A type to represent the version of the uuid (meaningful only
    //!     when the variant is `rfc_4122`).
    // -----------------------------------------------------------------------
    enum version_type { time_based = 1, dce_security = 2, name_based_md5 = 3,
                        pseudo_random = 4, name_based_sha1 = 5 } ;

    //!     Constructs a nil uuid, i.e. a uuid that has all 128 bits set
    //!     to zero.
    // -----------------------------------------------------------------------
                        uuid() noexcept ;

    //!     Constructs a uuid having the given variant and version.
    // -----------------------------------------------------------------------
                        uuid( variant_type, version_type ) ;

    //!     \pre
    //!         `*this` is not a nil uuid.
    //!
    //!     \return
    //!         The variant of the uuid.
    // -----------------------------------------------------------------------
    variant_type        variant() const ;

    //!     \pre
    //!         `*this` is not a nil uuid.
    //!
    //!     \return
    //!         The version of the uuid.
    // -----------------------------------------------------------------------
    version_type        version() const ;

    //!     A named alternative to the default constructor.
    //!
    //!     \return
    //!         uuid()
    // -----------------------------------------------------------------------
    static uuid         nil() noexcept ;

    //!     \return
    //!         Whether `*this` is equal to `other`. Used by a base
    //!         class to provide `operator ==()` and `operator !=()`.
    // -----------------------------------------------------------------------
    bool                is_equal( uuid const & other ) const noexcept ;

    //      less:
    //      =====
    //
    //!     \brief
    //!         Implements a strict weak ordering relation between uuid
    //!         objects. Useful for ordered associative containers.
    // -----------------------------------------------------------------------
    class               less
    {
    public:
        bool                operator ()( uuid const & u1,
                                         uuid const & u2 ) const noexcept ;
    } ;

private:
    uint8_t             m_octets[ 16 ] ;

    //!     Outputs `uu` to the provided `std::ostream`, in the format
    //!     prescribed by RFC 4122 (in particular, the letters 'a' to
    //!     'f' are output as lowercase).
    // -----------------------------------------------------------------------
    friend std::ostream & operator <<( std::ostream &, uuid const & uu ) ;
} ;

}

#endif
