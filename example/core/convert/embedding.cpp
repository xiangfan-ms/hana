// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/assert.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/when.hpp>

#include <vector>
namespace hana = boost::hana;


namespace boost { namespace hana {
    template <typename To, typename From>
    struct to_impl<std::vector<To>, std::vector<From>,
        when<is_convertible<From, To>::value>>
        : embedding<is_embedded<From, To>::value>
    {
        static std::vector<To> apply(std::vector<From> const& xs) {
            std::vector<To> result;
            for (auto const& x: xs)
                result.push_back(to<To>(x));
            return result;
        }
    };
}}

int main() {
#ifdef BOOST_HANA_WORKAROUND_MSVC_NARROWING_CONVERSION_FLOAT_616032
    BOOST_HANA_RUNTIME_CHECK(
        hana::to<std::vector<int>>(std::vector<float>{1.1f, 2.2f, 3.3f})
                        ==
        std::vector<int>{1, 2, 3}
    );
#else
    BOOST_HANA_RUNTIME_CHECK(
        hana::to<std::vector<int>>(std::vector<float>{1.1, 2.2, 3.3})
                        ==
        std::vector<int>{1, 2, 3}
    );
#endif

    static_assert(!hana::is_embedded<std::vector<float>, std::vector<int>>{}, "");
}
