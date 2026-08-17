#include "app_counter.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static int failures;

#define EXPECT_TRUE(condition)                                                   \
    do {                                                                         \
        if (!(condition)) {                                                       \
            printf("FAIL %s:%d: expected true: %s\n", __FILE__, __LINE__,       \
                   #condition);                                                   \
            failures++;                                                           \
        }                                                                          \
    } while (0)

#define EXPECT_FALSE(condition) EXPECT_TRUE(!(condition))

#define EXPECT_EQ_UINT32(expected, actual)                                        \
    do {                                                                          \
        uint32_t expected_value = (expected);                                     \
        uint32_t actual_value = (actual);                                         \
        if (expected_value != actual_value) {                                     \
            printf("FAIL %s:%d: expected %lu, got %lu\n", __FILE__, __LINE__,   \
                   (unsigned long)expected_value,                                 \
                   (unsigned long)actual_value);                                  \
            failures++;                                                           \
        }                                                                          \
    } while (0)

static void test_init_starts_at_zero(void)
{
    AppCounter counter;

    AppCounter_Init(&counter, 3U);

    EXPECT_EQ_UINT32(0U, AppCounter_Value(&counter));
}

static void test_increment_counts_up_to_limit(void)
{
    AppCounter counter;
    AppCounter_Init(&counter, 3U);

    EXPECT_TRUE(AppCounter_Increment(&counter));
    EXPECT_EQ_UINT32(1U, AppCounter_Value(&counter));
    EXPECT_TRUE(AppCounter_Increment(&counter));
    EXPECT_EQ_UINT32(2U, AppCounter_Value(&counter));
    EXPECT_TRUE(AppCounter_Increment(&counter));
    EXPECT_EQ_UINT32(3U, AppCounter_Value(&counter));
}

static void test_increment_saturates_at_limit(void)
{
    AppCounter counter;
    AppCounter_Init(&counter, 1U);

    EXPECT_TRUE(AppCounter_Increment(&counter));
    EXPECT_FALSE(AppCounter_Increment(&counter));
    EXPECT_EQ_UINT32(1U, AppCounter_Value(&counter));
}

static void test_zero_limit_never_increments(void)
{
    AppCounter counter;
    AppCounter_Init(&counter, 0U);

    EXPECT_FALSE(AppCounter_Increment(&counter));
    EXPECT_EQ_UINT32(0U, AppCounter_Value(&counter));
}

static void test_null_pointer_is_safe(void)
{
    AppCounter_Init(NULL, 3U);

    EXPECT_FALSE(AppCounter_Increment(NULL));
    EXPECT_EQ_UINT32(0U, AppCounter_Value(NULL));
}

int main(void)
{
    test_init_starts_at_zero();
    test_increment_counts_up_to_limit();
    test_increment_saturates_at_limit();
    test_zero_limit_never_increments();
    test_null_pointer_is_safe();

    if (failures != 0) {
        printf("%d test assertion(s) failed.\n", failures);
        return 1;
    }

    printf("All AppCounter tests passed.\n");
    return 0;
}

