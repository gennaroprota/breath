// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2016-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/porting/dependent_code.hpp"
#include BREATH_DEPENDENT_CODE( system, system_time_for_uuid.cpp )

#include "breath/uuid/uuid.hpp"
#include "breath/counting/count.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/meta/width.hpp"
#include "breath/random/entropy_source.hpp"
#include "breath/stream/format_saver.hpp"

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ostream>

namespace {

//      adjusted_system_time():
//      =======================
//
//      Gets the system time and compensates for the fact that the
//      system clock resolution is (or may be) less than 100ns, which is
//      the resolution that would be required for UUIDs.
//
//      Note: this function is the reason why the uuid class is not
//      thread-safe.
// ---------------------------------------------------------------------------
std::uint64_t
adjusted_system_time()
{
    int const           max_uuids_per_tick = 1024 ;
    static std::uint64_t
                        last_time = breath::uuid_private::
                                    system_time_for_uuid() ;
    static int          uuids_on_this_tick = 0 ;

    std::uint64_t       now ;
    while ( true ) {
        now = breath::uuid_private::system_time_for_uuid() ;
        if ( last_time != now ) {
            last_time = now ;
            uuids_on_this_tick = 0 ;
            break ;
        } else if ( uuids_on_this_tick < max_uuids_per_tick ) {
            ++ uuids_on_this_tick ;
            break ;
        }

        // Requesting too many UUIDs on the same tick; busy wait.
    }

    return now + uuids_on_this_tick ;
}

}


namespace breath {

uuid::uuid() noexcept
    :   m_time_low( 0 ),
        m_time_mid( 0 ),
        m_time_hi_and_version( 0 ),
        m_clock_seq( 0 ),
        m_node()
{
}

uuid::uuid( uuid::variant_type var, uuid::version_type ver )
{
    //      Other variants/versions not implemented.
    // -----------------------------------------------------------------------
    BREATH_ASSERT( var == rfc_4122 && ver == time_based ) ;

    std::uint64_t const time_stamp = ::adjusted_system_time() ;

    m_time_low = time_stamp & 0xFFFF'FFFF ;
    m_time_mid = (time_stamp >> 32) & 0xFFFF ;
    m_time_hi_and_version = static_cast< std::uint16_t >(
                            ( (time_stamp >> 48) & 0x0FFF ) | ( 1 << 12 ) ) ;
    entropy_source      es ;
    std::uint32_t const rnd = ( es.next() << 24 ) | ( es.next() << 16 )
                            | ( es.next() << 8 )  |   es.next() ;
    m_clock_seq = static_cast< std::uint16_t >(
                            ( ( rnd >> 4 ) & 0x3fff ) | 0x8000 ) ;

    //      A random MAC address (this is allowed by RFC 4122, and
    //      desirable). To distinguish it from a real MAC address, RFC
    //      4122 requires that the least significant bit of the first
    //      octet be set to 1.
    // -----------------------------------------------------------------------
    for ( std::size_t i = 0 ; i < breath::count( m_node ) ; ++ i ) {
        m_node[ i ] = static_cast< std::uint8_t >( es.next() ) ;
    }
    m_node[ 0 ] |= 1 ;
}

uuid::variant_type
uuid::variant() const noexcept
{
    //      Reference: RFC 4122
    // -----------------------------------------------------------------------
    std::uint8_t const  octet8 = m_clock_seq >> 8 ;
    std::uint8_t const  high3 = octet8 >> 5 ;

    if ( ( high3 & 0b100 ) == 0 ) {
        return ncs ;
    } else if ( ( high3 & 0b110 ) == 0b100 ) {
        return rfc_4122 ;
    } else if ( ( high3 & 0b111 ) == 0b110 ) {
        return microsoft ;
    } else {
        BREATH_ASSERT( ( high3 & 0b111 ) == 0b111 ) ;
        return future ;
    }

}

uuid::version_type
uuid::version() const noexcept
{
    //      Reference: RFC 4122
    // -----------------------------------------------------------------------
    std::uint8_t const  version_number = m_time_hi_and_version >> 12 ;

    BREATH_ASSERT( 1 <= version_number && version_number <= 5 ) ;
    return static_cast< version_type >( version_number ) ;
}

uuid
uuid::nil() noexcept
{
    return uuid() ;
}

template< typename T >
std::ostream &
output_as_hex( std::ostream & os, T value )
{
    int const           bits_per_hex_digit = 4 ;
    int const           hex_digits_per_value = meta::width< T >::value /
                                               bits_per_hex_digit ;

    os.setf( std::ios_base::hex, std::ios_base::basefield ) ;

    //      About the static_cast: see the note near the declarations of
    //      the class data members. Keep in sync.
    // -----------------------------------------------------------------------
    os << std::setw( hex_digits_per_value ) << static_cast< std::uint32_t >(
                                                                       value ) ;
    return os ;
}

std::ostream &
operator <<( std::ostream & os, uuid const & uu )
{
    format_saver const  saver( os ) ;

    os.fill( '0' ) ;

    os.setf( std::ios_base::right, std::ios_base::adjustfield ) ;
    os.unsetf( std::ios_base::showbase ) ;
    os.unsetf( std::ios_base::uppercase ) ;

    output_as_hex( os, uu.m_time_low )            << '-' ;
    output_as_hex( os, uu.m_time_mid )            << '-' ;
    output_as_hex( os, uu.m_time_hi_and_version ) << '-' ;
    output_as_hex( os, uu.m_clock_seq )           << '-' ;
    for ( std::size_t i = 0 ; i < count( uu.m_node ) ; ++ i ) {
        output_as_hex( os, uu.m_node[ i ] ) ;
    }
    return os ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
