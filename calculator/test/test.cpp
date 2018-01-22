#include "eval.h"
#include "gtest/gtest.h"

namespace tests {

    TEST(Calculator, Simple) {
        ASSERT_EQ(1, EvaluateExpression("1"));
        ASSERT_EQ(-2, EvaluateExpression("-2"));
        ASSERT_EQ(3, EvaluateExpression("1+2"));
        ASSERT_EQ(6, EvaluateExpression("2*3"));
        ASSERT_EQ(9, EvaluateExpression("10-1"));
        ASSERT_EQ(5, EvaluateExpression("10/2"));
        ASSERT_EQ(8, EvaluateExpression("-2*-4"));
    }

    TEST(Calculator, Complex) {
        ASSERT_EQ(362944, EvaluateExpression("2*(1+2*(3*4+105*431)*2+((2*3)*10+343))"));
        ASSERT_EQ(36, EvaluateExpression("(((1 + 1)*3)*4)+12"));
        ASSERT_EQ(2, EvaluateExpression("(((1 + 1)))"));
        ASSERT_EQ(30870, EvaluateExpression("(2+3)*(4+5*1234)"));
        ASSERT_EQ(3628800, EvaluateExpression("1*2*3*4*5*6*7*8*9* 10"));
        ASSERT_EQ(55, EvaluateExpression("1+2+3+4+5+6+7+8+9+10"));
        ASSERT_EQ(5, EvaluateExpression("(((2))+(3))"));
        ASSERT_EQ(62557728738473LL,
                  EvaluateExpression("-1- -2-(-(-(0-2-3-4-5+ -2-(3))+1)-3-2     -19) * 17239 * 82473842"));
        ASSERT_EQ(47, EvaluateExpression("19 + 2 / 3 + (1 + 1 + 394) / 7 / 2 / 1"));
    }
}