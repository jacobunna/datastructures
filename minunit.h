/*
 * Adapted from
 * https://gist.github.com/sam159/0849461161e86249f849
 * which in turn is based on
 * http://www.jera.com/techinfo/jtns/jtn002.html
 */

#ifndef _MINUNIT_H
#define	_MINUNIT_H

#include <stdio.h>
#include <stdlib.h>

#define mu_suite_start() char *message = NULL

#define mu_assert(test, message)    \
    do {                            \
        if (!(test)) {              \
            return message;         \
        }                           \
    } while(0)

#define mu_run_test(test)                   \
    do {                                    \
        printf("----- %s...", #test);       \
        message = test();                   \
        if (message) {                      \
          printf("FAIL\n");                 \
          return message;                   \
        } else {                            \
          printf("PASS\n");                 \
        }                                   \
    } while(0)

#define RUN_TESTS(name)                                 \
    int main(int argc, char *argv[]) {                  \
        char *result;                                   \
        result = name();                                \
        if (result != 0) {                              \
            printf("Failure: %s\n", result);            \
            printf("Remaining tests will not be run\n");\
        }                                               \
        else {                                          \
            printf("All tests passed\n");               \
        }                                               \
        exit(result == 0 ? EXIT_SUCCESS : EXIT_FAILURE);\
    }

#endif
