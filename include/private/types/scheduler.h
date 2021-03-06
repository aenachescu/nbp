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

#ifndef NBP_PRIVATE_TYPES_SCHEDULER_H
#define NBP_PRIVATE_TYPES_SCHEDULER_H

struct nbp_scheduler_interface_t;
typedef struct nbp_scheduler_interface_t nbp_scheduler_interface_t;

typedef void (*nbp_scheduler_config_pfn_t)(
    nbp_scheduler_interface_t*
);

typedef void (*nbp_scheduler_callback_init_pfn_t)(
    void
);

typedef void (*nbp_scheduler_callback_uninit_pfn_t)(
    void
);

typedef void (*nbp_scheduler_callback_run_pfn_t)(
    void
);

typedef void (*nbp_scheduler_callback_run_test_pfn_t)(
    nbp_test_details_t* /* current test */
);

typedef void (*nbp_scheduler_callback_run_test_ctx_pfn_t)(
    nbp_test_details_t*, /* current test */
    void* /* context */
);

typedef void (*nbp_scheduler_callback_run_module_pfn_t)(
    nbp_module_details_t* /* current module */
);

typedef void (*nbp_scheduler_callback_run_module_ctx_pfn_t)(
    nbp_module_details_t*, /* current module */
    void* /* context */
);

typedef void (*nbp_scheduler_callback_run_module_completed_pfn_t)(
    nbp_module_details_t* /* current module */
);

struct nbp_scheduler_interface_t {
    const char* schedulerName;
    nbp_scheduler_config_pfn_t configFunc;

    nbp_scheduler_callback_init_pfn_t initCbk;
    nbp_scheduler_callback_uninit_pfn_t uninitCbk;
    nbp_scheduler_callback_run_pfn_t runCbk;
    nbp_scheduler_callback_run_test_pfn_t runTestCbk;
    nbp_scheduler_callback_run_test_ctx_pfn_t runTestCtxCbk;
    nbp_scheduler_callback_run_module_pfn_t runModuleCbk;
    nbp_scheduler_callback_run_module_ctx_pfn_t runModuleCtxCbk;
    nbp_scheduler_callback_run_module_completed_pfn_t runModuleCompletedCbk;
};
typedef struct nbp_scheduler_interface_t nbp_scheduler_interface_t;

#endif // end if NBP_PRIVATE_TYPES_SCHEDULER_H
