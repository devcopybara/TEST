#include "app_counter.h"

#include <stddef.h>

void AppCounter_Init(AppCounter *counter, uint32_t limit)
{
    if (counter == NULL) {
        return;
    }

    counter->value = 0U;
    counter->limit = limit;
}

bool AppCounter_Increment(AppCounter *counter)
{
    if ((counter == NULL) || (counter->value >= counter->limit)) {
        return false;
    }

    counter->value++;
    return true;
}

uint32_t AppCounter_Value(const AppCounter *counter)
{
    if (counter == NULL) {
        return 0U;
    }

    return counter->value;
}

