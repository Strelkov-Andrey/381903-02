#pragma once

#include<iostream>


using namespace std;

template <class ValType>
class ICollection {
public:
	virtual int getSize() const = 0;

	virtual void push(const ValType& v) = 0;
	virtual ValType pop() = 0;
	virtual bool Empty() const = 0;
	virtual bool Full() const = 0;
};

template <class ValType>
class Stack : public ICollection<ValType> {
	ValType* tStack;
	int n;
	int top;
public:
	Stack(int _n = 100);
	Stack(Stack<ValType>& s);
	
	int getSize() const;

	void push(const ValType& v);
	ValType pop();

	bool Full() const;
	bool Empty() const;

	Stack<ValType>& operator=(Stack<ValType>& s);
	bool operator==(Stack<ValType>& q);

};

template <class ValType>
Stack<ValType>::Stack(int _n) : n(_n)
{
	if (_n < 0) throw logic_error("negative number of elements");
	top = -1;
	tStack = new ValType[n];
}

template <class ValType>
Stack<ValType>::Stack(Stack<ValType>& s)
{
	n = s.n;
	top = -1;
	tStack = new T[n];
	ValType* tArray = new T[n];
	int count = 0;
	while (!s.Empty())
	{
		tArray[count] = s.pop();
		count++;
	}
	for (int i = count - 1; i >= 0; i--)
	{
		push(tArray[i]);
		s.push(tArray[i]);
	}
	delete[] tArray;
}

template <class ValType>
Stack<ValType>& Stack<ValType>::operator=(Stack<ValType>& s)
{
	if (this == &s) return *this;
	delete[] tStack;
	n = s.n;
	top = -1;
	tStack = new ValType[n];
	ValType* tArray = new ValType[n];
	int count = 0;
	while (!s.Empty())
	{
		tArray[count] = s.pop();
		count++;
	}
	for (int i = count - 1; i >= 0; i--)
	{
		push(tArray[i]);
		s.push(tArray[i]);
	}
	delete[] tArray;
	return *this;
}

template <class ValType>
bool Stack<ValType>::operator==(Stack<ValType>& s)
{
	if (n != s.n) return false;
	Stack<ValType> t1(*this);
	Stack<ValType> t2(s);
	ValType tVal1;
	ValType tVal2;
	while ((!t1.Empty()) && (!t2.Empty()))
	{
		tVal1 = t1.pop();
		tVal2 = t2.pop();
		if (tVal1 != tVal2) return false;
	}

	if ((!t1.Empty()) || (!t2.Empty())) return false;
	return true;
}

template <class ValType>
int Stack<ValType>::getSize() const
{
	return n;
}

template <class ValType>
void Stack<ValType>::push(const ValType& v)
{
	if (Full()) throw logic_error("stack overflow");
	top++;
	tStack[top] = v;
}

template <class ValType>
ValType Stack<ValType>::pop()
{
	if (Empty()) { throw logic_error("stack is empty"); }
	ValType t = tStack[top];
	top--;
	return t;
}

template <class ValType>
bool Stack<ValType>::Full() const
{
	return (n - 1 == top);
}

template <class ValType>
bool Stack<ValType>::Empty() const
{
	return (top == -1);
}

template <class ValType>
class Queue : public ICollection<ValType> {
	ValType* pQueue;
	int n;
	int l, f;

	int next(int i) const;
public:
	Queue(int _n = 100);
	Queue(Queue<ValType>& q);
	Queue<ValType>& operator=(Queue<ValType>& q);

	bool operator==(Queue<ValType>& q);

	int getSize() const;

	void push(const ValType& v);
	ValType pop();
	bool Full() const;
	bool Empty() const;
};

template <class ValType>
int Queue<ValType>::next(int i) const
{
	return (i + 1) % n;
}

template <class ValType>
Queue<ValType>::Queue(int _n) :n(_n + 1)
{
	pQueue = new ValType[n];
	f = 0;
	l = n - 1;
}

template <class ValType>
Queue<ValType>::Queue(Queue<ValType>& q)
{
	n = q.n;
	f = 0;
	l = n - 1;
	pQueue = new ValType[n];
	ValType* tmpArray = new ValType[n];
	int count = 0;
	while (!q.Empty())
	{
		tArray[count] = q.pop();
		count++;
	}
	for (int i = 0; i < count; i++)
	{
		push(tArray[i]);
		q.push(tArray[i]);
	}
	delete[] tArray;
}

template <class ValType>
Queue<ValType>& Queue<ValType>::operator=(Queue<ValType>& q)
{
	if (this == &q) return *this;
	delete[] pQueue;
	n = q.n;
	f = 0;
	l = n - 1;
	pQueue = new T[n];
	ValType* tArray = new ValType[n];
	int count = 0;
	while (!q.Empty())
	{
		tArray[count] = q.pop();
		count++;
	}
	for (int i = 0; i < count; i++)
	{
		push(tArray[i]);
		q.push(tArray[i]);
	}
	return *this;
}

template <class ValType>
bool Queue<ValType>::operator==(Queue<ValType>& q)
{
	if (n != q.n) return false;

	Queue<ValType> t1(*this);
	Queue<ValType> t2(q);
	ValType tVal1;
	ValType tVal2;
	while ((!t1.Empty()) && (!t2.Empty()))
	{
		tVal1 = t1.pop();
		tVal2 = t2.pop();
		if (tVal1 != tVal2) return false;
	}
	if ((!t1.Empty()) || (!t2.Empty())) return false;

	return true;
}

template <class ValType>
int Queue<ValType>::getSize() const
{
	return n - 1;
}

template <class ValType>
void Queue<ValType>::push(const ValType& v)
{
	if (Full()) { throw logic_error("queue overflow"); }
	l = next(l);
	pQueue[l] = v;
}

template <class ValType>
ValType Queue<ValType>::pop()
{
	if (Empty()) { throw logic_error("queue is empty"); }
	ValType t = pQueue[f];
	f = next(f);
	return t;
}

template <class ValType>
bool Queue<ValType>::Full() const
{
	return next(next(l)) == f;
}

template <class ValType>
bool Queue<ValType>::Empty() const
{
	return next(l) == f;
}