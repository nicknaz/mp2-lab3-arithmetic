// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include "stack.h"
#include <vector>
#include <map>

using namespace std;

enum typeLexem{ number = 0, variable = 1, obracket, sum, pr, clbracket, unarmin };

class Lexem{
	double value = 0;
	char s;
	typeLexem type;
public:
	Lexem() = default;
	Lexem(typeLexem t, double v) :type(t), value(v){};
	Lexem(typeLexem t, char s) :type(t), s(s){};
	typeLexem getType() const{ return type; };
	double getValue() const{ return value; };
	char getChar() const{ return s; };
	void show()
	{
		if (type == number)
			cout << value;
		else
			cout << s;
	}

	friend ostream& operator<<(ostream &out, const Lexem &v)
	{
		if (v.getType() == number)
			out << v.getValue();
		else
			out << v.getChar();
		return out;
	}

	bool operator==(const Lexem &l) const
	{
		if (l.getChar() != s || value != l.getValue() || type != l.getType())
			return false;
		return true;
	}
};

class vector_lexems : public vector<Lexem>{
public:
	map<char, double> variables;

	friend ostream& operator<<(ostream &out, const vector_lexems &v)
	{
		for (int i = 0; i < v.size(); i++)
			out << v[i];
		out << endl;
		return out;
	}
};

class Polish{

public:
	


};

void isCorrect(const string &str);
vector_lexems toLexems(string &str);
vector_lexems toPostfix(vector_lexems &lexems);
double compute(vector_lexems &postfix);