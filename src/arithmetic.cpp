// реализация функций и классов для вычисления арифметических выражений

#include "../include/arithmetic.h"

void isCorrect(const string &str){
	for (int i = 0; i < str.length(); i++){
		if (strchr("0123456789.+-*/()abcdefghijklmnopqrstuvwxyz", str[i]) == nullptr)
			throw("Incorrect symbol");
		if (strchr("abcdefghijklmnopqrstuvwxyz", str[i]) != nullptr && i != (str.length() - 1) && strchr("abcdefghijklmnopqrstuvwxyz", str[i + 1]) != nullptr)
			throw("Very long name for variable, please use one symbol for name variable");
	}

	if (strchr("+/*).", str[0]) != nullptr || strchr("+-*/(.", str[str.length()-1]) != nullptr){
		throw("Incorrect begin or end");
	}

	bool check_open = false;
	int count = 0;
	for (int i = 0; i < str.length(); i++){
		if (str[i] == '('){
			check_open = true;
			count++;
			if (i < str.length()-1 && strchr("+*/.", str[i + 1]) != nullptr)
				throw("Operator after open bracket");
			if (i > 0 && strchr("0123456789abcdefghijklmnopqrstuvwxyz", str[i-1]) != nullptr)
				throw("Number or variable before open bracket");
		}
		if (str[i] == ')')
		{
			check_open = false;
			count--;
			if (i > 0 && strchr("+*/.", str[i - 1]) != nullptr)
				throw("Operator before close bracket");
			if (i < str.length()-1 && strchr("0123456789abcdefghijklmnopqrstuvwxyz", str[i + 1]) != nullptr)
				throw("Number or variable after close bracket");
		}
	}

	if (check_open && count != 0)
		throw("Error with bracket");
	
}

vector_lexems toLexems(string &str){
	vector_lexems result_vector;
	for (int i = 0; i < str.length(); i++){
		if (i != 0 && strchr("0123456789", str[i - 1]) == nullptr && str[i] == '.')
			throw("Incorrect dot");
		if (strchr("abcdefghijklmnopqrstuvwxyz", str[i]) != nullptr){
			Lexem temp_lexem(variable, str[i]);
			result_vector.push_back(temp_lexem);			
		}else
		if (strchr("0123456789", str[i]) != nullptr){
			if (i != 0 && strchr("0123456789.", str[i - 1]) != nullptr){
				continue;
			}
			string temp = "";
			int count_dot = 0, j = i;
			while (strchr("0123456789.", str[j]) != nullptr){
				temp += str[j];
				if (str[j] == '.')
					count_dot++;
				j++;
				if (j == str.length())
					break;
			}
			if (count_dot > 1)
				throw("Incorrect dot");
			Lexem temp_lexem(number, atof(temp.c_str()));
			result_vector.push_back(temp_lexem);
		}else
		if (str[i] == '+'){
			Lexem temp_lexem(sum, str[i]);
			result_vector.push_back(temp_lexem);
		}else
		if (strchr("*/", str[i]) != nullptr){
			Lexem temp_lexem(pr, str[i]);
			result_vector.push_back(temp_lexem);
		}else
		if (str[i] == '('){
			Lexem temp_lexem(obracket, str[i]);
			result_vector.push_back(temp_lexem);
		}else
		if (str[i] == ')'){
			Lexem temp_lexem(clbracket, str[i]);
			result_vector.push_back(temp_lexem);
		}else
		if (str[i] == '-'){
			if (i == 0 || (i != 0 && strchr("*/+(-", str[i-1]) != nullptr)){
				Lexem temp_lexem(unarmin, '_');
				result_vector.push_back(temp_lexem);
			}
			else{
				Lexem temp_lexem(sum, '-');
				result_vector.push_back(temp_lexem);
			}
		}

		
	}

	return result_vector;
}

vector_lexems toPostfix(vector_lexems &lexems){
	vector_lexems postfix;
	Stack<Lexem> stack(lexems.size());

	for (int i = 0; i < lexems.size(); i++){
		if (lexems[i].getType() == 0)
			postfix.push_back(lexems[i]);
		else if (lexems[i].getType() == 1){
			postfix.push_back(lexems[i]);
			if (postfix.variables.count(lexems[i].getChar()) == 0){
				cout << "Please enter value for " << lexems[i].getChar() << ": ";
				cin >> postfix.variables[lexems[i].getChar()];
			}
		}
		else{
			switch (lexems[i].getType())
			{
			case obracket:
				stack.push(lexems[i]);
				break;
			case clbracket:
				while (stack.getTop().getType() != obracket){
					postfix.push_back(stack.pop());
				}
				stack.pop();
				break;
			case sum:
				
				while (!stack.isEmpty() && (stack.getTop().getType() == sum || stack.getTop().getType() == unarmin || stack.getTop().getType() == pr))
					postfix.push_back(stack.pop());
				
				stack.push(lexems[i]);
				break;
			case unarmin:
				/*if (!stack.isEmpty()){
					while (stack.getTop().getType() == unarmin)
						postfix.push_back(stack.pop());
				}*/
				stack.push(lexems[i]);
				break;
			case pr:
				while (!stack.isEmpty() && (stack.getTop().getType() == pr || stack.getTop().getType() == unarmin))
					postfix.push_back(stack.pop());
				
				stack.push(lexems[i]);
				break;
			default:
				break;
			}
		}

	}
	while (!stack.isEmpty()){
		postfix.push_back(stack.pop());
	}
	return postfix;
}

double compute(vector_lexems &postfix){
	double result = 0;
	Stack<double> nums(postfix.size());

	for (int i = 0; i < postfix.size(); i++){
		switch (postfix[i].getType())
		{
		case number:
			nums.push(postfix[i].getValue());
			break;
		case variable:
			nums.push(postfix.variables[postfix[i].getChar()]);
			break;
		case sum:
			if (postfix[i].getChar() == '+')
				nums.push(nums.pop() + nums.pop());
			else
				nums.push(-nums.pop() + nums.pop());
			break;
		case unarmin:
			nums.push(-nums.pop());
			break;
		case pr:
			if (postfix[i].getChar() == '*')
				nums.push(nums.pop() * nums.pop());
			else
				nums.push(nums.pop() / nums.pop());
			break;
		default:
			break;
		}
	}

	return nums.pop();
}