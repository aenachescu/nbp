/*
No Bugs in Production (NBP)
Copyright (C) 2019-present Alin Enachescu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <nbp.h>

#include "../sample_utils.h"

#include <limits.h>

unsigned long long int get_ullong()
{
    return 2ULL;
}

volatile unsigned long long int ullong_min = 0;
volatile unsigned long long int ullong_max = ULLONG_MAX;
volatile unsigned long long int ullong_ = 2ULL;

NBP_TEST(module_assert_ullong_eq)
{
    SAMPLE_SLEEP();
    NBP_MODULE_ASSERT_ULLONG_EQ(get_ullong(), ullong_);
    NBP_MODULE_ASSERT_ULLONG_EQ_FAIL_MSG(get_ullong(), ullong_, "module_assert failed");
    NBP_MODULE_ASSERT_ULLONG_EQ_PASS_MSG(get_ullong(), ullong_, "module_assert passed");
    NBP_MODULE_ASSERT_ULLONG_EQ_MSG(get_ullong(), ullong_, "module_assert failed", "module_assert passed");
}

NBP_TEST(module_assert_ullong_ne)
{
    SAMPLE_SLEEP();
    NBP_MODULE_ASSERT_ULLONG_NE(get_ullong(), ullong_min);
    NBP_MODULE_ASSERT_ULLONG_NE_FAIL_MSG(get_ullong(), ullong_min, "module_assert failed");
    NBP_MODULE_ASSERT_ULLONG_NE_PASS_MSG(get_ullong(), ullong_min, "module_assert passed");
    NBP_MODULE_ASSERT_ULLONG_NE_MSG(get_ullong(), ullong_min, "module_assert failed", "module_assert passed");
}

NBP_TEST(module_assert_ullong_gt)
{
    SAMPLE_SLEEP();
    NBP_MODULE_ASSERT_ULLONG_GT(get_ullong(), ullong_min);
    NBP_MODULE_ASSERT_ULLONG_GT_FAIL_MSG(get_ullong(), ullong_min, "module_assert failed");
    NBP_MODULE_ASSERT_ULLONG_GT_PASS_MSG(get_ullong(), ullong_min, "module_assert passed");
    NBP_MODULE_ASSERT_ULLONG_GT_MSG(get_ullong(), ullong_min, "module_assert failed", "module_assert passed");
}

NBP_TEST(module_assert_ullong_ge)
{
    SAMPLE_SLEEP();
    NBP_MODULE_ASSERT_ULLONG_GE(get_ullong(), ullong_min);
    NBP_MODULE_ASSERT_ULLONG_GE_FAIL_MSG(get_ullong(), ullong_, "module_assert failed");
    NBP_MODULE_ASSERT_ULLONG_GE_PASS_MSG(get_ullong(), ullong_min, "module_assert passed");
    NBP_MODULE_ASSERT_ULLONG_GE_MSG(get_ullong(), ullong_, "module_assert failed", "module_assert passed");
}

NBP_TEST(module_assert_ullong_lt)
{
    SAMPLE_SLEEP();
    NBP_MODULE_ASSERT_ULLONG_LT(get_ullong(), ullong_max);
    NBP_MODULE_ASSERT_ULLONG_LT_FAIL_MSG(get_ullong(), ullong_max, "module_assert failed");
    NBP_MODULE_ASSERT_ULLONG_LT_PASS_MSG(get_ullong(), ullong_max, "module_assert passed");
    NBP_MODULE_ASSERT_ULLONG_LT_MSG(get_ullong(), ullong_max, "module_assert failed", "module_assert passed");
}

NBP_TEST(module_assert_ullong_le)
{
    SAMPLE_SLEEP();
    NBP_MODULE_ASSERT_ULLONG_LE(get_ullong(), ullong_max);
    NBP_MODULE_ASSERT_ULLONG_LE_FAIL_MSG(get_ullong(), ullong_, "module_assert failed");
    NBP_MODULE_ASSERT_ULLONG_LE_PASS_MSG(get_ullong(), ullong_max, "module_assert passed");
    NBP_MODULE_ASSERT_ULLONG_LE_MSG(get_ullong(), ullong_, "module_assert failed", "module_assert passed");
}

NBP_MODULE(module_assert_ullong)
{
    NBP_CALL_TEST(module_assert_ullong_eq);
    NBP_CALL_TEST(module_assert_ullong_ne);
    NBP_CALL_TEST(module_assert_ullong_gt);
    NBP_CALL_TEST(module_assert_ullong_ge);
    NBP_CALL_TEST(module_assert_ullong_lt);
    NBP_CALL_TEST(module_assert_ullong_le);
}