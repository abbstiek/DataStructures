//Abygail Stiekman 10/24/2016
//COP4530 Assignment #3

#include "stack.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <utility>

using namespace std;
using namespace cop4530;

//convert infix to postfix, returns pair containing converted number and error code
pair<string, int> infix2postfix(const vector<string> &infix, map<string, int> &operators) {
    Stack<string> s;
    string answer;
    int error_code = 0;
    bool op_flag = false;               //signals last input was operator
    bool op_flag2 = false;              // signals last input was operand
    bool right_parenth_flag = false;    //signals last input was right parenthesis

    //--BEGIN INPUT CYCLE--
    for (int I = 0; I < infix.size(); ++I)
    {
        //if(this input is operand)
        if (operators.count(infix[I]) < 1)
        {
            //--ERROR CHECK--
            //if(last input was ")" AND this input is operand)
            //if(last input was operand AND this input is operand)
            if(right_parenth_flag == true || op_flag2 == true)
            {                   //error: missing operator - two operands in a row
                error_code = 3; //error: missing operator - example: 6 + ( 4 + 5) 8
            }
            answer += infix[I] + " ";

            //--SET STATE FLAGS--
            op_flag = false;
            op_flag2 = true;
            right_parenth_flag = false;
        } //if( this input is +, -, *, /, or "(" operator )
        else if (operators.count(infix[I]) > 0 && infix[I].compare(")") != 0)
        {
            //--CHECK FOR ERRORS--
            //if( this is first input AND input is anything other than "(" )
            if(I == 0 && infix[I].compare("(") != 0)
                error_code = 1; // error: missing operand - operator at beginning of input

            //if( this is last input AND input is anything other than ")" )
            if( I == (infix.size() - 1) )
                error_code = 1; // error: missing operand - operator at end of input

            //if(last input was operand AND this input is "(" OR ")" )
            if(op_flag2 && ( infix[I].compare("(") == 0 || infix[I].compare(")") == 0) )
                error_code = 3; //error: missing operator example: 6 ( 4 + 5)

            //if (last input was anything other than ")" AND this input IS NOT "(")
             if((op_flag == true && !right_parenth_flag) && infix[I].compare("(") != 0)
                error_code = 1; //error: missing operand - two operators in a row

            //--PERFORM CONVERSION OPERATIONS--
            while (!s.empty() && s.top().compare("(") != 0  && (operators[s.top()] >= operators[infix[I]]) )
            {
                answer += s.top() + " ";
                s.pop();
            }
            s.push(infix[I]);
            //--SET STATE FLAGS--
            op_flag = true;
            op_flag2 = false;
            right_parenth_flag = false;

          //if( this input is ")" operator )
        } else if (infix[I].compare(")") == 0 )
        {
            //--PERFORM CONVERSION OPERATIIONS--
            // output and pop stack until "("
            while (!s.empty() && s.top().compare("(") != 0 )
            {
                answer += s.top() + " ";
                s.pop();
            }
            // pop "(" from stack, but dont output it
            if(!s.empty())
            {
                s.pop();
            } else
            {   //we popped everything off and didn't see a "("
                error_code = 2; // error: missing parenthesis
            }

            //--ERROR CHECK--
            if(op_flag == true)
                error_code = 1; //error: missing operand - two operators in a row
            //--SET STATE FLAGS--
            op_flag = true;
            right_parenth_flag = true;
            op_flag2 = false;
        }
    }
    //--END INPUT CYCLE--

    //--EMPTYING STACK--
    while (!s.empty())
    {
        if(s.top().compare("(") == 0)
        {
            error_code = 2; // error: missing parenthesis
        }
        answer += s.top() + " ";
        s.pop();
    }
    return make_pair(answer, error_code);
}

string print_error(int error_code, string exp)
{
    string response = "";
    switch(error_code)
    {
        case 0:
            response = "";
            break;
        case 1:
            response = "Error: Missing operand in postfix string. Unable to evaluate postfix string!\n";
            break;
        case 2:
            response = "\nError: Infix expression: " + exp + " has mismatched parens!\n";
            break;
        case 3:
            response = "Error: Missing operator in postfix string. Unable to evaluate postfix string!\n";
            break;
    }
    return response;
}

//tokenize using space as delimeter
void tokenize(vector<string> &output, string input)
{
    string buffer;
    for(int x = 0; x < input.size(); x++)
    {
        if(isspace(input[x]) == 0)
        {
            buffer += input[x];
        }
        else
        {
            output.push_back(buffer);
            buffer = "";
        }

        if( x == (input.size()-1) && buffer.compare("") != 0 )
            output.push_back(buffer);
    }
}
//checks operands to see if they are variables or literals
bool evaluate(vector<string> &input)
{
    bool eval = true;
    char c;
    int input_size = input.size();
    for(int x  = 0; x <  input_size && eval != false; x++)
    {
        for(int y = 0; y < (input[x]).size(); y++)
        {
            c = (input[x])[y];
            if(isalpha(c))
            {
                eval = false;
                break;
            }
        }
    }
    return eval;
}

int main(){
bool DEBUG = false;
map<string, int> operators;
operators["("] = 3;
operators[")"] = 3;
operators["/"] = 2;
operators["*"] = 2;
operators["+"] = 1;
operators["-"] = 1;

string input;
vector<string> holder;
pair<string, int> response;
string postfix;
int error_code = 0;
while(true)
{
    cout << "Enter infix expression (\"exit\" to quit): ";
    getline(cin, input);
	while(error_code == 0){
    if(input.compare("exit") == 0)
        exit(0);

    tokenize(holder, input);
    response = infix2postfix(holder, operators);
    postfix = response.first;
    error_code  = response.second;

    if(error_code != 2 && error_code > 1) 
        cout << endl << "Postfix expression: " << postfix;

    holder.clear();
    tokenize(holder, postfix);

    if(error_code < 1 && evaluate(holder))
    {
        cout << endl << "Postfix evaluation: " << postfix << " = ";
        Stack<double> s;
        string temp;
        string oper;
        double first_op;
        double sec_op;
        double t_dbl;
        double ans;
        for(int x  = 0; x < holder.size(); x++)
        {
            temp = holder[x];
            if( (t_dbl = strtod(temp.c_str(),NULL)) != 0.0 )
            {
                s.push(t_dbl);
            } else if(!s.empty())
            {
                sec_op = s.top();
                s.pop();
                first_op =  s.top();
                s.pop();
                if(temp.compare("*") == 0)
                {
                    ans = first_op * sec_op;
                    s.push(ans);
                }
                else if(temp.compare("/") == 0)
                {
                    ans = first_op / sec_op;
                    s.push(ans);
                }
                else if(temp.compare("+") == 0)
                {
                    ans = first_op + sec_op;
                    s.push(ans);
                }
                else if(temp.compare("-") == 0)
                {
                    ans = first_op - sec_op;
                    s.push(ans);
                }
            }
        }
        cout << s.top() << endl;
    }
    else
    {
        if(error_code == 0)
		 cout << endl << "Postfix evaluation: " << postfix << " = " << postfix << endl;
        else if(error_code == 1 || error_code == 3)
            cout << endl << "Postfix evaluation: " << postfix << " = " << endl;
    }
    cout << print_error(error_code, input);
    holder.clear();
}
return 0;
}
}
