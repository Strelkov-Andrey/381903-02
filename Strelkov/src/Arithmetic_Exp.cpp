#include "Arithmetic_Exp.h"
#include "stack.h"

Expression::Expression()
{
	input = "";
	output = "";
	rpn = new Queue<Lexem*>(MaxSize);
	inpExp = new Queue<Lexem*>(MaxSize);
}

Expression::Expression(const string& str)
{
	if (str.length() == 0)
		throw logic_error("String length is zero");
	input = str;
	output = "";
	rpn = new Queue <Lexem*>(MaxSize);
	inpExp = new Queue<Lexem*>(MaxSize);
}

void Expression::Exp_Analyse()
{
	State state = q0;
	char c;
	int t = 0;
	for (int i = 0; i < input.length(); i++)
	{
		c = input[i];
		if (state == q0)
		{
			if ((c >= '0') && (c <= '9'))
			{
				state = q1;
				
			}
			else if ((c >= 'a') && (c <= 'z'))
			{
				state = q2;
				
			}
			else if (c == '-')
			{
				state = q3;	
				
			}
			else if ((c == '(') && (input[i + 1] != ')'))
			{
				state = q0;
				t++;
			}
			else if ((c == ')') && (t != 0))
			{
				state = q2;
				t--;
			}
			else 
			{
				if ((c == '+') || (c == '^') || (c == '*') || (c == '/'))
				{
					throw logic_error("Incorrect expression");
				}
				else if ((c == ')') && (t == 0))
				{
					throw logic_error("Incorrect bracket");
				}
				else if (c == ' ') 
				{
					throw logic_error("Expression is empty");
				}
				else
				{
					throw logic_error("Incorrect expression");
				}
			}
			continue;
		}
		if (state == q1)
		{
			
			if ((c >= '0') && (c <= '9'))
			{
				state = q1;
			}
			else if ((c == '+') || (c == '-'))
			{
				state = q3;
			}
			else if ((c == '*') || (c == '/'))
			{
				state = q3;
			}
			else if (c == '^')
			{
				state = q3;
			}
			else if ((c >= 'a') && (c <= 'z'))
			{
				state = q2;
			}
			else if (c == '(')
			{
				state = q0;
				t++;
			}
			else if (c == ')')
			{
				state = q2;
				t--;
			}
			else if (c == ' ') {}
			else
			{
				throw logic_error("Incorrect expression");
			}
			continue;
		}
		if (state == q2)
		{
			if ((c >= '0') && (c <= '9'))
			{
				state = q1;
			}
			
			if ((c == '+') || (c == '-'))
			{
				state = q3;
			}
			else if ((c == '*') || (c == '/'))
			{
				state = q3;
			}
			else if (c == '^')
			{
				state = q3;
			}
			else if ((c >= 'a') && (c <= 'z'))
			{
				state = q2;
			}
			else if (c == '(')
			{
				state = q0;
				t++;
			}
			else if (c == ')')
			{
				state = q2;
				t--;
			}
			else if (c == ' ') {}
			else
			{
				throw logic_error("Incorrect expression");
			}
		
		continue;
		}
		if (state == q3)
		{	
			if ((c >= 'a') && (c <= 'z'))
			{
				state = q2;
			}
			else if ((c >= '0') && (c <= '9'))
			{
				state = q1;
			}
			else if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^'))
			{
				throw logic_error("Incorrect expression");
			}
			else if (c == '(')
			{
				state = q0;
				t++;
			}
			else if (c == ')')
			{
				state = q2;
				t--;
			}
			else if (c == ' ') {}
			else
			{
				throw logic_error("Incorrect expression");
			}
		}
	}
	if (t != 0)
		throw logic_error("Incorrect bracket");
}

void Expression::split_Lex()
{
	{
		string s;
		State state = q0;
		input += " ";
		char c;

		for (int i = 0; i < input.length(); i++)
		{
			c = input[i];
			if (state == q0)
			{
				s = c;
				if ((c >= '0') && (c <= '9'))
				{
					state = q1;
				}
				else if ((c >= 'a') && (c <= 'z'))
				{
					state = q2;
					
					inpExp->push(new Lexem(s, 2));
				}
				else if (c == '-')
				{
					state = q1;
					inpExp->push(new Lexem(s, -1));
				}
				else if (c == '(')
				{
					inpExp->push(new Lexem(s, 0));
				}
				else if (c == ')')
				{
					state = q2;
					inpExp->push(new Lexem(s, 4));
				}
				else if (c == ' ') {}
				else
				{
					if ((c == '+') || (c == '^') || (c == '*') || (c == '/'))
					{
						throw logic_error("Incorrect expression");
					}
					else
					{
						throw logic_error("Incorrect expression");
					}
				}
				continue;
			}
			if (state == q1)
			{
				if ((c >= '0') && (c <= '9'))
				{
					s += c;
					state = q1;
				}
				else
				{
					int val = stoi(s);
					inpExp->push(new Lexem(s, 1, val));
					state = q3;
					s = c;
					if ((c == '+') || (c == '-'))
					{
						inpExp->push(new Lexem(s, 3, -1, 3));
					}
					else if ((c == '*') || (c == '/'))
					{
						inpExp->push(new Lexem(s, 3, -1, 2));
					}
					else if (c == '^')
					{
						inpExp->push(new Lexem(s, 3, -1, 1));
					}
					else if ((c >= 'a') && (c <= 'z'))
					{
						state = q2;
						
						inpExp->push(new Lexem("*", 3, -1, 2));
						inpExp->push(new Lexem(s, 2));
					}
					else if (c == '(')
					{
						state = q0;
						inpExp->push(new Lexem(s, 0));
					}
					else if (c == ')')
					{
						state = q2;
						inpExp->push(new Lexem{ s, 4 });
					}
					else if (c == ' ') {}
					else
					{
						throw logic_error("Incorrect expression");
					}
				}
				continue;
			}
			if (state == q2)
			{
				s = c;
				if ((c >= 'a') && (c <= 'z'))
				{
					state = q2;
					
					inpExp->push(new Lexem("*", 3, -1, 2));
					inpExp->push(new Lexem(s, 2));
				}
				else if ((c >= '0') && (c <= '9'))
				{
					inpExp->push(new Lexem("*", 3, -1, 2));
					state = q1;
				}
				else if ((c == '+') || (c == '-'))
				{
					state = q3;
					inpExp->push(new Lexem(s, 3, -1, 3));
				}
				else if ((c == '*') || (c == '/'))
				{
					state = q3;
					inpExp->push(new Lexem(s, 3, -1, 2));
				}
				else if (c == '^')
				{
					state = q3;
					inpExp->push(new Lexem(s, 3, -1, 1));
				}
				else if (c == '(')
				{
					state = q0;
					inpExp->push(new Lexem("*", 3, -1, 2));
					inpExp->push(new Lexem(s, 0));
				}
				else if (c == ')')
				{
					inpExp->push(new Lexem(s, 4));
				}
				else if (c == ' ') {}
				else
				{
					throw logic_error("Incorrect expression");
				}
			}
			if (state == q3)
			{
				s = c;
				if ((c >= '0') && (c <= '9'))
				{
					state = q1;
				}
				else if ((c == '+') || (c == '-'))
				{
					inpExp->push(new Lexem(s, 3, -1, 3));
				}
				else if ((c == '*') || (c == '/'))
				{
					inpExp->push(new Lexem(s, 3, -1, 2));
				}
				else if (c == '^')
				{
					inpExp->push(new Lexem(s, 3, -1, 1));
				}
				else if ((c >= 'a') && (c <= 'z'))
				{
					state = q2;
					
					inpExp->push(new Lexem(s, 2));
				}
				else if (c == '(')
				{
					state = q0;
					inpExp->push(new Lexem(s, 0));
				}
				else if (c == ')')
				{
					state = q2;
					inpExp->push(new Lexem(s, 4));
				}
				else if (c == ' ') {}
				else
				{
					throw logic_error("Incorrect expression");
				}
			}
		}
	}
}

void Expression::RPN(Expression* e)
{
	e->Exp_Analyse();
	e->split_Lex();
	Stack<Lexem*>s(MaxSize);
	while (!inpExp->Empty())
	{
		Lexem* l = inpExp->pop();
		if ((l->te == 0) || (l->te == -1))
		{
			s.push(l);
		}
		if ((l->te == 1) || (l->te == 2))
		{
			rpn->push(l);
			output += l->s;
		}
		if ((l->te == 4)) {
			while (!s.Empty())
			{
				l = s.pop();
				if (l->te != 0)
				{
					rpn->push(l);
					output += l->s;
				}
				else
				{
					break;
				}
			}
		}
		if ((l->te == 3)) 
		{
			Lexem* l1;
			while (!s.Empty())
			{
				l1 = s.pop();
				if (l1->te == -1)
				{
					rpn->push(l1);
					output += l1->s;
				}
				else if ((l1->te == 3) && (l1->p <= l->p)) 
				{
					rpn->push(l1);
					output += l1->s;
				}
				else
				{
					s.push(l1);
					break;
				}
			}
			s.push(l);
		}
	}
	Lexem* l;
	while (!s.Empty())
	{
		l = s.pop();
		rpn->push(l);
		output += l->s;
	}
	
}

int Expression::result()
{
	Lexem* l;
	Stack<Lexem*> s(MaxSize);
	while (!rpn->Empty())
	{
		l = rpn->pop();
		if (l->te == 1)
		{
			s.push(l);
		}
		if (l->te == 2)
		{
			int var;
			cout << "Input value of " << l->s << " ";
			cin >> var;
			s.push(new Lexem(l->s, 1, var));
		}
		if (l->te == -1)
		{
			Lexem* l;
			int t;
			l = s.pop();
			t = -l->val;
			s.push(new Lexem{ to_string(t),1, t });
		}
		if (l->te == 3)
		{
			Lexem* l1;
			Lexem* l2;
			int t;
			if (l->s == "+")
			{
				l1 = s.pop();
				l2 = s.pop();
				t = l1->val + l2->val;
				s.push(new Lexem{ to_string(t),1, t });
			}
			if (l->s == "-")
			{
				l1 = s.pop();
				l2 = s.pop();
				t = l2->val - l1->val;
				s.push(new Lexem{ to_string(t),1, t });
			}
			if (l->s == "*")
			{
				l1 = s.pop();
				l2 = s.pop();
				t = l2->val * l1->val;
				s.push(new Lexem{ to_string(t),1, t });
			}
			if (l->s == "/")
			{
				l1 = s.pop();
				l2 = s.pop();
				t = l2->val / l1->val;
				s.push(new Lexem{ to_string(t),1, t });
			}
			if (l->s == "^")
			{
				l1 = s.pop();
				l2 = s.pop();
				t = pow(l2->val, l1->val);
				s.push(new Lexem{ to_string(t),1, t });
			}
		}
	}
	return s.pop()->val;
}



const string& Expression::OutExpression() const
{
	return output;
}