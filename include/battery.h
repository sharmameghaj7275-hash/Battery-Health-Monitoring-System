#ifndef BATTERY_H
#define BATTERY_H
#define MAX_RECORDS 100
typedef enum { HEALTH_GOOD=0, HEALTH_WARNING=1, HEALTH_CRITICAL=2 } HealthStatus;
typedef struct { int id; float voltage_v,current_a,temperature_c; unsigned int cycle_count; } BatteryRecord;
typedef struct { float average_voltage,average_current,average_temperature,maximum_temperature; unsigned int total_cycles; int overheating_count; HealthStatus status; } BatterySummary;
int record_is_valid(const BatteryRecord *r);
BatterySummary analyze_records(const BatteryRecord records[],int count);
const char *health_status_name(HealthStatus status);
int save_record(const char *filename,const BatteryRecord *r);
int load_records(const char *filename,BatteryRecord records[],int capacity);
#endif
