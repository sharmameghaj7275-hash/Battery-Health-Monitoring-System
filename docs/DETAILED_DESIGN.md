# Detailed Software Design

## Modules
- `main.c`: menu and interaction.
- `battery.c`: input validation, calculations, status classification, CSV persistence.
- `battery.h`: shared structures, enums, constants, prototypes.
- `test_battery.cpp`: Google Test unit tests.

## Data structures
`BatteryRecord` groups ID, voltage, current, temperature, and cycle count.
`BatterySummary` groups averages, max temperature, total cycles, elevated-temperature count, and status.
`HealthStatus` names GOOD/WARNING/CRITICAL outcomes.

## Analysis procedure
1. Reject null/empty dataset as CRITICAL.
2. Initialize summary accumulators.
3. Validate each record.
4. Accumulate voltage/current/temperature and cycle totals.
5. Track maximum temperature and count samples >= warning threshold.
6. Apply status rules: critical if any temperature >= critical threshold or voltage below low threshold; otherwise warning if any temperature >= warning threshold.
7. Divide accumulated averages by record count.

## File handling
CSV fields: `id,voltage,current,temperature,cycle_count`. Open in append mode to save. Check fopen, fprintf, fclose. Load validates parsed records and returns count or -1 on error.

## Error handling
Reject invalid record values and malformed CSV. Check file operations. Handle menu input failure. Bound record count.

## Complexity
Analysis is O(n) time and O(1) extra space for n observations.

## Limits
Thresholds are illustrative; dataset lacks chemistry, rated capacity, and cell topology. No physical sensing or certified SOH model.
