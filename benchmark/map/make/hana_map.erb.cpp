// Copyright Louis Dionne 2013-2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/map.hpp>

#include "../../at_key/pair.hpp"
namespace hana = boost::hana;


template <int i>
struct x { };

struct undefined { };

int main() {
    auto map = hana::make_map(<%=
        (1..input_size).map { |n| "light_pair<x<#{n}>, undefined>{}" }.join(', ')
    %>);
    (void)map;
}