// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief  SHA-1 policy and typedef's for SHA-1 hasher and digest.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_lTc6ZJg4kodcuFjtlYBwwj0hqDplySkG
#define BREEZE_GUARD_lTc6ZJg4kodcuFjtlYBwwj0hqDplySkG

#include "breeze/top_level_namespace.hpp"
#include "breeze/cryptography/merkle_damgard_engine.hpp"
#include "breeze/cryptography/merkle_damgard_machine.hpp"

namespace breeze_ns {

class               sha1_engine ;

template< typename Hasher >
class               digest ;

//!\{
//!     Convenience typedef(s).
// ---------------------------------------------------------------------------
typedef merkle_damgard_machine< sha1_engine >
                    sha1_hasher ;
typedef digest< sha1_hasher >
                    sha1_digest ;
//!\}


//!     SHA-1 policy class for \c merkle_damgard_machine.
// ---------------------------------------------------------------------------
class sha1_engine
    :   public merkle_damgard_engine< 160, 512, big_endian_policy >
{
public:
    static void         init_state( state_type & state ) ;
    static void         process_block( state_type & state,
                                       block_type const & block ) ;
} ;

}

#endif
