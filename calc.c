#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int checkPrior(char);
float calculate(char, float, float);

int main()
{
	setlocale(LC_ALL, "Russian");

	vector<float> NUMBERS;
	vector<char> OPERATIONS;
	vector<int> PRIORITY;

	string buffer("");
	
	//string expr = "2000/30-  10*(400-10 )+2-4+ 7;			//-3828.33
	//string expr = "2*(3-1)";					// 4
	//string expr = "12,3+78.1-5/3-9";				// 79.73
	//string expr = "1 + (2 *(2.5 + 2.5 + (3-2))) -(3/1.5)";  	// 11
	//string expr = "-1 +5-3";					// 1
	//string expr = "-10+(8*2.5)-(3/1,5)";	 			// 8
	//string expr = "-1 + 3 / 2 + 0.5";				// 1
	//string expr = "1.1+2.1+ abc";					// Некорректный ввод, строка содержит недопустимое выражение
	
	string expr;
	cout << "Введите выражение...";
	cin >> expr;
	
	float numBuffer = 0;
	cout << expr << endl;
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
					cout << "Не корректный ввод, строка содержит недопустимое выражение " << expr[i];
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
			NUMBERS.push_back(strtof((buffer).c_str(), 0)); buffer.clear();
		} 
		
		if ((expr[0] == '-') && (NUMBERS.size() == 0))
		{
			NUMBERS.push_back(0);
			goto END;
		}

		if (expr[0] == '(')
			OPERATIONS.push_back(expr[0]);
		if (expr[0] == ')')
		{
			while (OPERATIONS[OPERATIONS.size() - 1] != '(')
			{
				numBuffer = calculate(OPERATIONS[OPERATIONS.size() - 1], NUMBERS[NUMBERS.size() - 1], NUMBERS[NUMBERS.size() - 2]);
				NUMBERS.pop_back();	NUMBERS.pop_back();		NUMBERS.push_back(numBuffer);
				OPERATIONS.pop_back();
				PRIORITY.pop_back();
			}
			OPERATIONS.pop_back();
		}

		if ((expr[0] == '*') || (expr[0] == '/') || (expr[0] == '+') || (expr[0] == '-'))
		{
			
		CHECKSTACK:
			if (PRIORITY.size() == 0)	
			{
				OPERATIONS.push_back(expr[0]);
				PRIORITY.push_back(checkPrior(expr[0]));
			}
			else if (NUMBERS.size() >= 2)
			{
				if ((PRIORITY[PRIORITY.size() - 1] < checkPrior(expr[0]))&&(OPERATIONS[OPERATIONS.size()-1]!='('))
				{
					OPERATIONS.push_back(expr[0]);
					PRIORITY.push_back(checkPrior(expr[0]));
				}
				else if ((PRIORITY[PRIORITY.size() - 1] >= checkPrior(expr[0])) && (OPERATIONS[OPERATIONS.size() - 1] != '(')) 	
				{
					numBuffer = calculate(OPERATIONS[OPERATIONS.size() - 1], NUMBERS[NUMBERS.size() - 1], NUMBERS[NUMBERS.size() - 2]);
					NUMBERS.pop_back(); NUMBERS.pop_back();		NUMBERS.push_back(numBuffer);	
					OPERATIONS.pop_back();																 
					PRIORITY.pop_back();																
					goto CHECKSTACK;
				}
				else if(OPERATIONS[OPERATIONS.size() - 1] == '(')
				{
					OPERATIONS.push_back(expr[0]);
					PRIORITY.push_back(checkPrior(expr[0]));
				}
			}
	
		}
		
		expr.erase(0, 1);
	END:
		if ((expr.length() == 0)&&(buffer.length()!=0))
			NUMBERS.push_back(strtof((buffer).c_str(), 0));		
	}
	
	while (NUMBERS.size() > 1)
	{
		numBuffer = calculate(OPERATIONS[OPERATIONS.size() - 1], NUMBERS[NUMBERS.size() - 1], NUMBERS[NUMBERS.size() - 2]);
		NUMBERS.pop_back();	NUMBERS.pop_back();				NUMBERS.push_back(numBuffer);
		OPERATIONS.pop_back();
		PRIORITY.pop_back();
	}

	for (int i = 0; i < NUMBERS.size(); i++)
		cout << NUMBERS[i] << endl;
OUT:
	return 0;
}

int checkPrior(char symbol)
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

float calculate(char oper, float num1, float num2)
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
			cout << "Ошибка: деление на ноль" << endl;
	}
}
