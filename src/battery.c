#include <stdio.h>
#include "battery.h"

/* Illustrative coursework thresholds only; not certified battery safety limits. */
#define WARNING_TEMP_C 40.0f
#define CRITICAL_TEMP_C 50.0f
#define LOW_VOLTAGE_V 10.5f

int record_is_valid(const BatteryRecord *r)
{
    return r != NULL && 
           r->id > 0 && 
           r->voltage_v >= 0.0f && 
           r->current_a >= 0.0f && 
           r->temperature_c >= -40.0f && 
           r->temperature_c <= 150.0f;
}

BatterySummary analyze_records(const BatteryRecord a[], int n)
{
    BatterySummary s = {0};
    int k;
    s.status = HEALTH_GOOD;

    if (!a || n <= 0) {
        s.status = HEALTH_CRITICAL;
        return s;
    }
    
    s.maximum_temperature = a[0].temperature_c;

    for (k = 0; k < n; k++) {
        if (!record_is_valid(&a[k])) {
            s.status = HEALTH_CRITICAL;
            continue;
        }
        
        s.average_voltage += a[k].voltage_v;
        s.average_current += a[k].current_a;
        s.average_temperature += a[k].temperature_c;

        if (a[k].temperature_c > s.maximum_temperature) {
            s.maximum_temperature = a[k].temperature_c;
        }
        
        s.total_cycles += a[k].cycle_count;
        
        if (a[k].temperature_c >= WARNING_TEMP_C) {
            s.overheating_count++;
        }
        
        if (a[k].temperature_c >= CRITICAL_TEMP_C || a[k].voltage_v < LOW_VOLTAGE_V) {
            s.status = HEALTH_CRITICAL;
        } else if (a[k].temperature_c >= WARNING_TEMP_C && s.status == HEALTH_GOOD) {
            s.status = HEALTH_WARNING;
        }
    }

    s.average_voltage /= (float)n;
    s.average_current /= (float)n;
    s.average_temperature /= (float)n;
    
    return s;
}

const char *health_status_name(HealthStatus s)
{
    switch (s) {
        case HEALTH_GOOD:     
            return "GOOD";
        case HEALTH_WARNING:  
            return "WARNING";
        case HEALTH_CRITICAL: 
            return "CRITICAL";
        default:              
            return "UNKNOWN";
    }
}

int save_record(const char *name, const BatteryRecord *r)
{
    FILE *f;
    if (!name || !record_is_valid(r)) {
        return 0;
    }
    
    f = fopen(name, "a");
    if (!f) {
        return 0;
    }
    
    if (fprintf(f, "%d,%.2f,%.2f,%.2f,%u\n", r->id, r->voltage_v, r->current_a, r->temperature_c, r->cycle_count) < 0) {
        fclose(f);
        return 0;
    }
    
    return fclose(f) == 0;
}

int load_records(const char *name, BatteryRecord a[], int cap)
{
    FILE *f;
    int n = 0, m;
    BatteryRecord r;

    if (!name || !a || cap <= 0) {
        return -1;
    }
    
    f = fopen(name, "r");
    if (!f) {
        return -1;
    }
    
    while (n < cap) {
        m = fscanf(f, "%d,%f,%f,%f,%u", &r.id, &r.voltage_v, &r.current_a, &r.temperature_c, &r.cycle_count);
        if (m == EOF) {
            break;
        }
        
        if (m != 5 || !record_is_valid(&r)) {
            fclose(f);
            return -1;
        }
        
        a[n++] = r;
    }
    
    fclose(f);
    return n;
}
