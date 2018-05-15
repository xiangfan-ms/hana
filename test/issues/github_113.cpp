// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/adapt_struct.hpp>
#include <boost/hana/define_struct.hpp>
namespace hana = boost::hana;


#ifndef BOOST_HANA_WORKAROUND_MSVC_PARSEQNAME_616018_DISABLETEST
struct Person {
    BOOST_HANA_DEFINE_STRUCT(Person,
        (int, Person)
    );
};

struct Employee {
    int Employee;
};

BOOST_HANA_ADAPT_STRUCT(Employee, Employee);
#endif

int main() { }
