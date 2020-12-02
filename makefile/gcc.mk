# ============================================================================
#                      Copyright 2007-2019 Gennaro Prota
#                         Copyright 2004 James Kanze
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

#       Maintenance note:
#       -----------------
#
#       Be sure that modifications to these options don't put the
#       various compiler-specific makefiles out of sync (e.g. by
#       requiring C++14 with one compiler and C++17 with another).
#
#
#       As usual, the options are listed in two groups. The group
#       appearing first relates mainly to standards conformance. The
#       other group contains other options in alphabetical order.
#
#       Special notes for some of the options:
#       ======================================
#
#       -D _GLIBCXX_USE_CXX11_ABI=1:
#
#           enables the new implementations of std::string and
#           std::list, which conform to C++11; for more details, see:
#
#             <https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dual_abi.html>.
#
#       -Wsign-conversion [not used]:
#
#           this simply gives too many false positives.
#
#       -Wno-format-nonliteral:
#
#           our time_string() facility relies on passing a non-literal
#           to std::strftime().
#
#       -Wstrict-overflow [not used]
#
#           we used -Wstrict-overflow=5 for a while, and we didn't notice any
#           problem because we weren't doing optimized builds; when we did, we
#           got a warning in set_of_chars::iterator::increment() until we
#           switched to -Wstrict-overflow=2, and another one in
#           binary_to_base64() until we switched to -Wstrict-overflow=1. But
#           -Wstrict-overflow=1 is enabled by -Wall, so we just dropped the
#           option.
#
#           I couldn't see a way to avoid the warnings by massaging the code.
#
#           (Problems encountered with GCC 7.4.0 and -O3.)
#
#       -pipe:
#
#           just an optimization, "but it can also allow compilations to
#           succeed even when the space on /tmp is tight.  (It's a very
#           important optimization on Unix systems, because it reduces
#           pressure on the disk cache.)
#
#           On a multi-core machine, -pipe also runs a lot faster, since
#           it allows the back end to generate code for one function
#           while the front end is parsing the next" (insights provided
#           by James Kanze).
# ----------------------------------------------------------------------------


#       This check on the minimum compiler version was implemented
#       thanks to Jonathan Wakely.
#
#       Note:
#           when incrementing the minimum version number, check:
#
#             <https://gcc.gnu.org/wiki/WarningHistory>
#
#           to see if there are useful switches that can be enabled.
#
#           For the moment, I've seen:
#
#           -Waligned-new=all      (introduced in GCC 7.1.0)
#           -Wcast-align=strict    (    "       "  "  8.1.0)  (note1)
#           -Wcatch-value=2        (    "       "  "  8.1.0)
#           -Wduplicated-branches  (    "       "  "  7.2.0)
#
#       ---
#       note1 This will replace -Wcast-align
# ----------------------------------------------------------------------------
minimum_gcc_version := 6.1.0

#       Note that this differs from the compiler name, which is in
#       $(compiler). See also the comment about the analogous statement
#       in clang.mk.
# ----------------------------------------------------------------------------
ifndef compiler_command
    compiler_command := g++
endif

compiler_display_name := GCC

#       Note:
#           starting from GCC 7 -dumpversion might print the major
#           version only, and we need -dumpfullversion to print the
#           major.minor.patch version (this depends on the
#           --with-gcc-major-version-only configure option). This
#           insight is from Jonathan Wakely, as well.
# ----------------------------------------------------------------------------
compiler_version := $(shell $(compiler_command) -dumpfullversion 2>/dev/null \
                        || $(compiler_command) -dumpversion)

lowest_version := $(shell                                            \
  printf '%s\n%s\n' $(minimum_gcc_version) $(compiler_version)  |    \
  sort -t . -k 1,1n -k 2,2n -k 3,3n | head -1                        \
  )

ifneq "$(lowest_version)" "$(minimum_gcc_version)"
    $(error You are using GCC $(compiler_version) but the minimum \
            supported version is $(minimum_gcc_version))
endif

#       KEEP in sync! (See above.)
# ----------------------------------------------------------------------------
cpp_basic_options := -std=c++14                      \
                     -Wall                           \
                     -Wextra                         \
                     -pedantic                       \
                     -Werror                         \
                     -fuse-cxa-atexit                \
                     -D _POSIX_C_SOURCE=200809L      \
                     -D _GLIBCXX_USE_CXX11_ABI=1

cpp_basic_options += -flto-odr-type-merging          \
                     -pipe                           \
                     -Warray-bounds=2                \
                     -Wcast-align                    \
                     -Wconditionally-supported       \
                     -Wconversion                    \
                     -Wdate-time                     \
                     -Wdelete-non-virtual-dtor       \
                     -Wdouble-promotion              \
                     -Wduplicated-cond               \
                     -Wfloat-equal                   \
                     -Wformat=2                      \
                     -Wformat-signedness             \
                     -Winvalid-pch                   \
                     -Wlogical-op                    \
                     -Wmissing-declarations          \
                     -Wmissing-include-dirs          \
                     -Wnoexcept                      \
                     -Wnon-virtual-dtor              \
                     -Wnull-dereference              \
                     -Wold-style-cast                \
                     -Woverloaded-virtual            \
                     -Wplacement-new=2               \
                     -Wredundant-decls               \
                     -Wshadow                        \
                     -Wshift-overflow=2              \
                     -Wstack-usage=16384             \
                     -Wstrict-null-sentinel          \
                     -Wsuggest-attribute=noreturn    \
                     -Wsuggest-override              \
                     -Wswitch-enum                   \
                     -Wsync-nand                     \
                     -Wundef                         \
                     -Wunreachable-code              \
                     -Wunused-const-variable         \
                     -Wunused-macros                 \
                     -Wuseless-cast                  \
                     -Wzero-as-null-pointer-constant

cpp_basic_options += -Wno-format-nonliteral

#       See:
#       <https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html>.
#
#       Keep in sync with clang.mk.
# ----------------------------------------------------------------------------
cpp_debug_options := -D _GLIBCXX_ASSERTIONS=1        \
                     -D _GLIBCXX_CONCEPT_CHECKS      \
                     -D _GLIBCXX_DEBUG               \
                     -D _GLIBCXX_DEBUG_PEDANTIC

cpp_debug_options += -ggdb3

include_switch := -I
object_file_suffix := .o

define compile_to_object
    $(compiler_command) $(cpp_options) -c -o $@ $<
endef

define compile_to_dependency
    $(compiler_command) $(cpp_options) -MT $@ -M -MP            \
                        -MF $(dependency_dir)/$*.temp_dep $<
endef

define build_library
    rm -f $@
    ar -rc $@ $^
endef

define link_to_exec
    $(compiler_command) $(cpp_options) -o $@ $+
endef

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
