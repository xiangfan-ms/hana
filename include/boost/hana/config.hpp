/*!
@file
Defines configuration macros used throughout the library.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONFIG_HPP
#define BOOST_HANA_CONFIG_HPP

#include <boost/hana/version.hpp>


//////////////////////////////////////////////////////////////////////////////
// Detect the compiler
//////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && !defined(__clang__) // MSVC
    // This must be checked first, because otherwise it produces a fatal
    // error due to unrecognized #warning directives used below.
#if _MSC_FULL_VER < 191426428
#   pragma message("Warning: the native Microsoft compiler is not supported due to lack of proper C++14 support.")
#endif

// Active issues
// Multiple copy/move ctors
#define BOOST_HANA_WORKAROUND_MSVC_MULTIPLECTOR_106654
// Generic lambda and sizeof...
//   test\type\is_valid.cpp
#define BOOST_HANA_WORKAROUND_MSVC_GENERIC_LAMBDA_RETURN_TYPE_269943
// Return type of generic lambda is emitted as a type token directly after pre-parsing
#define BOOST_HANA_WORKAROUND_MSVC_GENERIC_LAMBDA_RETURN_TYPE_610227
// Pack expansion of decltype
//   test\detail\variadic\at.cpp
//   test\detail\variadic\drop_into.cpp
#define BOOST_HANA_WORKAROUND_MSVC_PACKEXPANSION_DECLTYPE_616024
// Variadic macro expansion
#define BOOST_HANA_WORKAROUND_MSVC_PREPROCESSOR_616033
// constexpr function isn't evaluated correctly in SFINAE context
#define BOOST_HANA_WORKAROUND_MSVC_SFINAE_CONSTEXPR_616157
// RDParser incorrectly parses a comparison operation as a template id
#define BOOST_HANA_WORKAROUND_MSVC_RDPARSER_TEMPLATEID_616568

// Issues fixed in 15.8
#if _MSC_VER < 1915
// Fixed by commit f4e60b2ecc169b0a5ec51d713125801adae24bc2, 20180323
// Note, the workaround requires /Zc:externConstexpr
#define BOOST_HANA_WORKAROUND_MSVC_NONTYPE_TEMPLATE_PARAMETER_INTERNAL

// Fixed by commit c9999d916f1d73bc852de709607b2ca60e76a4c9, 20180513
#define BOOST_HANA_WORKAROUND_MSVC_CONSTEXPR_NULLPTR
#define BOOST_HANA_WORKAROUND_MSVC_CONSTEXPR_ARRAY_399280

// error C2131: expression did not evaluate to a constant
//   test\_include\auto\for_each.hpp
#define BOOST_HANA_WORKAROUND_MSVC_FOR_EACH_DISABLETEST

//   test\functional\placeholder.cpp
#define BOOST_HANA_WORKAROUND_MSVC_CONSTEXPR_ADDRESS_DISABLETEST
#define BOOST_HANA_WORKAROUND_MSVC_CONSTEXPR_ARRAY_DISABLETEST

// Fixed by commit 5ef87ec5d20b45552784a40fe455c04c257c7b08, 20180516
// Generic lambda preparsing and static capture
#define BOOST_HANA_WORKAROUND_MSVC_GENERIC_LAMBDA_NAME_HIDING_616190

// Fixed by commit 9c4869e61b5ad301f1fe265193241d2c74729a1c, 20180518
// ICE when try to give warning on the format string for printf
//   example\misc\printf.cpp
#define BOOST_HANA_WORKAROUND_MSVC_PRINTF_WARNING_506518

// Fixed by commit 095130d02c8805517bbaf93d92415041eecbca00, 20180521
// decltype behavior difference when comparing character array and std::string
//   test\orderable.cpp
#define BOOST_HANA_WORKAROUND_MSVC_DECLTYPE_ARRAY_616099

// Fixed by commit a488f9dccbfb4ceade4104c0d8d00e25d6ac7d88, 20180521
// Member with array type
//   test\issues\github_365.cpp
#define BOOST_HANA_WORKAROUND_MSVC_GITHUB365_DISABLETEST

// Fixed by commit 7a572ef6535746f1cee5adaa2a41edafca6cf1bc, 20180522
// Member with the same name as the enclosing class
//   test\issues\github_113.cpp
#define BOOST_HANA_WORKAROUND_MSVC_PARSEQNAME_616018_DISABLETEST

// Fixed by commit 3c9a06971bf4c7811db1a21017ec509a56d60e59, 20180524
#define BOOST_HANA_WORKAROUND_MSVC_VARIABLE_TEMPLATE_EXPLICIT_SPECIALIZATION_616151

// error C3520: 'Args': parameter pack must be expanded in this context
//   example\tutorial\integral-branching.cpp
#define BOOST_HANA_WORKAROUND_MSVC_LAMBDA_CAPTURE_PARAMETERPACK_616098_DISABLETEST

// Fixed by commit 5b1338ce09f7827e5b9248bcba2f519043044fef, 20180529
// Narrowing warning on constant float
//   example\core\convert\embedding.cpp
#define BOOST_HANA_WORKAROUND_MSVC_NARROWING_CONVERSION_FLOAT_616032

// Fixed by commit be8778ab26957ae7c6a36376a9ae2d049d64a095, 20180611
// Pack expansion of decltype
//   example\hash.cpp
#define BOOST_HANA_WORKAROUND_MSVC_PACKEXPANSION_DECLTYPE_616094

// Fixed by commit 5fd2bf807a0320167c72d9960b32d823a634c04d, 20180613
// Parser error when using '{}' in template arguments
#define BOOST_HANA_WORKAROUND_MSVC_PARSE_BRACE_616118

// Fixed by commit 120bb866980c8a1abcdd41653fa084d6c8bcd327, 20180615
// Nested generic lambda
//   test\index_if.cpp
#define BOOST_HANA_WORKAROUND_MSVC_NESTED_GENERIC_LAMBDA_615453

// Fixed by commit 884bd374a459330721cf1d2cc96d231de3bc68f9, 20180615
// Explicit instantiation involving decltype
//   example\tutorial\introspection.cpp
#define BOOST_HANA_WORKAROUND_MSVC_DECLTYPE_EXPLICIT_SPECIALIZATION_508556
#endif

// Issues fixed conditionally
// Requires __declspec(empty_bases)
#define BOOST_HANA_WORKAROUND_MSVC_EMPTYBASE

// Source issues
#define BOOST_HANA_WORKAROUND_MSVC_IS_CONVERTIBLE_INCOMPLETE_TAG
#define BOOST_HANA_WORKAROUND_MSVC_TYPEID_RESULT

// Boost related issues

// For the related tests to pass, the following logic in boost 1.64 should be updated:
//
//   boost\fusion\container\deque\deque_fwd.hpp
//   boost\fusion\container\map\map_fwd.hpp
//
//   // MSVC variadics at this point in time is not ready yet (ICE!)
//   #if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1900))
//   # if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
//   #   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
//   # endif
//   #endif
//
// In boost 1.67, the condition is changed to
//
//   #if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
//
// Otherwise 'test\ext\boost\fusion\deque\auto\_specs.hpp' needs to define something like
//   #define FUSION_MAX_VECTOR_SIZE 50
//
// Impacted tests:
//   test\ext\boost\fusion\deque\auto
//#define BOOST_HANA_WORKAROUND_MSVC_BOOST_FUSION_DEQUE_SIZE

// BOOST_HANA_CONFIG_ENABLE_STRING_UDL requires GNU extension
// BOOST_HANA_STRING requires C++17 because of constexpr lambdas
#if _MSVC_LANG > 201402
// Use BOOST_HANA_STRING if /std:c++17 is used
#define BOOST_HANA_WORKAROUND_MSVC_NO_STRING_UDL
#endif

// boost::mpl::aux::vector_tag depends on BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES
// It is a class if the macro is defined.
// It is a class template if the macro is not defined
#define BOOST_HANA_WORKAROUND_MSVC_MPL_NO_TYPEOF

#elif defined(__clang__) && defined(_MSC_VER) // Clang-cl (Clang for Windows)

#   define BOOST_HANA_CONFIG_CLANG BOOST_HANA_CONFIG_VERSION(               \
                    __clang_major__, __clang_minor__, __clang_patchlevel__)

#   if BOOST_HANA_CONFIG_CLANG < BOOST_HANA_CONFIG_VERSION(3, 5, 0)
#       warning "Versions of Clang prior to 3.5.0 are not supported by Hana."
#   endif

#   if _MSC_VER < 1900
#       warning "Clang-cl is only supported with the -fms-compatibility-version parameter set to 19 and above."
#   endif

#elif defined(__clang__) && defined(__apple_build_version__) // Apple's Clang

#   if __apple_build_version__ >= 6020049
#       define BOOST_HANA_CONFIG_CLANG BOOST_HANA_CONFIG_VERSION(3, 6, 0)
#   else
#       warning "Versions of Apple's Clang prior to the one shipped with Xcode 6.3 are not supported by Hana."
#   endif

#elif defined(__clang__) // genuine Clang

#   define BOOST_HANA_CONFIG_CLANG BOOST_HANA_CONFIG_VERSION(               \
                __clang_major__, __clang_minor__, __clang_patchlevel__)

#   if BOOST_HANA_CONFIG_CLANG < BOOST_HANA_CONFIG_VERSION(3, 5, 0)
#       warning "Versions of Clang prior to 3.5.0 are not supported by Hana."
#   endif

#elif defined(__GNUC__) // GCC

#   define BOOST_HANA_CONFIG_GCC BOOST_HANA_CONFIG_VERSION(                 \
                            __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)

#   if BOOST_HANA_CONFIG_GCC < BOOST_HANA_CONFIG_VERSION(6, 0, 0)
#       warning "Versions of GCC prior to 6.0.0 are not supported by Hana."
#   endif

#else

#   warning "Your compiler is not officially supported by Hana or it was not detected properly."

#endif

//////////////////////////////////////////////////////////////////////////////
// Check the compiler for general C++14 capabilities
//////////////////////////////////////////////////////////////////////////////
#if (__cplusplus < 201400)
#   if defined(_MSC_VER)
#if _MSC_FULL_VER < 191426428
#       pragma message("Warning: Your compiler doesn't provide C++14 or higher capabilities. Try adding the compiler flag '-std=c++14' or '-std=c++1y'.")
#endif
#   else
#       warning "Your compiler doesn't provide C++14 or higher capabilities. Try adding the compiler flag '-std=c++14' or '-std=c++1y'."
#   endif
#endif

//////////////////////////////////////////////////////////////////////////////
// Detect the standard library
//////////////////////////////////////////////////////////////////////////////

// We include this header, which normally defines the proper detection macros.
// At least, libc++ and libstdc++ do.
#include <cstddef>

#if defined(_LIBCPP_VERSION)

#   define BOOST_HANA_CONFIG_LIBCPP BOOST_HANA_CONFIG_VERSION(              \
                ((_LIBCPP_VERSION) / 1000) % 10, 0, (_LIBCPP_VERSION) % 1000)

#   if BOOST_HANA_CONFIG_LIBCPP < BOOST_HANA_CONFIG_VERSION(1, 0, 101)
#       warning "Versions of libc++ prior to the one shipped with Clang 3.5.0 are not supported by Hana."
#   endif

#elif defined(__GLIBCXX__)

// We do not define a macro to keep track of libstdc++'s version, because
// we have no scalable way of associating a value of __GLIBCXX__ to the
// corresponding GCC release. Instead, we just check that the release date
// of the libstdc++ in use is recent enough, which should indicate that it
// was released with a GCC >= 5.1, which in turn indicates good enough C++14
// support.
#   if __GLIBCXX__ < 20150422 // --> the libstdc++ shipped with GCC 5.1.0
#       warning "Versions of libstdc++ prior to the one shipped with GCC 5.1.0 are not supported by Hana for lack of full C++14 support."
#   endif

#   define BOOST_HANA_CONFIG_LIBSTDCXX

#elif defined(_MSC_VER)

#   define BOOST_HANA_CONFIG_LIBMSVCCXX

#else

#   warning "Your standard library is not officially supported by Hana or it was not detected properly."

#endif


//////////////////////////////////////////////////////////////////////////////
// Caveats and other compiler-dependent options
//////////////////////////////////////////////////////////////////////////////

// `BOOST_HANA_CONFIG_HAS_CONSTEXPR_LAMBDA` enables some constructs requiring
// `constexpr` lambdas, which are in the language starting with C++17.
//
// Always disabled for now because Clang only has partial support for them
// (captureless lambdas only).
#if defined(__cplusplus) && __cplusplus > 201402L
#   define BOOST_HANA_CONSTEXPR_STATELESS_LAMBDA constexpr
// #   define BOOST_HANA_CONFIG_HAS_CONSTEXPR_LAMBDA
#else
#   define BOOST_HANA_CONSTEXPR_STATELESS_LAMBDA /* nothing */
#endif

// `BOOST_HANA_CONSTEXPR_LAMBDA` expands to `constexpr` if constexpr lambdas
// are supported and to nothing otherwise.
#if defined(BOOST_HANA_CONFIG_HAS_CONSTEXPR_LAMBDA)
#   define BOOST_HANA_CONSTEXPR_LAMBDA constexpr
#else
#   define BOOST_HANA_CONSTEXPR_LAMBDA /* nothing */
#endif

// There's a bug in std::tuple_cat in libc++ right now.
// See http://llvm.org/bugs/show_bug.cgi?id=22806.
#if defined(BOOST_HANA_CONFIG_LIBCPP)
#   define BOOST_HANA_CONFIG_LIBCPP_HAS_BUG_22806
#endif

//////////////////////////////////////////////////////////////////////////////
// Namespace macros
//////////////////////////////////////////////////////////////////////////////
#define BOOST_HANA_NAMESPACE_BEGIN namespace boost { namespace hana {

#define BOOST_HANA_NAMESPACE_END }}

//////////////////////////////////////////////////////////////////////////////
// Library features and options that can be tweaked by users
//////////////////////////////////////////////////////////////////////////////

#if defined(BOOST_HANA_DOXYGEN_INVOKED) || \
    (defined(NDEBUG) && !defined(BOOST_HANA_CONFIG_DISABLE_ASSERTIONS))
    //! @ingroup group-config
    //! Disables the `BOOST_HANA_*_ASSERT` macro & friends.
    //!
    //! When this macro is defined, the `BOOST_HANA_*_ASSERT` macro & friends
    //! are disabled, i.e. they expand to nothing.
    //!
    //! This macro is defined automatically when `NDEBUG` is defined. It can
    //! also be defined by users before including this header or defined on
    //! the command line.
#   define BOOST_HANA_CONFIG_DISABLE_ASSERTIONS
#endif

#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    //! @ingroup group-config
    //! Disables concept checks in interface methods.
    //!
    //! When this macro is not defined (the default), tag-dispatched methods
    //! will make sure the arguments they are passed are models of the proper
    //! concept(s). This can be very helpful in catching programming errors,
    //! but it is also slightly less compile-time efficient. You should
    //! probably always leave the checks enabled (and hence never define this
    //! macro), except perhaps in translation units that are compiled very
    //! often but whose code using Hana is modified very rarely.
#   define BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
#endif

#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    //! @ingroup group-config
    //! Enables usage of the "string literal operator template" GNU extension.
    //!
    //! That operator is not part of the language yet, but it is supported by
    //! both Clang and GCC. This operator allows Hana to provide the nice `_s`
    //! user-defined literal for creating compile-time strings.
    //!
    //! When this macro is not defined, the GNU extension will be not used
    //! by Hana. Because this is a non-standard extension, the macro is not
    //! defined by default.
#   define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#endif

#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    //! @ingroup group-config
    //! Enables additional assertions and sanity checks to be done by Hana.
    //!
    //! When this macro is defined (it is __not defined__ by default),
    //! additional sanity checks may be done by Hana. These checks may
    //! be costly to perform, either in terms of compilation time or in
    //! terms of execution time. These checks may help debugging an
    //! application during its initial development, but they should not
    //! be enabled as part of the normal configuration.
#   define BOOST_HANA_CONFIG_ENABLE_DEBUG_MODE
#endif

#endif // !BOOST_HANA_CONFIG_HPP
