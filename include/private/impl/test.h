/*
No Bugs in Production (NBP)
https://github.com/aenachescu/nbp

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT
Copyright (c) 2019-2020 Alin Enachescu <https://github.com/aenachescu>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef NBP_PRIVATE_IMPL_TEST_H
#define NBP_PRIVATE_IMPL_TEST_H

unsigned int nbpTotalNumberOfTests = 0;

static void nbp_test_init(nbp_test_details_t* test,
    nbp_module_details_t* module, nbp_test_setup_pfn_t testSetup,
    nbp_test_teardown_pfn_t testTeardown)
{
    unsigned int state = NBP_SYNC_ATOMIC_UINT_CAS(
        &test->testState,
        NBP_TEST_STATE_NOT_INITIALIZED,
        NBP_TEST_STATE_READY
    );
    if (state != NBP_TEST_STATE_NOT_INITIALIZED) {
        NBP_ERROR_REPORT(NBP_ERROR_CODE_TEST_ALREADY_RUN);
        NBP_EXIT(NBP_ERROR_CODE_TEST_ALREADY_RUN);
    }

    test->configFunc(test);

    test->testId = nbpTotalNumberOfTests;
    nbpTotalNumberOfTests++;

    test->module = module;
    test->module->isEmptyModule = 0;
    test->module->tests.num++;
    test->module->taskNum++;

    // set setup function
    if (test->testSetupFunc == NBP_MEMORY_NULL_POINTER &&
        testSetup != NBP_MEMORY_NULL_POINTER) {
        test->testSetupFunc = testSetup;
    }

    // set teardown function
    if (test->testTeardownFunc == NBP_MEMORY_NULL_POINTER &&
        testTeardown != NBP_MEMORY_NULL_POINTER) {
        test->testTeardownFunc = testTeardown;
    }

    if (module->firstTest == NBP_MEMORY_NULL_POINTER) {
        module->firstTest = test;
        module->lastTest = test;
    } else {
        test->prev = module->lastTest;
        module->lastTest->next = test;
        module->lastTest = test;
    }
}

void nbp_test_run(nbp_test_details_t* test, nbp_module_details_t* module,
    nbp_test_setup_pfn_t testSetup, nbp_test_teardown_pfn_t testTeardown)
{
    nbp_test_init(test, module, testSetup, testTeardown);

    nbp_printer_notify_run_test(test);
    nbp_scheduler_notify_run_test(test);
}

void nbp_test_run_ctx(nbp_test_details_t* test, void* ctx,
    nbp_module_details_t* module, nbp_test_setup_pfn_t testSetup,
    nbp_test_teardown_pfn_t testTeardown)
{
    nbp_test_init(test, module, testSetup, testTeardown);

    nbp_printer_notify_run_test(test);
    nbp_scheduler_notify_run_test_ctx(test, ctx);
}

void nbp_test_increment_asserts_stats(nbp_test_details_t* test,
    unsigned int assertStatus, unsigned int assertType)
{
    switch (assertType)
    {
        case NBP_ASSERT_NON_FATAL:
            if (assertStatus == NBP_ASSERT_STATUS_PASSED) {
                test->asserts.nonFatal.numPassed++;
            } else if (assertStatus == NBP_ASSERT_STATUS_FAILED) {
                test->asserts.nonFatal.numFailed++;
            }
            break;

        case NBP_ASSERT_FATAL:
            if (assertStatus == NBP_ASSERT_STATUS_PASSED) {
                test->asserts.fatal.numPassed++;
            } else if (assertStatus == NBP_ASSERT_STATUS_FAILED) {
                test->asserts.fatal.numFailed++;
            }
            break;

        case NBP_ASSERT_FATAL_FOR_TEST:
            if (assertStatus == NBP_ASSERT_STATUS_PASSED) {
                test->asserts.fatalForTest.numPassed++;
            } else if (assertStatus == NBP_ASSERT_STATUS_FAILED) {
                test->asserts.fatalForTest.numFailed++;
            }
            break;

        case NBP_ASSERT_FATAL_FOR_MODULE:
            if (assertStatus == NBP_ASSERT_STATUS_PASSED) {
                test->asserts.fatalForModule.numPassed++;
            } else if (assertStatus == NBP_ASSERT_STATUS_FAILED) {
                test->asserts.fatalForModule.numFailed++;
            }
            break;

        default:
            return;
    }
}

unsigned int nbp_test_get_number_of_asserts(nbp_test_details_t* test,
    unsigned int assertStatus, unsigned int assertType)
{
    switch (assertType)
    {
        case NBP_ASSERT_NON_FATAL:
            if (assertStatus == NBP_ASSERT_STATUS_PASSED) {
                return test->asserts.nonFatal.numPassed;
            } else if (assertStatus == NBP_ASSERT_STATUS_FAILED) {
                return test->asserts.nonFatal.numFailed;
            }
            break;

        case NBP_ASSERT_FATAL:
            if (assertStatus == NBP_ASSERT_STATUS_PASSED) {
                return test->asserts.fatal.numPassed;
            } else if (assertStatus == NBP_ASSERT_STATUS_FAILED) {
                return test->asserts.fatal.numFailed;
            }
            break;

        case NBP_ASSERT_FATAL_FOR_TEST:
            if (assertStatus == NBP_ASSERT_STATUS_PASSED) {
                return test->asserts.fatalForTest.numPassed;
            } else if (assertStatus == NBP_ASSERT_STATUS_FAILED) {
                return test->asserts.fatalForTest.numFailed;
            }
            break;

        case NBP_ASSERT_FATAL_FOR_MODULE:
            if (assertStatus == NBP_ASSERT_STATUS_PASSED) {
                return test->asserts.fatalForModule.numPassed;
            } else if (assertStatus == NBP_ASSERT_STATUS_FAILED) {
                return test->asserts.fatalForModule.numFailed;
            }
            break;
    }

    return 0;
}

#endif // end if NBP_PRIVATE_IMPL_TEST_H
