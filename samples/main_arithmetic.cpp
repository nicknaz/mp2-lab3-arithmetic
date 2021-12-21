// реализация пользовательского приложения
#include <iostream>
#include <string>
#include <vector>
#include <arithmetic.h>

int main()
{
	vector_lexems lexems;
	vector_lexems postfix;
	string str;
	double result;
	getline(cin, str);

	cout << endl;

	isCorrect(str);
	lexems = toLexems(str);
	cout << "You input: " << lexems << endl << endl;
	
	postfix = toPostfix(lexems);
	cout << "Postfix: " << postfix << endl << endl;

	result = compute(postfix);
	
	cout << "Result: " << result << endl;
	return 0;
}
