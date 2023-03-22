#include <unity.h>
#include "unittests.c"

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(Test_GetAdcMode);
    return UNITY_END();
}
