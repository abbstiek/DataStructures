#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOperator(char currentChar)
{
    switch (currentChar) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '%':
        return true;
    default:
        return false;
    }
}

// returns whether a `lOp` b `rOp` c == (a `lOp` b) `rOp` c
bool precedence(char leftOperator, char rightOperator)
{
    if ( leftOperator == '^' ) {
        return true;
    } else if ( rightOperator == '^' ) {
        return false;
    } else if ( leftOperator == '*' || leftOperator == '/' || leftOperator == '%' ) {
        return true;
    } else if ( rightOperator == '*' || rightOperator == '/' || rightOperator == '%' ) {
        return false;
    }

    return true;
}

#include <stdexcept>
#include <cctype>
#include <sstream>
#include <stack>
std::string convertToPostfix(const std::string& infix)
{
    std::stringstream postfix; // Our return string
    std::stack<char> stack;
    stack.push('('); // Push a left parenthesis ‘(‘ onto the stack.

    for(std::size_t i = 0, l = infix.size(); i < l; ++i) {
        const char current = infix[i];

        if (isspace(current)) {
            // ignore
        }
        // If it's a digit or '.' or a letter ("variables"), add it to the output
        else if(isalnum(current) || '.' == current) {
            postfix << current;
        }

        else if('(' == current) {
            stack.push(current);
        }

        else if(isOperator(current)) {
            char rightOperator = current;
            while(!stack.empty() && isOperator(stack.top()) && precedence(stack.top(), rightOperator)) {
                postfix << ' ' << stack.top();
                stack.pop();
            }
            postfix << ' ';
            stack.push(rightOperator);
        }

        // We've hit a right parens
        else if(')' == current) {
            // While top of stack is not a left parens
            while(!stack.empty() && '(' != stack.top()) {
                postfix << ' ' << stack.top();
                stack.pop();
            }
            if (stack.empty()) {
                throw std::runtime_error("missing left paren");
            }
            // Discard the left paren
            stack.pop();
            postfix << ' ';
        } else {
            throw std::runtime_error("invalid input character");
        }
    }


    // Started with a left paren, now close it:
    // While top of stack is not a left paren
    while(!stack.empty() && '(' != stack.top()) {
        postfix << ' ' << stack.top();
        stack.pop();
    }
    if (stack.empty()) {
        throw std::runtime_error("missing left paren");
    }
    // Discard the left paren
    stack.pop();

    // all open parens should be closed now -> empty stack
    if (!stack.empty()) {
        throw std::runtime_error("missing right paren");
    }

    return postfix.str();
}

#include <iostream>
#include <string>
int main()
{
    for (;;) {
        if (!std::cout.good()) break;
        std::cout << "Enter the Arithmetic Expression: ";
        std::string infix;
        std::getline(std::cin, infix);
        if (infix.empty()) break;

        std::cout << "Postfix: '" << convertToPostfix(infix) << "'\n";
    }

    return 0;
}