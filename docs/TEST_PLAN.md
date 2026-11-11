# Test Plan
12 Google Test cases are supplied in `tests/test_battery.cpp`:
1 valid record
2 negative voltage rejected
3 negative current rejected
4 excessive temperature rejected
5 average voltage calculation
6 normal GOOD status
7 WARNING status
8 critical temperature
9 low voltage critical
10 overheating count
11 empty dataset
12 maximum temperature calculation

Run `make test` after installing Google Test. Record the actual outcome; do not claim passing tests unless they were executed.
