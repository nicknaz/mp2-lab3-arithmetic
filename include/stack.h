// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#include <iostream>

using namespace std;

template <typename VT>
class Stack{
	int top = 0, size;
	VT *data;

public:

	Stack(const int size = 0);
	Stack(const Stack &s);
	~Stack();

	void push(const VT &value);
	VT& pop();
	VT& getTop();
	bool isEmpty();
	int getSize();
	void clear();
};

template <class VT>
Stack<VT>::Stack(const int size = 0) :size(size)
{
	data = new VT[size];
}

template <class VT>
Stack<VT>::Stack(const Stack &s) : size(s.size), top(s.top)
{
	data = new VT[size];
	for (int i = 0; i < top; i++)
		data[i] = s.data[i];
}

template <class VT>
Stack<VT>::~Stack()
{
	delete[] data;
}

template <class VT>
void Stack<VT>::push(const VT &value)
{
	if (top == size){
		VT *temp = new VT[size + 1];
		for (int i = 0; i < size; i++){
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;	
		size++;
	}

	data[top] = value;
	top++;
}

template <class VT>
VT& Stack<VT>::pop()
{
	if (top == 0)
		throw 0;

	top--;
	return data[top];
}

template <class VT>
VT& Stack<VT>::getTop()
{
	if (top == 0)
		throw 0;

	return data[top-1];
}

template <class VT>
bool Stack<VT>::isEmpty()
{
	return top == 0;
}

template <class VT>
int Stack<VT>::getSize()
{
	return top;
}

template <class VT>
void Stack<VT>::clear()
{
	delete[] data;
	data = new VT[size];
	top = 0;
}