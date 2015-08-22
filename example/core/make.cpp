/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/tuple.hpp>

#include <string>
namespace hana = boost::hana;


int main() {
    hana::tuple<int, char, double, std::string> ts{1, '2', 3.3, "abcd"};
    BOOST_HANA_RUNTIME_CHECK(ts == hana::make_tuple(1, '2', 3.3, std::string{"abcd"}));

    // std::string has no notion of data type, but it still works with make<>
    std::string foo{"foo"};
    BOOST_HANA_RUNTIME_CHECK(hana::make<std::string>("foo") == foo);
}