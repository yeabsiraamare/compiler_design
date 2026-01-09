#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isValidParentheses(const string& expr) {
    stack<char> s;

    for (char ch : expr) {
        // Push opening brackets to the stack
        if (ch == '(' || ch == '{' || ch == '[') 
        {
            s.push(ch);
        }


        // Handle closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') 
        {
            if (s.empty()) {
                return false;         
             }

            char top = s.top();
            s.pop();

            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;            }
        }
    }

    // If stack is empty, parentheses are balanced
    return s.empty();
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    cin >> expression;

    if (isValidParentheses(expression)) {
        cout << "The parentheses are valid." << endl;
    } else {
        cout << "The parentheses are invalid." << endl;
    }

    return 0;
}
