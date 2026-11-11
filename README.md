# Battery Health Monitoring and Analysis System in C

## Summary
A terminal-based educational program that stores battery observations (voltage, current, temperature, cycle count), validates them, computes summary statistics, and assigns GOOD/WARNING/CRITICAL using explicitly illustrative thresholds.

**Safety / scope:** Not a certified Battery Management System or real State-of-Health estimator. Example thresholds vary by chemistry, series cell count, and manufacturer. Do not use this program to protect a real battery.

## Build and use
Requires GCC and GNU Make.
```sh
make all
make run
make test
make clean
```
Menu: add a sample; display samples; analyze; exit. Example entry: `1 12.4 1.2 32 120`.

## Included modules
`src/main.c` menu/control; `src/battery.c` validation, summary, CSV read/write; `include/battery.h` types/interfaces; `tests/test_battery.cpp` Google Test cases.

## Threshold assumptions
Warning at temperature >=40 C; critical at >=50 C or voltage below 10.5 V. These are sample logic thresholds for demonstrating branching, not general battery limits.

## Test
Google Test must be installed for `make test`. Execute locally and record actual results.

## Limitations and future work
No live sensor interface, calibration, chemistry profile, or capacity-based SOH estimate. Possible future extensions: configurable profiles, trend charts, sensor integration, and a better-defined capacity/impedance SOH model.

## Submission details
Student:
Course/division:
Instructor:
