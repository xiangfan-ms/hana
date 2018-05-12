// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/assert.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/ext/boost/tuple.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/transform.hpp>

#include <boost/tuple/tuple.hpp>

#include <string>
namespace hana = boost::hana;


#ifdef BOOST_HANA_WORKAROUND_MSVC_DECLTYPE_ARRAY
BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <std::size_t N>
    struct EqualityComparable<std::string, char[N], void> : std::true_type {
    };
    template <std::size_t N>
    struct EqualityComparable<char[N], std::string, void> : std::true_type {
    };
} } }
#endif

struct Fish { std::string name; };
struct Cat  { std::string name; };
struct Dog  { std::string name; };

int main() {
    boost::tuple<Fish, Cat, Dog> animals{{"Nemo"}, {"Garfield"}, {"Snoopy"}};
    hana::front(animals).name = "Moby Dick";

    auto names = hana::transform(animals, [](auto a) {
      return a.name;
    });

    BOOST_HANA_RUNTIME_CHECK(hana::equal(
        names,
        boost::make_tuple("Moby Dick", "Garfield", "Snoopy")
    ));
}
