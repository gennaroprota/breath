# ============================================================================
#                      Copyright 2016-2020 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

include $(root)/makefile/main.mk

object_files  := $(patsubst                                 \
                    %.cpp,                                  \
                    $(bin_dir)/%$(object_file_suffix),      \
                    $(source_files))
exe_base_name := $(shell basename "$(shell pwd)")
target        := $(bin_dir)/$(exe_base_name)$(exe_name_suffix)


.PHONY: all
all: $(target)

breeze_library := $(bin_dir)/$(library_name_prefix)breeze$(library_name_suffix)

$(target): $(object_files) $(breeze_library)
	$(link_to_exec)

.PHONY: clean
clean:
	rm -fr $(dependency_dir)
	rm -f  $(object_files)
	rm -f  $(target)
