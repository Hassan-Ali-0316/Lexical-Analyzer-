#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include<regex>
#include<bits/stdc++.h>
using namespace std;

bool Is_a_Keyword(char *str)						//check if the given substring is a keyword or not
{
    char my_keywords[64][18] = {"asm","auto","bool","break","case","catch","char","class","const","const_cast",
								"continue","default","delete","do","double","dynamic_cast","else","enum","explicit",
								"export","extern","false","float","for","friend","goto","if","inline","int","long",
								"main","mutable","namespace","new","operator","private","protected","public",
								"register","reinterpret_cast","return","short","signed","sizeof","static",
								"static_cast","struct","switch","template","this","throw","true","try","typedef",
								"typeid","typename","union","unsigned","using","virtual","void","volatile","wchar_t",
								"while"	};
	int i, flag = 0;
	for(i = 0; i < 64; ++i)
	{
		if(strcmp(my_keywords[i], str) == 0)
		{
			flag = 1;
			break;
		}
	}
	return flag;
}
bool Is_a_Punctuation(char ch)					//check if the given character is a punctuator or not
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' || ch == '>' || ch == '<' ||
		ch == '=' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '&' || ch == '|')
        {
            return true;
        }
    return false;
}

bool Is_a_ValidIdentifier(char* str)						//check if the given identifier is valid or not
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9' || Is_a_Punctuation(str[0]) == true)
        {
            return false;
        }									//if first character of string is a digit or a special character, identifier is not valid
    int i,len = strlen(str);
    if (len == 1)
    {
        return true;
    }										//if length is one, validation is already completed, hence return true
    else
    {
    for (i = 1 ; i < len ; i++)						//identifier cannot contain special characters
    {
        if (Is_a_Punctuation(str[i]) == true)
        {
            return false;
        }
    }
    }
    return true;
}

bool Is_a_Operator(char ch)							//check if the given character is an operator or not
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=' || ch == '|' || ch == '&')
    {
       return true;
    }
    return false;
}


bool Is_a_Number(char* str)							//check if the given substring is a number or not
{
    int i, len = strlen(str),numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0 ; i < len ; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return false;
        } else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
            {
                return false;
            }
    }
    return true;
}

bool Is_a_Letter(char c) 
{
	if((c>='a' && c<='z') || (c>='A' && c<='Z'))
	{
		return true;
	}
	return false;
}

bool Is_a_Separator(char c)
{
	if(c == ')' || c == '(' || c == '{' || c  == '}' || c == '[' || c == ']')
	{
		return true;
	}
	return false;
}

bool isDigit(char c)
{
	if(c>='0' && c<='9')
	{
		return true;
	}
	return false;
}

char* subString(char* realStr, int l, int r)				//extract the required substring from the main string
{
    int i;

    char* str = (char*) malloc(sizeof(char) * (r - l + 2));

    for (i = l; i <= r; i++)
    {
        str[i - l] = realStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}


int interpret(char* str, int token)						//interpreting the expression
{
    int left = 0, right = 0;
    int len = strlen(str);
    while(right <= len && left <= right) 
	{
        if(Is_a_Punctuation(str[right]) == false)			//if character is a digit or an alphabet
        {
            right++;
        }
        if(Is_a_Punctuation(str[right]) == true && left == right)		//if character is a punctuator
        {
	        right++;
	        left = right;
        } 
		else if(Is_a_Punctuation(str[right]) == true && left != right|| (right == len && left != right)) 	
        {
            	//check if parsed substring is a keyword or identifier or number
       	 	char* sub = subString(str, left, right - 1);   //extract substring

	        if (Is_a_Keyword(sub) == true)
	        {
	            cout<< sub <<"\t Is a Keyword\n";
	            token++;
	        }
	        else if (Is_a_Number(sub) == true)
	        {
	            cout<< sub <<"\t Is a Number\n";
	            token++;
	        }
        	else if (Is_a_ValidIdentifier(sub) == true && Is_a_Punctuation(str[right - 1]) == false)
            {
                cout<< sub <<"\t Is a Identifier\n";
                token++;
            }
            else if(Is_a_ValidIdentifier(sub) == false && Is_a_Punctuation(str[right - 1]) == false)
            {
                cout<< sub <<"\t Is not a Valid Identifier\n";
            }
            left = right;
        }
    }
    return token;
}

void lexicalAnalysis(const string& exp)
{
	string token;
	for(char c : exp)
	{
		if(isspace(c))
		{
			continue; // continue if spaces
		}
		else if(isDigit(c))
		{
			token = c;
			cout << "'" << token << "'" << " is an integer\n";
		}
		else if(Is_a_Letter(c))
		{
			token = c;
			cout << "'" << token << "'" << " is a variable\n";
		}
		else if(Is_a_Operator(c))
		{
			token = c;
			cout  << "'" << token << "'" << " is a operator\n";
		}
		else if(Is_a_Separator(c))
		{
			token = c;
			cout << "'" << token << "'" << "is a parenthesis\n";
		}
		else
		{
			cout << "Not a valid identifier\n";
		}
	}
}

bool isValidexpb(const string& exp)
{
	stack<char> s;
	for(char c : exp)
	{
		if(c == '(' || c == '[' || c == '{')
		{
			s.push(c);
		}
		else if(c == ')' || c == ']' || c == '}')
		{
			if(s.empty() || (c == ')' && s.top() != '(') || (c == ']' && s.top() != '[') || (c == '}' && s.top() != '{'))
			{
				return false;	
			} 
			s.pop();
		}
	}
	if(s.empty() == true)
	{
		return true;
	}
	return false;
}
bool isValidexpo(const string& exp)
{
	if(Is_a_Operator(exp[0]) || Is_a_Operator(exp[exp.length()-1]))
	{
		return false;
	}
	for(int i=0 ; i<exp.length() ; i++)
	{
		if(!Is_a_Separator(exp[i]) && !isDigit(exp[i]) && !Is_a_Letter(exp[i]) && !Is_a_Operator(exp[i]))
		{
			return false;
		}
	}
	return true;
}

void gotoxy(short x, short y) 
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Opening_Screen(void)
{
	long int r;
	int i,j;
	int y=5;
	char c = 177;
//	for(i=0;i<20;i++)
//	{
//		gotoxy(15,y);
//		if(i==0||i==19)
//		{	
//			for(j=0;j<75;j++)
//			{
//				cout << c;
//				for(r=0;r<10000000;r++);
//			}
//		}
//		else
//		{
//			for(j=0;j<75;j++)
//			{		
//				if(j==0||j==74)
//				cout << c;
//		
//				else 
//				cout << " ";
//			}
//			for(r=0;r<10000000;r++);
//		}
//		cout<< "";
//		y++;
//	}
	gotoxy(40,14);
	cout << "!!! LEXICAL ANALYZER !!!";
    getch();
    system("cls");
}

int main()
{
	system("color 9F");
	Opening_Screen();
	
	int i,j=0,s=0,count=0,total_lines[3],tokens=0;
	char ch, buffer[100], string1[100], Is_a_Operator[] = "+-*/%=<>|&";
	char Is_a_Separator[] = "{}[](),$;:";
	bool operatorflag, separatorflag;
	string str;
	ifstream file;
	int choice;
	cout << "\n\t\t------------------------------ W E L C O M E -------------------------------\n\n";
	cout << "If you want to analyze a .cpp file enter 1 OR if you want to analyze a mathematical expression enter 2\n";
	cin >> choice;
	if(choice == 1)
	{
		cout << "---------------------------------------------------------------------------------------------------" << endl;
		int a = 0;
		for(int a=0; a<3; a++)
		{
			if(a==0)
			{
				file.open("testprog1.txt");
				while (getline(file, str))
				{
	        		count++;
				}
				total_lines[a] = count;
				file.close();
				file.open("testprog1.txt");
				cout<<"opening the first test-program file for lexical analysis..."<<endl;
			}
			else if(a==1)
			{
				file.open("testprog2.txt");
				while (getline(file, str))
				{
	        		count++;
				}
				total_lines[a] = count;
				file.close();
				file.open("testprog2.txt");
				cout<<"\n\nopening the second test-program file for lexical analysis..."<<endl;
			}
			else if(a==2)
			{
				file.open("testprog3.txt");
				while (getline(file, str))
				{
	        		count++;
				}
				total_lines[a] = count;
				file.close();
				file.open("testprog3.txt");
				cout<<"\n\nopening the third test-program file for lexical analysis..."<<endl;
			}
			
			if(!file.is_open())
			{
				cout<<"error while opening the file\n";
				exit(0);
			}
			while(!file.eof())
			{
			   ch = file.get();
			  
				for(i = 0; i < 10; ++i)
				{
				   if(ch == Is_a_Operator[i])
				   {
						cout<<ch<<"\t Is a Operator\n";
						tokens++;
						operatorflag = 1;
				   }
				}
				for(i = 0; i < 10; ++i)
				{
				   if(ch == Is_a_Separator[i])
				   {
						cout<<ch<<"\t Is a Separator\n";
						tokens++;
						separatorflag = 1;
				   }
				}
				if(ch == '"')
				{
					ch = file.get();
					while(ch!='"')
					{
						string1[s++] = ch;
						ch = file.get();
					}
					string1[s] = '\0';
					cout<<string1<<"\t Is a string"<<endl;
					s=0;
					tokens++;
				}
			   	if(isalnum(ch))
			   	{
			   		buffer[j++] = ch;
			   	}
			   	else if((ch == ' ' || ch == '\n' || ch == '"' || ch == '(' || ch == ')' || operatorflag == 1 || separatorflag == 1) && (j != 0))
			   	{
			   		buffer[j] = '\0';
			   		j = 0;
			   		tokens = interpret(buffer,tokens); 
			   	}
			}
			cout << "Total Numbers of lines in the file : " << total_lines[a] << endl;
			cout << "Total Numbers of tokens in the file : " << tokens << endl;
			cout << "Lexical analysis for this file is complete...closing file" <<endl;
			cout << "---------------------------------------------------------------------------------------------------" << endl;
			file.close();
		}
	}
	if(choice == 2)
	{
		int counter = 0;
		int cc = 1;
		while(1)
		{
			if(counter != 0)
			{
				cout << "Do you want to analyze more expressions?Press 1 else Press any other key\n";
				cin >> cc;
			}
			if(cc == 1)
			{
				string expression;
			    cout << "Enter a mathematical expression: ";
			    fflush(stdin);
			    getline(cin, expression);
			    lexicalAnalysis(expression);
			     
			    if(isValidexpb(expression) && isValidexpo(expression))
			    {
			    	cout << "Mathematical Expression is Valid!\n";
				}
				else
				{
					cout << "Mathematical Expression is Not Valid!\n";
				}
			}
			else
			{
				break;
			}
			counter=1;
			cout << "\n------------------------------------------------------------------\n";
		}
	}
    return 0;
}
