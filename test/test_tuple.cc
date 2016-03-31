#include <tuple>
#include <typeinfo>

#include <gtest/gtest.h>
#include <Python.h>

#include "libpy/libpy.h"

using namespace py;

TEST(Tuple, type) {
    ASSERT_EQ((PyObject*) tuple::type, (PyObject*) &PyTuple_Type);

    {
        auto t = tuple::type();

        EXPECT_EQ((PyObject*) t.type(), (PyObject*) &PyTuple_Type);
        EXPECT_TRUE((t == tuple::pack()).istrue());
    }
    {
        auto t = tuple::type(tuple::pack(0_p, 1_p));

        EXPECT_EQ((PyObject*) t.type(), (PyObject*) &PyTuple_Type);
        EXPECT_TRUE((t == tuple::pack(0_p, 1_p)).istrue());
    }
}

TEST(Tuple, object_indexing) {
    std::array<object, 3> expected = {0_p, 1_p, 2_p};
    auto ob = tuple::pack(0_p, 1_p, 2_p);

    ASSERT_EQ(ob.len(), 3);
    for (const auto &n : expected) {
        EXPECT_EQ((PyObject*) ob[n], (PyObject*) n);
    }
}

TEST(Tuple, ssize_t_indexing) {
    std::array<object, 3> expected = {0_p, 1_p, 2_p};
    auto ob = tuple::pack(0_p, 1_p, 2_p);

    ASSERT_EQ(ob.len(), 3);
    for (ssize_t n : {0, 1, 2}) {
        EXPECT_TRUE(ob[n].is(expected[n]));
    }
}

TEST(Tuple, iteration) {
    std::array<object, 3> expected = {0_p, 1_p, 2_p};
    auto ob = tuple::pack(0_p, 1_p, 2_p);
    std::size_t n = 0;

    ASSERT_EQ(ob.len(), 3);
    for (const auto &e : ob) {
        ASSERT_TRUE((std::is_same<decltype(e), const object&>::value)) <<
            "const iteration over ob does not yield correct type";

        EXPECT_TRUE(e.is(expected[n++]));
    }
    EXPECT_EQ(n, 3) << "ran through too many iterations";
}