#include <datetime.h>
#include <gtest/gtest.h>

TEST(DateTimeTests, MidTimeCalculation) {
    int Date0 = 20010324;
    int Date1 = 20020324;
    float ut0 = 3.0;
    float ut1 = 12.0;
    int Datem;
    float utm;

    MidTime(Date0, ut0, Date1, ut1, &Datem, &utm);

    EXPECT_EQ(Datem, 20010922);
    EXPECT_FLOAT_EQ(utm, 19.5);
}