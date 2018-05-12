// Copyright Jason Rice 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/assert.hpp>
#include <boost/hana/experimental/printable.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/type.hpp>

#include <sstream>
namespace hana = boost::hana;

namespace foo {
    template <typename T> struct my_template { };
    template <typename ...> struct my_mf { struct type; };
    struct my_mf_class { template <typename ...> struct apply { struct type; }; };
}

int main() {
    {
        std::ostringstream ss;
        ss << hana::experimental::print(
            hana::template_<foo::my_template>
        );
#ifdef BOOST_HANA_WORKAROUND_MSVC_TYPEID_RESULT
        BOOST_HANA_RUNTIME_CHECK(ss.str() == "struct boost::hana::template_t<struct foo::my_template>");
#else
        BOOST_HANA_RUNTIME_CHECK(ss.str() == "template<foo::my_template>");
#endif
    }
    {
        std::ostringstream ss;
        ss << hana::experimental::print(
            hana::metafunction<foo::my_mf>
        );
#ifdef BOOST_HANA_WORKAROUND_MSVC_TYPEID_RESULT
        BOOST_HANA_RUNTIME_CHECK(ss.str() == "struct boost::hana::metafunction_t<struct foo::my_mf>");
#else
        BOOST_HANA_RUNTIME_CHECK(ss.str() == "metafunction<foo::my_mf>");
#endif
    }
    {
        std::ostringstream ss;
        ss << hana::experimental::print(
            hana::metafunction_class<foo::my_mf_class>
        );
#ifdef BOOST_HANA_WORKAROUND_MSVC_TYPEID_RESULT
        BOOST_HANA_RUNTIME_CHECK(ss.str() == "struct boost::hana::metafunction_class_t<struct foo::my_mf_class>");
#else
        BOOST_HANA_RUNTIME_CHECK(ss.str() == "metafunction_class<foo::my_mf_class>");
#endif
    }
}
