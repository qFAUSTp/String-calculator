#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int СheckPrior(char);
float Сalculate(char, float, float);
void SolveExpression(string);

int main(int argc, char* argv[])
{
	string expr(argv[1]);
	
	cout << "Entered expression: " << expr << endl;
	
	SolveExpression(expr);

	system("pause");
}

void SolveExpression(string expr)
{
	vector<float> numbers;
	vector<char> operations;
	vector<int> priority;

	std::string buffer("");

	float numBuffer = 0;
	bool flag = false;

	for (int i = 0; i < expr.length(); i++)
	{
		if ((expr[i] != '-') && (expr[i] != '+') && (expr[i] != '*') && (expr[i] != '/') && (expr[i] != '(') && (expr[i] != ')') && (expr[i] != ' '))
		{
			if (isalpha(expr[i]) != 0)
			{
				if (flag == false)
				{
					flag = true;
					cout << "Invalid input, string contains invalid expression!" << expr[i];
				}
				else
					cout << expr[i];
			}
		}
	}

	if (flag == true)
	{
		cout << endl;
		goto OUT;
	}

	while (expr.length() != 0)
	{
		if ((expr[0] != '+') && (expr[0] != '-') && (expr[0] != '*') && (expr[0] != '/') && (expr[0] != ' ') && (expr[0] != '(') && (expr[0] != ')'))
		{
			if ((expr[0] == '.') || (expr[0] == ','))
				buffer.push_back('.');
			else
				buffer.push_back(expr[0]);
		}
		else if (buffer.length() != 0)
		{
			numbers.push_back(strtof((buffer).c_str(), 0)); buffer.clear();
		}

		if ((expr[0] == '-') && (numbers.size() == 0))
		{
			numbers.push_back(0);
			goto END;
		}

		if (expr[0] == '(')
			operations.push_back(expr[0]);
		if (expr[0] == ')')
		{
			while (operations[operations.size() - 1] != '(')
			{
				numBuffer = Сalculate(operations[operations.size() - 1], numbers[numbers.size() - 1], numbers[numbers.size() - 2]);
				numbers.pop_back();	numbers.pop_back();		numbers.push_back(numBuffer);
				operations.pop_back();
				priority.pop_back();
			}
			operations.pop_back();
		}

		if ((expr[0] == '*') || (expr[0] == '/') || (expr[0] == '+') || (expr[0] == '-'))
		{

		CHECKSTACK:
			if (priority.size() == 0)
			{
				operations.push_back(expr[0]);
				priority.push_back(СheckPrior(expr[0]));
			}
			else if (numbers.size() >= 2)
			{
				if ((priority[priority.size() - 1] < СheckPrior(expr[0])) && (operations[operations.size() - 1] != '('))
				{
					operations.push_back(expr[0]);
					priority.push_back(СheckPrior(expr[0]));
				}
				else if ((priority[priority.size() - 1] >= СheckPrior(expr[0])) && (operations[operations.size() - 1] != '('))
				{
					numBuffer = Сalculate(operations[operations.size() - 1], numbers[numbers.size() - 1], numbers[numbers.size() - 2]);
					numbers.pop_back(); numbers.pop_back();		numbers.push_back(numBuffer);
					operations.pop_back();
					priority.pop_back();
					goto CHECKSTACK;
				}
				else if (operations[operations.size() - 1] == '(')
				{
					operations.push_back(expr[0]);
					priority.push_back(СheckPrior(expr[0]));
				}
			}

		}

		expr.erase(0, 1);
	END:
		if ((expr.length() == 0) && (buffer.length() != 0))
			numbers.push_back(strtof((buffer).c_str(), 0));
	}

	while (numbers.size() > 1)
	{
		numBuffer = Сalculate(operations[operations.size() - 1], numbers[numbers.size() - 1], numbers[numbers.size() - 2]);
		numbers.pop_back();	numbers.pop_back();				numbers.push_back(numBuffer);
		operations.pop_back();
		priority.pop_back();
	}

	for (int i = 0; i < numbers.size(); i++)
		cout << numbers[i] << endl;
OUT:

	return;
}

int СheckPrior(char symbol)
{
	switch (symbol)
	{
	default:
		break;
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	}
	return 0;
}

float Сalculate(char oper, float num1, float num2)
{
	switch (oper)
	{
	default:
		break;
	case '+':
		return num2 + num1;
	case '-':
		return num2 - num1;
	case '*':
		return num2 * num1;
	case '/':
		if (num1 != 0)
			return num2 / num1;
		else
		{
			cout << "Error: division by zero!" << endl;
			exit(0);
		}
	}
}
