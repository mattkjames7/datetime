# datetime
A C++ library contianing some time-related tools.

## Installation

This library requires GNU-make and g++ to be built in Linux and Mac. In Windows, I use TDM-GCC to provide the C++ compiler.

Clone the repo:

```bash
git clone https://github.com/mattkjames7/datetime.git
cd datetime
```

For Linux or Mac:
```bash
#build the library
make

#optionally install globally
sudo make install
```

For Windows:
```cmd
> compile.bat
```

## Linking
 
To link to this library in C or C++, you should include the header for the library:
```cpp
#include <datetime.h>
```
then link to the library, e.g.:
```bash
#when installed globally
g++ $(CFLAGS) main.cc -o main -ldatetime

#otherwise
g++ $(CFLAGS) -I/path/to/header/ main.cc -o main -L/path/to/lib -ldatetime
```

## Testing

To check that all of the functions are working as expected, run the following tests in Linux/Mac:

```bash
make test
```
or in Windows:
```cmd
> test.bat
```

If the library has been installed globally then the following test will check that linking can be done to the globally installed lib/header:
```bash
make testinstall
```

## Summary of Functions

| Name | Description |
|:-----|:------------|
| [`ContUT()`](include/datetime.h#L29) | Converts Date and UT to a continuous value of hours since 19500101 00:00/ |
| [`ContUTtoDate()`](include/datetime.h#L46) | Converts output of `ContUT()` back to date and time. |
| [`DateDifference()`](include/datetime.h#L64) | Find the number of days between two dates. |
| [`DateJoin()`](include/datetime.h#L82) | Join the individual elements of a date (year, month and day) to a single integer with the format _yyyymmdd_. |
| [`DateSplit()`](include/datetime.h#L100) | Split the date integer into year, month and day. |
| [`DayNo()`](include/datetime.h#L118) | Converts a date of the format _yyyymmdd_ to year and day number. |
| [`DayNotoDate()`](include/datetime.h#L135) | Converts year and day number to a date with the format _yyyymmdd_. |
| [`DectoHHMM()`](include/datetime.h#L154) | Converts the time in decimal hours to hours, minutes, seconds and milliseconds. |
| [`HHMMtoDec()`](include/datetime.h#L172) | Converts hours, minutes, seconds and milliseconds to decimal hours. |
| [`JulDay()`](include/datetime.h#L188) | Converts a date and time to Julian day. |
| [`JulDaytoDate()`](include/datetime.h#L204) | Converts Julian day to date and time. |
| [`LeapYear()`](include/datetime.h#L219) | Determines whether a year is a leap year or not. |
| [`MidTime()`](include/datetime.h#L237) | Works out the time and date exactly in the middle of two dates/times. |
| [`MinusDay()`](include/datetime.h#L252) | Subtracts one day off a date. |
| [`NearestTimeIndex()`](include/datetime.h#L272) | Finds the index of a time array closest to a given date/time. |
| [`PlusDay()`](include/datetime.h#L287) | Adds a day onto a date. |
| [`TimeDifference()`](include/datetime.h#L305) | Calculates the time difference(in days) between two dates/times. |
| [`UnixTime()`](include/datetime.h#L324) | Calculate the Unix time given a date and time. |
| [`UnixTimetoDate()`](include/datetime.h#L341) | Convert Unix time back to date and UT. |
| [`WithinTimeRange()`](include/datetime.h#L364) | Find the indices of a time array which lie within two dates/times. |

