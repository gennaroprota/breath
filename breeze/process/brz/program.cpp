// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2010-2019 Gennaro Prota
//                      Copyright 1997-2003 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/process/program.hpp"
#include "breeze/counting/signed_count.hpp"
#include "breeze/diagnostics/assert.hpp"
#include "breeze/process/exit_code.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>

namespace breeze_ns {
namespace           {

//      NOTE:
//          keep in sync with enum gravity in the class definition and
//          the switch-case in declare_error().
// ---------------------------------------------------------------------------
int const           exit_codes[] = {
    breeze::exit_success,
    breeze::exit_warning,
    breeze::exit_error,
    breeze::exit_fatal,
    breeze::exit_internal
} ;

bool
has_program_name( int argc, char const * const * argv )
{
    return argc > 0 && argv[ 0 ][ 0 ] != '\0' ;
}

}

program &
program::instance() noexcept
{
    static program      the_instance ;

    return the_instance ;
}

void
program::set_name( int argc, char const * const * argv )
{
    BREEZE_ASSERT( ! m_program_name.is_valid() ) ;

    if ( has_program_name( argc, argv ) ) {
        do_set_name( argv[ 0 ] ) ;
    }
}

void
program::set_name( int argc, char const * const * argv,
                             std::filesystem::path const & fallback )
{
    BREEZE_ASSERT( ! m_program_name.is_valid() ) ;
    BREEZE_ASSERT( ! fallback.empty() ) ;

    do_set_name( has_program_name( argc, argv )
                    ? argv[ 0 ]
                    : fallback ) ;
}

void
program::set_name( std::filesystem::path const & name )
{
    BREEZE_ASSERT( ! m_program_name.is_valid() ) ;
    BREEZE_ASSERT( ! name.empty() ) ;

    do_set_name( name ) ;
}

maybe< std::filesystem::path >
program::name() const
{
    return m_program_name ;
}

void
program::declare_error( program::gravity g ) // gps nome OK?
{
    BREEZE_ASSERT( static_cast< int >( g ) <
                     breeze::signed_count( exit_codes ) ) ;

    if ( g > m_max_gravity ) {
        m_max_gravity = g ;
    }

    switch ( m_max_gravity ) {
    case comment:
    case warning:
    case error:
        break ;

    case fatal:
        terminate() ;
        // no break ;, to avoid compiler warnings

    case internal:
        std::abort() ;
        // no break ;, to avoid compiler warnings
    }
}

void
program::declare_error( program::gravity g, std::string const & message )
{
    std::cerr << message << std::endl ;
    declare_error( g ) ;
}

int
program::exit_code()
{
    std::cout.flush() ;

    if ( std::cout.fail() ) {
        declare_error( program::error, "I/O error on standard output" ) ;
    }

    return exit_codes[ m_max_gravity ] ;
}

[[ noreturn ]] void
program::terminate()
{
    int const           code = exit_code() ;
    if ( m_terminate_handler != nullptr ) {
        ( *m_terminate_handler )( code ) ;
    } else {
        std::exit( code ) ;
    }

    std::abort() ;
}

void
program::set_terminate_handler( void ( *handler )( int ) )
{
    m_terminate_handler = handler ;
}

program::program() noexcept
    :   m_max_gravity( comment ),
        m_terminate_handler( nullptr )
{
}

void
program::do_set_name( std::filesystem::path const & name )
{
    m_program_name = name.filename() ;
}

}
