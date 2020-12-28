#include <iostream>
#include <string>
#include "Arithmetic_Exp.h"
#include "stack.h"

int main()
{

	string s = "2*3+6-18^2";
	Expression e(s);

	e.RPN(&e);
	int res=e.result();
	cout << res;
	return 0;
}