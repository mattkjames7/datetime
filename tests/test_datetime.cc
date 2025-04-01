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

TEST(DateTimeTests, TestMinusDay) {
    int Date = 20040301;
    Date = MinusDay(Date);

    EXPECT_EQ(Date, 20040229);
}


TEST(DateTimeTests, TestAddDay) {
    int Date = 20040228;
    Date = PlusDay(Date);

    EXPECT_EQ(Date, 20040229);
}


TEST(DateTimeTests, FindNearestTimeIndex) {
	int Date[] = {20010101,20010101,20010103,20010104};
	float ut[] = {12.0,23.0,15.0,4.0};
	int testDate = 20010102;
	float testUt = 3.0;

    int ind = NearestTimeIndex(4,Date,ut,testDate,testUt);

    EXPECT_EQ(ind, 1);
}

TEST(DateTimeTests, CalculateTimeDifference) {
    int Date0 = 20010324;
    int Date1 = 20020324;
    float ut0 = 3.0;
    float ut1 = 12.0;
    float dt;
    dt = TimeDifference(Date0,ut0,Date1,ut1);

    EXPECT_FLOAT_EQ(dt, 365.375);
}

TEST(DateTimeTests, UniqueFunction) {

    float x[] = {1.0,2.0,2.3,4.2,4.2,6.3,6.3};
    float expected[] = {1.0,2.0,2.3,4.2,6.3};
    int nu;
    float ux[7];

    Unique(7,x,&nu,ux);

    ASSERT_EQ(nu, 5);  // Confirm correct number of unique elements
    for (int i = 0; i < nu; ++i) {
        EXPECT_FLOAT_EQ(ux[i], expected[i]);
    }
}

TEST(DateTimeTests, DateToUnixTime) {
	int Date;
	float ut;
	double unixt;

	Date = 20010405;
	ut = 19.0;
	UnixTime(1,&Date,&ut,&unixt);

    EXPECT_FLOAT_EQ(unixt, 986497200.0);
}

TEST(DateTimeTests, UnixTimeToDate) {
	int Date;
	float ut;
	double unixt;

    unixt = 986497200.0;
	UnixTimetoDate(1,&unixt,&Date,&ut);

    EXPECT_EQ(Date, 20010405);
    EXPECT_FLOAT_EQ(ut, 19.0);
}