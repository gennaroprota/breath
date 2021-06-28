# ============================================================================
#                      Copyright 2013-2018 Gennaro Prota
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
#       (See gcc.mk for further notes on some options.)
#
#       -Wno-anon-enum-enum-conversion:
#
#           Silences warnings in the cryptography facilities, where we
#           use unnamed enums to define constants (so that we don't need
#           to provide a separate definition) and do arithmetic on them.
#
#           Since this warning option doesn't exist on all the Clang
#           versions we support, we also use
#           -Wno-unknown-warning-option.
#
#       -Wno-weak-vtables:
#
#           The -Wweak-vtables warning tries to point out possible
#           object file bloat, but that's probably moot either because
#           it isn't really going to make a difference with regard to
#           performance, and because the linker will likely collapse the
#           duplicated vtables anyway.
#
#           So this warning can be safely suppressed. Note, too, that it
#           would be difficult to silence it by modifying the code, as
#           in the case (as of Febrary 27, 2019) for the class
#           command_line_error, in command_line.hpp.
#
#       -Wno-zero-as-null-pointer-constant:
#
#           Silences warnings on things like:
#
#             if ( GetModuleHandle( L"kernel32" ) == NULL )
#                 ...
#
#           (we don't want to use nullptr, there). GCC seems to be
#           smarter and doesn't give such warnings when the option is
#           enabled.
#
#       -Wno-reserved-id-macro:
#
#           Introduced to be able to define _DARWIN_C_SOURCE under Mac
#           OS X (GitHub Actions)---see macos/get_amount_of_physical_memory.cpp
# ----------------------------------------------------------------------------

#       KEEP in sync! (See above.)
# ----------------------------------------------------------------------------
cpp_basic_options       := -std=c++17                           \
                           -Weverything                         \
                           -Wno-c++98-compat                    \
                           -Wno-c++98-compat-pedantic           \
                           -Werror                              \
                           -fuse-cxa-atexit                     \
                           -D _XOPEN_SOURCE=700                 \
                           -D _GLIBCXX_USE_CXX11_ABI=1

cpp_basic_options       += -finput-charset=utf-8                \
                           -pipe                                \
                                                                \
                           -Wno-unknown-warning-option          \
                                                                \
                           -Wno-anon-enum-enum-conversion       \
                           -Wno-padded                          \
                           -Wno-sign-conversion                 \
                           -Wno-unknown-pragmas                 \
                           -Wno-weak-vtables                    \
                           -Wno-zero-as-null-pointer-constant   \
                           -Wno-reserved-id-macro

#       The following three options are temporary
#       (-fcomment-block-commands=cond is a hack for Clang, which
#       doesn't seem to recognize the \cond command, although it
#       recognizes \endcond; this is better than using
#       -Wno-documentation-unknown-command, as that could hide real
#       errors). - gps
#
#       Addendum: Clang doesn't recognize \copydoc and its variants,
#       either.
# ----------------------------------------------------------------------------
cpp_basic_options       += -Wno-exit-time-destructors           \
                           -Wno-global-constructors             \
                           -fcomment-block-commands=cond,copydoc,copybrief,copydetails

#       As of September 2020, Clang's -Og is the same as -O1 but
#
#         "In future versions, this option might disable different
#         optimizations in order to improve debuggability.",
#
#       however
#
#         "-O0 Means "no optimization": this level compiles the fastest
#         and generates the most debuggable code."
#
#                                         (From the Clang documentation)
#
#       So, we use -O0 instead of -Og. (I'm not sure what -O option is
#       the default.)
#
#       For the libstdc++ macros, see:
#
#         <https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html>.
#
#       Keep in sync with gcc.mk.
# ----------------------------------------------------------------------------
cpp_debug_options       := -O0                                  \
                           -D _GLIBCXX_ASSERTIONS=1             \
                           -D _GLIBCXX_DEBUG                    \
                           -D _GLIBCXX_DEBUG_PEDANTIC

cpp_debug_options       += -ggdb3

cpp_optimize_options    := -O3 -fomit-frame-pointer -finline-functions

include_switch          := -I
object_file_suffix      := .o
additional_library_options  \
                        := $(addprefix -l,$(additional_libraries))

#       Note that this differs from the compiler name, which is in
#       $(compiler). And that, in the continuous integration (currently,
#       GitHub Actions), we often need to select a specific version
#       (e.g. clang++-8), which we do externally to this makefile: hence
#       the ifndef test.
# ----------------------------------------------------------------------------
ifndef compiler_command
    compiler_command    := clang++
endif

compiler_display_name   := Clang

#       Get the version number from --version, because Clang's
#       -dumpversion lies, for GCC compatibility.
# ----------------------------------------------------------------------------
compiler_version        := $(shell $(compiler_command) --version 2>&1 |    \
                 sed -n 's/.*version \([1-9][0-9]*\.[0-9]*\.[0-9]*\).*/\1/p' )

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
    $(compiler_command) $(cpp_options) -o $@ $+ $(additional_library_options)
endef
