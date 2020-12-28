#include "Arithmetic_Exp.h"
#include "gtest.h"

TEST (Arithmetic_Exp, can_create_expression)
{
	ASSERT_NO_THROW(Expression e);
}

TEST(Arithmetic_Exp, can_set_expression)
{
	string str = "2+2";
	ASSERT_NO_THROW(Expression e(str));

}

TEST(Arithmetic_Exp, correct_analyse1)
{
	string str = "2+2";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse2)
{
	string str = "(2+2)";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse3)
{
	string str = "-2+2";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse4)
{
	string str = ")2+2";
	Expression e(str);
	ASSERT_ANY_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse5)
{
	string str = "2+)2";
	Expression e(str);
	ASSERT_ANY_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse6)
{
	string str = "2+2(";
	Expression e(str);
	ASSERT_ANY_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse7)
{
	string str = "x+2";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse8)
{
	string str = "=2+2";
	Expression e(str);
	ASSERT_ANY_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse9)
{
	string str = "2*2";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse10)
{
	string str = "2/2";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse11)
{
	string str = "2^2+1";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse12)
{
	string str = "(2^2+1";
	Expression e(str);
	ASSERT_ANY_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse13)
{
	string str = "()";
	Expression e(str);
	ASSERT_ANY_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse14)
{
	string str = " ";
	Expression e(str);
	ASSERT_ANY_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse15)
{
	string str = "xyz";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse16)
{
	string str = "(-2+2)";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse17)
{
	string str = "(2(-(2+2)))";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse18)
{
	string str = "2+*2";
	Expression e(str);
	ASSERT_ANY_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_analyse19)
{
	string str = "2-(-2)";
	Expression e(str);
	ASSERT_NO_THROW(e.Exp_Analyse());
}

TEST(Arithmetic_Exp, correct_rpn)
{
	string str = "2+2";
	string str1 = "22+";
	Expression e(str);
	e.RPN(&e);
	EXPECT_EQ(e.OutExpression(), str1);
}

TEST(Arithmetic_Exp, correct_rpn1)
{
	string str = "2*2+1";
	string str1 = "22*1+";
	Expression e(str);
	e.RPN(&e);
	EXPECT_EQ(e.OutExpression(), str1);
}

TEST(Arithmetic_Exp, correct_rpn2)
{
	string str = "1+3*4-2";
	string str1 = "134*+2-";
	Expression e(str);
	e.RPN(&e);
	EXPECT_EQ(e.OutExpression(), str1);
}

TEST(Arithmetic_Exp, correct_rpn3)
{
	string str = "2*(2+2)";
	string str1 = "222+*";
	Expression e(str);
	e.RPN(&e);
	EXPECT_EQ(e.OutExpression(), str1);
}

TEST(Arithmetic_Exp, correct_rpn4)
{
	string str = "(2*2+1)/(1+3*4-2)";
	string str1 = "22*1+134*+2-/";
	Expression e(str);
	e.RPN(&e);
	EXPECT_EQ(e.OutExpression(), str1);
}

TEST(Arithmetic_Exp, correct_rpn5)
{
	string str = "-3+5^2";
	string str1 = "-352^+";
	Expression e(str);
	e.RPN(&e);
	EXPECT_EQ(e.OutExpression(), str1);
}

TEST(Arithmetic_Exp, correct_res)
{
	string str = "2+2*2";
	Expression e(str);
	e.RPN(&e);
	int n = e.result();
	EXPECT_EQ(n, 6);
}

TEST(Arithmetic_Exp, correct_res2)
{
	string str = "1+3*4-2";
	Expression e(str);
	e.RPN(&e);
	int n = e.result();
	EXPECT_EQ(n, 11);
}