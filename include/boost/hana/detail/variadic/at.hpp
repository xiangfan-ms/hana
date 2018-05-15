/*!
@file
Defines `boost::hana::detail::variadic::at`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_AT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_AT_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
#ifdef BOOST_HANA_WORKAROUND_MSVC_PACKEXPANSION_DECLTYPE_616024
    template<std::size_t> struct at_ignore_function_parameter_helper { using type = void *; };
#endif

    template <std::size_t n, typename = std::make_index_sequence<n>>
    struct at_type;

    template <std::size_t n, std::size_t ...ignore>
    struct at_type<n, std::index_sequence<ignore...>> {
    private:
        template <typename Nth>
#ifdef BOOST_HANA_WORKAROUND_MSVC_PACKEXPANSION_DECLTYPE_616024
        static constexpr auto go(typename at_ignore_function_parameter_helper<ignore>::type..., Nth nth, ...)
#else
        static constexpr auto go(decltype(ignore, (void*)0)..., Nth nth, ...)
#endif
        { return nth; }

    public:
        template <typename ...Xs>
        constexpr auto operator()(Xs ...xs) const
        { return *go(&xs...); }
    };

    template <std::size_t n>
    constexpr at_type<n> at{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_AT_HPP
