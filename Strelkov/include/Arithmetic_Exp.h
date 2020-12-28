#pragma once

#include<iostream>
#include<string>
#include<cmath>
#include"stack.h"

using namespace std;

const int MaxSize = 1000;

enum State { q0, q1, q2, q3 };

struct Lexem {
	string s;
	int te;
	int val;
	int p;

	Lexem(const string _s, const int _te = 0, int _val = -1, int _p = -1) :
		s(_s), te(_te), val(_val), p(_p) { };
};

class Expression {
	string input;
	string output;
	

	Queue<Lexem*>* rpn;
	Queue<Lexem*>* inpExp;
	
	
	
public:
	Expression();
	Expression(const string& str);

	void Exp_Analyse();
	void split_Lex();
	
	const string& OutExpression() const;
	

	void RPN(Expression* e);
	int result();
};