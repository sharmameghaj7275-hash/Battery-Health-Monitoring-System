#include <stdio.h>
#include "battery.h"

int main(void)
{
    BatteryRecord a[MAX_RECORDS], r;
    BatterySummary s;
    int n, ch, i;
    
    n = load_records("data/battery_records.csv", a, MAX_RECORDS);
    if (n < 0) {
        n = 0;
    }
    
    puts("=== BATTERY HEALTH MONITOR ===");
    
    for (;;) {
        printf("\n1 Add record\n2 Display records\n3 Analyze\n4 Exit\nChoice: ");
        
        if (scanf("%d", &ch) != 1) {
            puts("Input error.");
            return 1;
        }
        
        if (ch == 1) {
            if (n >= MAX_RECORDS) {
                puts("Record limit reached.");
                continue;
            }
            
            printf("ID voltage(V) current(A) temperature(C) cycles: ");
            
            if (scanf("%d%f%f%f%u", &r.id, &r.voltage_v, &r.current_a, &r.temperature_c, &r.cycle_count) != 5 || !record_is_valid(&r)) {
                puts("Invalid input.");
                continue;
            }
            
            if (save_record("data/battery_records.csv", &r)) {
                a[n++] = r;
                puts("Saved.");
            } else {
                puts("Save failed.");
            }
            
        } else if (ch == 2) {
            if (!n) {
                puts("No records.");
            }
            
            for (i = 0; i < n; i++) {
                printf("%d | %.2f V | %.2f A | %.2f C | %u cycles\n", 
                       a[i].id, a[i].voltage_v, a[i].current_a, a[i].temperature_c, a[i].cycle_count);
            }
            
        } else if (ch == 3) {
            s = analyze_records(a, n);
            
            printf("Status: %s\n", health_status_name(s.status));
            printf("Mean voltage %.2f V; mean current %.2f A; mean temp %.2f C\n", 
                   s.average_voltage, s.average_current, s.average_temperature);
            printf("Max temp %.2f C; overheating records %d; total cycles %u\n", 
                   s.maximum_temperature, s.overheating_count, s.total_cycles);
            
        } else if (ch == 4) {
            break;
        } else {
            puts("Select 1-4.");
        }
    }
    
    return 0;
}
