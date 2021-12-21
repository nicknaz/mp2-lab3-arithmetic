// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_with_size)
{
	ASSERT_NO_THROW(Stack<int> stack(5));
}

TEST(Stack, can_copy)
{
	Stack<int> stack1(5);

	ASSERT_NO_THROW(Stack<int> stack2(stack1));
}

TEST(Stack, can_push)
{
	Stack<int> stack(5);
	ASSERT_NO_THROW(stack.push(5));
}

TEST(Stack, can_get_top)
{
	Stack<int> stack(5);
	stack.push(5);
	ASSERT_EQ(5, stack.getTop());
}

TEST(Stack, can_get_size)
{
	Stack<int> stack(5);
	stack.push(5);
	stack.push(5);
	stack.push(5);
	ASSERT_EQ(3, stack.getSize());
}

TEST(Stack, can_check_empty)
{
	Stack<int> stack(5);
	ASSERT_TRUE(stack.isEmpty());
}

TEST(Stack, can_push_in_full_stack)
{
	Stack<int> stack(0);
	ASSERT_NO_THROW(stack.push(5));
	ASSERT_EQ(1,stack.getSize());
	ASSERT_EQ(5, stack.getTop());
}

TEST(Stack, can_pop)
{
	Stack<int> stack(5);
	stack.push(5);
	stack.push(9);
	ASSERT_EQ(9, stack.pop());
	ASSERT_EQ(5, stack.getTop());
	ASSERT_EQ(1, stack.getSize());
}

TEST(Stack, can_clear)
{
	Stack<int> stack(5);
	stack.push(5);
	stack.push(9);
	ASSERT_NO_THROW(stack.clear());
	ASSERT_EQ(0, stack.getSize());
	ASSERT_ANY_THROW(stack.getTop());
}

