#include <gtest/gtest.h>
#include "model/Record.h"

TEST(RecordTest, ConstructorSetsFields) {
    Record r(1, "Temperature", 36.5);
    EXPECT_EQ(r.getId(), 1);
    EXPECT_EQ(r.getName(), "Temperature");
    EXPECT_DOUBLE_EQ(r.getValue(), 36.5);
}

TEST(RecordTest, DefaultConstructor) {
    Record r;
    EXPECT_EQ(r.getId(), 0);
    EXPECT_EQ(r.getName(), "");
    EXPECT_DOUBLE_EQ(r.getValue(), 0.0);
}

TEST(RecordTest, GetterReturnsCorrectValues) {
    Record r(42, "Pressure", 101.3);
    EXPECT_EQ(r.getId(), 42);
    EXPECT_EQ(r.getName(), "Pressure");
    EXPECT_DOUBLE_EQ(r.getValue(), 101.3);
}
