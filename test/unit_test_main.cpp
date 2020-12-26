// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "unit_test_main.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include "breeze/environment/operating_system_name.hpp"
#include "breeze/memory/amount_of_physical_memory.hpp"
#include <cstdlib>
#include <iostream>

int
main()
{
    using               test_function_type = int () ;

    test_function_type * const
                        tests[] = {
            test_breeze_assert,
            test_auto_array,
            test_base_file_name,
            test_base64_to_binary,
            test_begins_with,
            test_binary_to_base64,
            test_bit_cast,
            test_clamp,
            test_count_bits,
            test_counter,
            test_crc,
            test_damerau_levenshtein_distance,
            test_digest_ordering,
            test_digital_root,
            test_breeze_dump_expression,
            test_endian_codec,
            test_ends_with,
            test_entropy_source,
            test_environment_variable_consistency,
            test_eof_value,
            test_extension,
            test_from_string,
            test_gcd,
            test_get_environment_variable,
            test_get_set_current_directory,
            test_is_2s_complement,
            test_is_power_of_2,
            test_last_api_error,
            test_lcm,
            test_levenshtein_distance,
            test_luhn,
            test_max_for_subrange,
            test_maybe,
            test_merkle_damgard_hashing,
            test_nist_vectors,
            test_null_stream,
            test_breeze_prevent_macro_expansion,
            test_printable_string,
            test_readable_type_name,
            test_remove_from_end,
            test_replace_all,
            test_representation_in_base,
            test_roman,
            test_rounded_up_quotient,
            test_set_of_chars,
            test_sha384,
            test_split,
            test_stream_equivalent,
            test_breeze_stringize,
            test_breeze_stringize_after_expansion,
            test_tail,
            test_to_lowercase,
            test_to_string,
            test_to_uppercase,
            test_trim_head,
            test_trim_tail,
            test_uuid
    } ;

    int                 result = EXIT_SUCCESS ;
    for ( auto const & f : tests )
    {
        int const           exit_code = f() ;
        if ( exit_code != EXIT_SUCCESS ) {
            result = EXIT_FAILURE ;
        }
    }

    std::cout << ( result == EXIT_SUCCESS
        ? "All tests passed."
        : "At least one test FAILED." ) << std::endl ;

    //      We output the detected operating system description here,
    //      because the operating_system_name class is basically
    //      untestable. We hope that, this way, the user can notice if
    //      something is wrong.
    // -----------------------------------------------------------------------
    std::cout << "\nDetected operating system: " <<
        breeze::operating_system_name() << std::endl ;

    //      Likewise for the amount of physical memory (use floating
    //      point to let the user notice if the amount is not a multiple
    //      of 1024)...
    // -----------------------------------------------------------------------
    auto const          amount = static_cast< double >(
            breeze::amount_of_physical_memory() ) / 1024.0 ;
    std::cout << "\nAmount of physical memory in MiB: " <<
        amount << std::endl ;

    //      ... and for the last API error.
    // -----------------------------------------------------------------------
    std::cout << "\nLast API error: " <<
        breeze::last_api_error( "Unit tests" ) << '\n' << std::endl ;

    return result ;
}
