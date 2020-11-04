<!--
 =============================================================================
                      Copyright 2019-2020 Gennaro Prota

                   Licensed under the 3-Clause BSD License.
              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
               <https://opensource.org/licenses/BSD-3-Clause>.)
 _____________________________________________________________________________
-->

# Overview

*GitHub repo's master branch at a glance:*

<!--    Note: if you word-wrap these links differently, make sure they
        appear correctly on <github.com>.
     -------------------------------------------------------------------------
-->
[![Build status](
https://travis-ci.com/gennaroprota/breath.svg?branch=master)](
https://travis-ci.com/gennaroprota/breath)
[![Lines of code counter](
https://tokei.rs/b1/github/gennaroprota/breath?category=code)](
https://github.com/gennaroprota/breath)
[![Lines of comment counter](
https://tokei.rs/b1/github/gennaroprota/breath?category=comments)](
https://github.com/gennaroprota/breath)

*DocsForge documentation:*

[![DocsForge documentation](
https://img.shields.io/badge/docs-docsforge-blue)](https://breath.docsforge.com)

Welcome to *Breath*, my personal toolkit of C++ components. The components range
from cryptography (MD5, SHA-1, SHA-2) to string utilities, operating system
identification and much more. You'll get a precise idea by exploring the breath/
subdirectory of the source tree or the full documentation (see below).

The library has been developed, in my spare time, over a period of about 13
years (as of June 2019) and I don't claim that all of it is of production
quality.

Some components don't take full advantage of the latest standards and some are
or will be superseded by standard components or features (e.g. those in the
path/ subdirectory). But, generally, the library is up to date with C++14.

The test/ subdirectories can be a good place to look at if you need to see usage
examples (but, please, let me know if you feel that the usage of a component
should be documented better).

# Building the library

Breath has been designed and implemented to be as portable as possible, without
a single usage of `#if`, `#ifdef` or `#ifndef` (the only conditional compilation
is for include guards), and the goal is that it can be compiled with any
conforming C++14 compiler.

Building the library, however, requires a Unix toolkit, with GNU Make and, for
the x86_64 builds only, the GNU Assembler. On Microsoft Windows, you'll need
Cygwin. (If I had to redo it today, most things would probably use Python.)

Note that only Cygwin 64-bit is supported.

For the editor support, and for some tests, you need to define the environment
variable `BREATH_ROOT` to the full path of the source tree. Use forward slashes,
even on Windows; omit the trailing slash.

The bin/ subdirectory of the Cygwin installation must be in the `PATH`.

To build the library:

 - if you are on Windows and you want to use Visual Studio, run a Visual Studio
   Command Prompt, issue the command `cd /D "%BREATH_ROOT%/tool/use_cygwin/"`
   (the `/D` option is for the case in which `%BREATH_ROOT%` is on a different
   drive) and launch `use_cygwin.bat`; then use the resulting Cygwin window

 - `cd` to `$BREATH_ROOT` (add quotes if the value of `$BREATH_ROOT` contains
   spaces)

 - issue a command like this:

   ```
   architecture=x86_64 system=windows compiler=gcc make
   ```

   *Note: on some systems, you might need to use `gmake` instead of `make`.*

The `architecture` part can be omitted for x86_64 (that's the default).

The `clean` target is also supported (you still need to provide `system` and
`compiler`: when you clean, only the files generated for a given
architecture/system/compiler triplet are removed).

At the moment, `system` must be set to one of the following:

 - unix, windows

while `compiler` must be set to one of:

 - clang, gcc, msvc

Finally, `architecture` can be anything, because it is currently only used to
include or exclude a component (get_cpuid_info()) which is only implemented for
x86_64.

Under Cygwin, with both Clang and GCC, you can build with `system=windows` or
`system=unix`. In both cases, this will, by default, generate a library which
depends on the Cygwin DLL. To avoid this dependency when `system=windows`, you
can use the compilers provided by the *mingw\*gcc\** or *mingw\*clang* packages
(available in the Cygwin installer) and select one of them via the
`compiler_command` variable; e.g.:

```
system=windows compiler=gcc compiler_command=x86_64-w64-mingw32-g++ make
```

**Warning:** you might want to also add

```
cpp_extra_options="-static -static-libgcc -static-libstdc++"
```

to the command line, but note that the `cpp_extra_options` variable is
experimental.

*Note: to get a list of the available Make targets, with a brief description for
each one, launch the command `make help` (or `gmake help`).*

# A note about the documentation

The documentation is contained in the source files, in the form of Doxygen
comments. This keeps the code and the documentation together, and that's about
the only advantage of it. For the rest, Doxygen is one of the most disappointing
tools available, but I don't have time to migrate to something else.

Given the quality of the Doxygen output, I unwillingly recommend to mostly read
the documentation directly from the source files. In any case, to generate
separate documents, a `documentation` target is provided in the makefiles
(please, remember to `cd` to `BREATH_ROOT`; the documentation will appear in
`BREATH_ROOT/doc`).

**Note on the note :-)**: I just registered the project with DocsForge; the
resulting documentation seems much better than the one generated by Doxygen,
although some interlinks are wrong. Unless you are without an Internet
connection, it might be a good alternative for you to use:
<https://breath.docsforge.com>.

# Editor support

The source tree contains a `.editorconfig` (https://editorconfig.org). This
support was added just recently. Before that, only Emacs and Vim were supported.

If you plan to contribute, please use `tool/init_file/init_file.sh` to
initialize your source files. You should define the environment variable
`BREATH_CONTRIBUTOR` to the name you wish to appear in your copyright notices.
Also, you should build the `include_guard` tool (which is automatically built
with the library: see Getting started), and copy it to `BREATH_ROOT/bin/`.

If you use Vim, just source `breath.vim` from your `.vimrc` and that will take
care of running the initialization script on any file you create in
`BREATH_ROOT` or in any subdirectory.

If you use Emacs, please contribute something analogous to `breath.vim` for that
editor.

# Git commit message template

To enable the Git commit message template provided with the library:

 - `cd` to `BREATH_ROOT`

 - run: `git config --local commit.template ./.git_commit_message_template.txt`

For better or for worse, the library uses the Git commit message guidelines
outlined at https://chris.beams.io/posts/git-commit/, except that the subject
line:

 - can reach 72 characters, just like the body lines (50 is really too little)

 - is worded in the imperative mood, but doesn't necessarily complete the
   sentence "this commit will...", e.g. it may begin with "Don't" (I believe
   that, in fact, this is the intent of the guidelines)

Please, have a look at the guidelines if you are not familiar with them.

# Supported compilers

Note that, as of August 24, 2020, if you need to use the library with MSVC 2015,
that's quite easy as long as you are willing to give up on `constexpr` for some
components (`BREATH_ASSERT()`, `count_bits()`, `gcd()`, `lcm()`).

Compiler | Minimum supported version
---------|----------------------------
Clang    | 5.0.1
GCC      | 6.1.0
MSVC     | 2017

# Future directions

The facilities for command line options will be removed and replaced with
something better. They came from another library, and seemed good at the time,
but, on closer analysis, show their limitations.

# License

Breath is made available subject to the terms of the 3-Clause BSD License,
reproduced in the file `3_CLAUSE_BSD_LICENSE.txt`, at the root of the source
tree.

# Reporting issues

I can't guarantee any kind of support, but if you have issues with the library,
please send me a mail describing the problem (*name.surname*@gmail.com) and I
will try to address it as soon as possible.

# Acknowledgments

My most heartfelt *thank you* goes to James Kanze, without whom I wouldn't be
the programmer I am.

[//]: # (
 Local Variables:
 mode: markdown
 indent-tabs-mode: nil
 coding: utf-8
 End:
 vim: set ft=markdown et sts=4 sw=4:
 vim: set fenc=utf-8 nobomb:
)
