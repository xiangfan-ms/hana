// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/back.hpp>
#include <boost/hana/tuple.hpp>
namespace hana = boost::hana;


static_assert(hana::back(hana::make_tuple(1, '2', 3.3)) == 3.3, "");
#ifdef BOOST_HANA_WORKAROUND_MSVC_CONSTEXPR_NULLPTR
int p;
static_assert(hana::back(hana::make_tuple(1, '2', 3.3, &p)) == &p, "");
#else
static_assert(hana::back(hana::make_tuple(1, '2', 3.3, nullptr)) == nullptr, "");
#endif

int main() { }
