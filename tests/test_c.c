#include <check.h>
#include <stdbool.h>
#include <math.h>
#include "datetime.h"

#define EPSILON 1e-6

START_TEST(test_midtime)
{
    int Date0 = 20010324, Date1 = 20020324, Datem;
    float ut0 = 3.0, ut1 = 12.0, utm;

    MidTime(Date0, ut0, Date1, ut1, &Datem, &utm);

    ck_assert_int_eq(Datem, 20010922);
    ck_assert(fabs(utm - 19.5) < EPSILON);
}
END_TEST

START_TEST(test_minus_day)
{
    int Date = 20040301;
    Date = MinusDay(Date);
    ck_assert_int_eq(Date, 20040229);
}
END_TEST

START_TEST(test_time_index)
{
    int Date[] = {20010101, 20010101, 20010103, 20010104};
    float ut[] = {12.0, 23.0, 15.0, 4.0};
    int tDate = 20010102;
    float tut = 3.0;

    int ind = NearestTimeIndex(4, Date, ut, tDate, tut);
    ck_assert_int_eq(ind, 1);
}
END_TEST

START_TEST(test_plus_day)
{
    int Date = 20040228;
    Date = PlusDay(Date);
    ck_assert_int_eq(Date, 20040229);
}
END_TEST

START_TEST(test_time_diff)
{
    int Date0 = 20010324, Date1 = 20020324;
    float ut0 = 3.0, ut1 = 12.0;
    float dt = TimeDifference(Date0, ut0, Date1, ut1);
    ck_assert(fabs(dt - 365.375) < EPSILON);
}
END_TEST

START_TEST(test_unix_time)
{
    int Date = 20010405;
    float ut = 19.0;
    double unixt;

    UnixTime(1, &Date, &ut, &unixt);
    ck_assert(fabs(unixt - 986497200.0) < EPSILON);

    UnixTimetoDate(1, &unixt, &Date, &ut);
    ck_assert_int_eq(Date, 20010405);
    ck_assert(fabs(ut - 19.0) < EPSILON);
}
END_TEST

START_TEST(test_within)
{
    int Date[] = {20010101, 20010101, 20010103, 20010104, 20010105};
    float ut[] = {12.0, 23.0, 15.0, 4.0, 12.0};
    int Date0 = 20010102, Date1 = 20010105;
    float ut0 = 12.0, ut1 = 6.0;
    int ind[5], ni;
    int expected[] = {2, 3};

    WithinTimeRange(5, Date, ut, Date0, ut0, Date1, ut1, &ni, ind);

    ck_assert_int_eq(ni, 2);
    ck_assert_int_eq(ind[0], expected[0]);
    ck_assert_int_eq(ind[1], expected[1]);
}
END_TEST

// ... You can continue converting the rest in the same style ...

Suite *datetime_suite(void)
{
    Suite *s = suite_create("Datetime");
    TCase *tc = tcase_create("Core");

    // Add tests here
    tcase_add_test(tc, test_midtime);
    tcase_add_test(tc, test_minus_day);
    tcase_add_test(tc, test_time_index);
    tcase_add_test(tc, test_plus_day);
    tcase_add_test(tc, test_time_diff);
    tcase_add_test(tc, test_unix_time);
    tcase_add_test(tc, test_within);

    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = datetime_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
