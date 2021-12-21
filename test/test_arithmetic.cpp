// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>

TEST(Stack, can_create_lexem)
{
	ASSERT_NO_THROW(Lexem());
}

TEST(Stack, can_string_to_lexem)
{
	string str = "a+7/8";
	Lexem a = Lexem(variable, 'a');
	Lexem b = Lexem(sum, '+');
	Lexem c = Lexem(number, 7.0);
	Lexem d = Lexem(pr, '/');
	Lexem e = Lexem(number, 8.0);
	ASSERT_NO_THROW(vector_lexems vl = toLexems(str));
	vector_lexems vl = toLexems(str);
	ASSERT_EQ(a, vl[0]);
	ASSERT_EQ(b, vl[1]);
	ASSERT_EQ(c, vl[2]);
	ASSERT_EQ(d, vl[3]);
	ASSERT_EQ(e, vl[4]);
}

TEST(Stack, check_error_with_brackets)
{
	string str = ")f+8(";
	ASSERT_ANY_THROW(isCorrect(str));
}

TEST(Stack, check_error_with_operator_after_open_bracket)
{
	string str = "(*7+6)";
	ASSERT_ANY_THROW(isCorrect(str));
}
TEST(Stack, check_error_with_number_after_close_bracket)
{
	string str = "(7+6)5";
	ASSERT_ANY_THROW(isCorrect(str));
}

TEST(Stack, simple_expression)
{
	string str = "7+6-4*3";
	vector_lexems lexems = toLexems(str);
	vector_lexems postfix = toPostfix(lexems);
	double result = compute(postfix);
	ASSERT_EQ(1, result);
}

TEST(Stack, simple_expression_with_brackets)
{
	string str = "7+(6-4)*3";
	vector_lexems lexems = toLexems(str);
	vector_lexems postfix = toPostfix(lexems);
	double result = compute(postfix);
	ASSERT_EQ(13, result);
}

TEST(Stack, simple_expression_with_unar_minus)
{
	string str = "16+-4";
	vector_lexems lexems = toLexems(str);
	vector_lexems postfix = toPostfix(lexems);
	double result = compute(postfix);
	ASSERT_EQ(12, result);
}

TEST(Stack, simple_expression_with_unar_minus_вшаашсгде)
{
	string str = "16---4";
	vector_lexems lexems = toLexems(str);
	vector_lexems postfix = toPostfix(lexems);
	double result = compute(postfix);
	ASSERT_EQ(12, result);
}

TEST(Stack, simple_expression_with_unar_minus_before_brackets)
{
	string str = "7+-(6-4)*3";
	vector_lexems lexems = toLexems(str);
	vector_lexems postfix = toPostfix(lexems);
	double result = compute(postfix);
	ASSERT_EQ(1, result);
}