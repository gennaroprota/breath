// ===========================================================================
//                     Copyright 2010-2019 Gennaro Prota
//                      Copyright 1997-2000 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A singleton class to manage the overall status of the
//!            program and its termination.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_1kA1ToNG1qsz9KwlXD9MfVvhaHxMym5b
#define BREEZE_GUARD_1kA1ToNG1qsz9KwlXD9MfVvhaHxMym5b

#include "breeze/top_level_namespace.hpp"
#include "breeze/process/exit_code.hpp"
#include "breeze/vocabulary/maybe.hpp"
#include <string>

namespace breeze_ns {

//      program:
//      ========
//
//!     \copybrief program.hpp
// ---------------------------------------------------------------------------
class program
{
public:
    //!     The gravity of an error.
    //
    //      NOTE: keep the enumeration in sync with the exit_codes[]
    //            array in the implementation file.
    // -----------------------------------------------------------------------
    enum gravity
    {
        comment = 0, // equivalent to success
        warning,
        error,
        fatal,
        internal
    } ;

    //!     Deleted copy constructor (this class is a singleton).
    // -----------------------------------------------------------------------
                        program(    program const & ) = delete ;

    //!     Deleted copy assignment operator (this class is a singleton).
    // -----------------------------------------------------------------------
    program &           operator =( program const & ) = delete ;

    //!     \return
    //!         A reference to the one and only instance of the class.
    // -----------------------------------------------------------------------
    static program &    instance() noexcept ;

    //!     \return
    //!         An integer to be passed to \c std::exit() or returned
    //!         from \c main(). This corresponds to the most severe
    //!         error reported by client code to the \c program class
    //!         through the \c declare_error() member function.
    //!
    //!     If possible, the various gravities will be distinguished in
    //!     the exit code, but e.g. \c warning will be undistinguishable
    //!     from a success with no warnings on Windows and Unix (because
    //!     treating a distinct value as success would be too difficult
    //!     in a shell script); in the worst case, all you get is \c
    //!     EXIT_SUCCESS or \c EXIT_FAILURE.
    //!
    //!     <strong>Important</strong>: this function also attempts to
    //!     flush \c std::cout, and calls \c declare_error( fatal ) if
    //!     the flush fails (for this reason, it is not \c const).
    // -----------------------------------------------------------------------
    int                 exit_code() ;

    //!     Sets the program name from the arguments to \c main(), if
    //!     <tt>argv[ 0 ]</tt> points to a non-empty name (i.e. if
    //!     <tt>argc > 0 && argv[ 0 ][ 0 ] != '\0'</tt>). Otherwise does
    //!     nothing.
    //!
    //!     If the name is set, any leading path is stripped.
    //!
    //!     \pre
    //!         No name was set before
    //!
    //!     \post
    //!         \e none
    // -----------------------------------------------------------------------
    void                set_name( int argc, char const * const * argv ) ;

    //!     Sets the program name from the arguments to \c main(), if
    //!     <tt>argv[ 0 ]</tt> points to a non-empty name; otherwise
    //!     sets it from \c fallback.
    //!
    //!     In any case, any leading path is stripped.
    //!
    //!     \pre
    //!         <tt>! fallback.empty()</tt> and no name was set before
    //!
    //!     \post
    //!         <tt>name().is_valid()</tt>
    // -----------------------------------------------------------------------
    void                set_name( int argc, char const * const * argv,
                                  std::string const & fallback ) ;

    //!     Sets the program name to \c name, with any leading path
    //!     stripped.
    //!
    //!     \pre
    //!         <tt>! name.empty()</tt> and no name was set before
    //!
    //!     \post
    //!         <tt>name().is_valid()</tt>
    // -----------------------------------------------------------------------
    void                set_name( std::string const & name ) ;

    //!     \return
    //!         The program name set by \c set_name(). An invalid \c
    //!         maybe if the name was never set.
    // -----------------------------------------------------------------------
    maybe< std::string >
                        name() const ;

    //!     Declares a program error.
    //!
    //!     \param g
    //!         The gravity of the error. If the gravity is higher
    //!         than any seen previously, it is saved to be used in
    //!         \c exit_code().
    //!
    //!     If the gravity is \c fatal or higher, this will also
    //!     terminate the program by calling \c program::terminate()
    //!     (when the gravity is \c fatal) or \c std::abort() (when it
    //!     is \c internal).
    // -----------------------------------------------------------------------
    void                declare_error( gravity g ) ;

    //!     Triggers the termination of the program with the exit
    //!     code which corresponds to the maximum value seen until
    //!     now. This function calls the function specified by
    //!     set_terminate_handler(), if set_terminate_handler() has
    //!     been called; otherwise, it calls \c std::exit().
    // -----------------------------------------------------------------------
    [[ noreturn ]] void terminate() ;

    //!     Sets \c *user_function as the "terminate handler", i.e. as
    //!     the function which is called, with the exit code as an
    //!     argument, if there is a fatal error or if the user calls
    //!     \c program::terminate(). This makes it possible for the user
    //!     to avoid calling the default terminate handler, which is \c
    //!     std::exit() (and thus to avoid \e not calling destructors of
    //!     local objects), for example, by raising an exception with the
    //!     argument, having taken the precaution to encapsulate the
    //!     entire contents of \c main() with:
    //!
    //!     \code
    //!         try {
    //!             breeze::program::instance().set_terminate_handler(
    //!                                             raise_int_exception ) ;
    //!             // ...
    //!         } catch ( int exit_code ) {
    //!             return exit_code ;
    //!         }
    //!     \endcode
    //!
    //!     \note
    //!         The terminate handler should not return, or \c
    //!         std::abort() will be called immediately after.
    // -----------------------------------------------------------------------
    void                set_terminate_handler( void (*user_function)( int ) ) ;

private:
                        program() noexcept ;
    void                do_set_name( std::string const & name ) ;

    gravity             m_max_gravity ;
    maybe< std::string >
                        m_program_name ;
    void (*             m_terminate_handler)( int ) ;
} ;

}

#endif
