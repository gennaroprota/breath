<!--
 =============================================================================
                         Copyright 2019 Gennaro Prota

                   Licensed under the 3-Clause BSD License.
              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
               <https://opensource.org/licenses/BSD-3-Clause>.)
 _____________________________________________________________________________
-->

# Breath - The library

Welcome. This library is my personal toolkit of C++ components. The components
range from cryptography (MD5, SHA-1, SHA-2) to string utilities, operating
system identification and much more. You'll get a precise idea by exploring the
breath/ subdirectory of the source tree.

The library has been developed over a period of about 16 years (as of June 2019)
and I don't claim that all of it is of production quality.

Some components don't take full advantage of the latest standards (e.g. they
don't use `noexcept`) and some are or will be superseded by standard components
or features (e.g. those in the path/ subdirectory). But, generally, the library
is up-to-date to C++14.

The test/ subdirectories can be a good place to look at if you need to see usage
examples (but, please, let me know if you feel that the usage of a component
should be documented better).

## Getting started

The library requires a Unix toolkit, with GNU Make and the GNU Assembler. On
Microsoft Windows, you'll need Cygwin. (If I had to redo it today, most things
would probably use Python.)

Note that only Cygwin 64-bit is supported.

For the build to work, for the editor support, and for some tests, you need to
define the environment variable `BREATH_ROOT` to the full path of the source
tree. Use forward slashes, even on Windows.

The bin/ subdirectory of the Cygwin installation must be in the `PATH`.

To build the library:

 - if you are on Windows and you want to use Visual Studio, run the Visual
   Studio Command Prompt, `cd` to `%BREATH_ROOT%/tool/use_cygwin` and launch
   `use_cygwin.bat`; then use the resulting Cygwin window

 - `cd` to `BREATH_ROOT`

 - issue a command like this:

   ```
   compiler=gcc system=windows make
   ```

The `clean` target is also supported (you still need to provide `compiler` and
`system`: when you clean, only the files generated for a given compiler/system
pair are removed).

At the moment, compiler can be any of the following:

 - gcc, clang, msvc

while system can be:

 - unix, windows

## A note about the documentation

The documentation is contained in the source files, in the form of Doxygen
comments. This keeps the code and the documentation together, and that's about
the only advantage of it. For the rest, Doxygen is one of the most disappointing
tools available, but I don't have time to migrate to something else.

Given the quality of the Doxygen output, I unwillingly recommend to mostly read
the documentation directly from the source files. In any case, to generate
separate documents, please see the `read_me` in `doc/source/`.

## Editor support

The source tree contains a .editorconfig (https://editorconfig.org/). This
support was added just recently. Before that, only Emacs and Vim were supported.

If you plan to contribute, please use `tool/init_file/init_file.sh` to
initialize your source files. You should define the environment variable
`BREATH_CONTRIBUTOR` to the name you wish you wish to appear in your copyright
notices.

If you use Vim, just source `breath.vim` from your `.vimrc` and that will take
care of running the initialization script on any file you create in
`BREATH_ROOT` or in any subdirectory.

If you use Emacs, please contribute something analogous to `breath.vim` for that
editor.

## License

Breath is made available subject to the terms of the 3-Clause BSD License,
reproduced for your convenience in the file `3_CLAUSE_BSD_LICENSE.txt`, at the
root of the source tree.

## Issues

I can't guarantee any kind of support, but if you have issues with the library,
please send me a mail describing the problem and I will try to address it as
soon as possible.

## Acknowledgments

My most heartfelt thank you goes to James Kanze, without whom I wouldn't be the
programmer that I am.


[//]: # (
 Local Variables:
 mode: markdown
 indent-tabs-mode: nil
 coding: utf-8
 End:
 vim: set ft=markdown et sts=4 sw=4:
 vim: set fenc=utf-8 nobomb:
)
