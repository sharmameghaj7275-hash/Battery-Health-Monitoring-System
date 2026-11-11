#include <gtest/gtest.h>

extern "C" {
#include "battery.h"
}

static BatteryRecord rec(int id = 1, float v = 12, float a = 1, float t = 25, unsigned c = 100)
{
    return BatteryRecord{id, v, a, t, c};
}

TEST(Input, ValidRecord)
{
    auto r = rec();
    EXPECT_TRUE(record_is_valid(&r));
}

TEST(Input, NegativeVoltage)
{
    auto r = rec(1, -1);
    EXPECT_FALSE(record_is_valid(&r));
}

TEST(Input, NegativeCurrent)
{
    auto r = rec(1, 12, -1);
    EXPECT_FALSE(record_is_valid(&r));
}

TEST(Input, ExcessiveTemperature)
{
    auto r = rec(1, 12, 1, 151);
    EXPECT_FALSE(record_is_valid(&r));
}

TEST(Analysis, AverageVoltage)
{
    BatteryRecord a[] = {rec(1, 12), rec(2, 14)};
    EXPECT_FLOAT_EQ(analyze_records(a, 2).average_voltage, 13);
}

TEST(Analysis, GoodStatus)
{
    BatteryRecord a[] = {rec()};
    EXPECT_EQ(analyze_records(a, 1).status, HEALTH_GOOD);
}

TEST(Analysis, WarningStatus)
{
    BatteryRecord a[] = {rec(1, 12, 1, 40);
    EXPECT_EQ(analyze_records(a, 1).status, HEALTH_WARNING);
}

TEST(Analysis, CriticalTemperature)
{
    BatteryRecord a[] = {rec(1, 12, 1, 50)};
    EXPECT_EQ(analyze_records(a, 1).status, HEALTH_CRITICAL);
}

TEST(Analysis, LowVoltageCritical)
{
    BatteryRecord a[] = {rec(1, 10)};
    EXPECT_EQ(analyze_records(a, 1).status, HEALTH_CRITICAL);
}

TEST(Analysis, OverheatCount)
{
    BatteryRecord a[] = {rec(1, 12, 1, 40), rec(2, 12, 1, 25)};
    EXPECT_EQ(analyze_records(a, 2).overheating_count, 1);
}

TEST(Analysis, EmptyIsCritical)
{
    EXPECT_EQ(analyze_records(nullptr, 0).status, HEALTH_CRITICAL);
}

TEST(Analysis, MaximumTemperature)
{
    BatteryRecord a[] = {rec(1, 12, 1, 30), rec(2, 12, 1, 45)};
    EXPECT_FLOAT_EQ(analyze_records(a, 2).maximum_temperature, 45);
}
