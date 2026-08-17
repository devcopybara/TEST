#ifndef APP_COUNTER_H
#define APP_COUNTER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint32_t value;
    uint32_t limit;
} AppCounter;

void AppCounter_Init(AppCounter *counter, uint32_t limit);
bool AppCounter_Increment(AppCounter *counter);
uint32_t AppCounter_Value(const AppCounter *counter);

#endif /* APP_COUNTER_H */

