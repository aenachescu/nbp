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

#ifndef NBP_PRIVATE_API_CHECK_H
#define NBP_PRIVATE_API_CHECK_H

#define NBP_PRIVATE_CHECK_BASE(cond, failMsg, passMsg)                         \
    if (cond) {                                                                \
        test->passedChecks++;                                                  \
        nbp_notify_printer_check_result(                                       \
            test,                                                              \
            #cond,                                                             \
            1,                                                                 \
            __LINE__,                                                          \
            0x0,                                                               \
            passMsg                                                            \
        );                                                                     \
    } else {                                                                   \
        test->failedChecks++;                                                  \
        nbp_notify_printer_check_result(                                       \
            test,                                                              \
            #cond,                                                             \
            0,                                                                 \
            __LINE__,                                                          \
            failMsg,                                                           \
            0x0                                                                \
        );                                                                     \
    }

#define NBP_PRIVATE_CHECK_OP_BASE(a, b, op, printerOp, failMsg, passMsg)       \
    if (a op b) {                                                              \
        test->passedChecks++;                                                  \
        nbp_notify_printer_check_op_result(                                    \
            test,                                                              \
            #a,                                                                \
            #b,                                                                \
            printerOp,                                                         \
            1,                                                                 \
            __LINE__,                                                          \
            0x0,                                                               \
            passMsg                                                            \
        );                                                                     \
    } else {                                                                   \
        test->failedChecks++;                                                  \
        nbp_notify_printer_check_op_result(                                    \
            test,                                                              \
            #a,                                                                \
            #b,                                                                \
            printerOp,                                                         \
            0,                                                                 \
            __LINE__,                                                          \
            failMsg,                                                           \
            0x0                                                                \
        );                                                                     \
    }

/*
 * TODO: add docs
 */
#define NBP_CHECK(cond)                                                        \
    NBP_PRIVATE_CHECK_BASE(cond, 0x0, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_FAIL_MSG(cond, msg)                                          \
    NBP_PRIVATE_CHECK_BASE(cond, msg, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_PASS_MSG(cond, msg)                                          \
    NBP_PRIVATE_CHECK_BASE(cond, 0x0, msg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_MSG(cond, failMsg, passMsg)                                  \
    NBP_PRIVATE_CHECK_BASE(cond, failMsg, passMsg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_EQ(a, b)                                                     \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, ==, NBP_PRINTER_OPERATOR_EQ, 0x0, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_EQ_FAIL_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, ==, NBP_PRINTER_OPERATOR_EQ, msg, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_EQ_PASS_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, ==, NBP_PRINTER_OPERATOR_EQ, 0x0, msg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_EQ_MSG(a, b, failMsg, passMsg)                               \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, ==, NBP_PRINTER_OPERATOR_EQ, failMsg,      \
        passMsg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_NE(a, b)                                                     \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, !=, NBP_PRINTER_OPERATOR_NE, 0x0, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_NE_FAIL_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, !=, NBP_PRINTER_OPERATOR_NE, msg, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_NE_PASS_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, !=, NBP_PRINTER_OPERATOR_NE, 0x0, msg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_NE_MSG(a, b, failMsg, passMsg)                               \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, !=, NBP_PRINTER_OPERATOR_NE, failMsg,      \
        passMsg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_GT(a, b)                                                     \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, >, NBP_PRINTER_OPERATOR_GT, 0x0, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_GT_FAIL_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, >, NBP_PRINTER_OPERATOR_GT, msg, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_GT_PASS_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, >, NBP_PRINTER_OPERATOR_GT, 0x0, msg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_GT_MSG(a, b, failMsg, passMsg)                               \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, >, NBP_PRINTER_OPERATOR_GT, failMsg,       \
        passMsg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_GE(a, b)                                                     \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, >=, NBP_PRINTER_OPERATOR_GE, 0x0, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_GE_FAIL_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, >=, NBP_PRINTER_OPERATOR_GE, msg, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_GE_PASS_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, >=, NBP_PRINTER_OPERATOR_GE, 0x0, msg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_GE_MSG(a, b, failMsg, passMsg)                               \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, >=, NBP_PRINTER_OPERATOR_GE, failMsg,      \
        passMsg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_LT(a, b)                                                     \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, <, NBP_PRINTER_OPERATOR_LT, 0x0, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_LT_FAIL_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, <, NBP_PRINTER_OPERATOR_LT, msg, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_LT_PASS_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, <, NBP_PRINTER_OPERATOR_LT, 0x0, msg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_LT_MSG(a, b, failMsg, passMsg)                               \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, <, NBP_PRINTER_OPERATOR_LT, failMsg,       \
        passMsg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_LE(a, b)                                                     \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, <=, NBP_PRINTER_OPERATOR_LE, 0x0, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_LE_FAIL_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, <=, NBP_PRINTER_OPERATOR_LE, msg, 0x0)

/*
 * TODO: add docs
 */
#define NBP_CHECK_LE_PASS_MSG(a, b, msg)                                       \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, <=, NBP_PRINTER_OPERATOR_LE, 0x0, msg)

/*
 * TODO: add docs
 */
#define NBP_CHECK_LE_MSG(a, b, failMsg, passMsg)                               \
    NBP_PRIVATE_CHECK_OP_BASE(a, b, <=, NBP_PRINTER_OPERATOR_LE, failMsg,      \
        passMsg)

#endif // end if NBP_PRIVATE_API_CHECK_H