/**
 * copy from https://github.com/miloyip/json-tutorial
*/
#pragma once

#include <iostream>

static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual) \
     do {\
         test_count++;\
         if (equality)\
			 test_pass++;\
         else {\
			 std::cout << '[' << __FILE__ << ':' << __LINE__ <<\
			 "] expect: " << expect << " actual: " << actual << '\n';\
         }\
     } while(0)

#define EXPECT_EQ(expect, actual) EXPECT_EQ_BASE(expect == actual, expect, actual)

#define TEST_RESULT() printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count)