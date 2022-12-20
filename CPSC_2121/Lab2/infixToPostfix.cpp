/*
 * Keenan Grant
 * 9/19/22
 * 003
 * Lab 2: Infix to Postfix Conversion
 */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

//Converts an infix arithmetic expression into postfix
//The function takes 3 parameters
//First parameter: array of strings for infix expression
//    each string is either an integer number or operator symbol
//Second parameter: number of strings in infix expression
//Third parameter: array of strings for postfix expression
//    generated by function, same format as first parameter
//    assumes that postfix is at least the size of postfix
//Return value: int, number of strings in postfix expression
//    Returns 0 if an error is encountered when converting expression
//    An error occurs with a mismatched parenthesis, e.g. ( ( ) or ( ) ) etc.
//Operator symbols:
// ( : left parenthesis, all operations between this and ")" take place first
// ) : right parenthesis, all op.s back to previous "(" take place first
// * : multiplication, higher precedence - takes place before "+" and "-"
// / : division, higher precedence - takes place before "+" and "-"
// % : remainder, higher precedence - takes place before "+" and "-"
// + : addition, lower precedence - takes place after "*" , "/" , "%"
// - : subtraction, lower precedence - takes place after "*" , "/" , "%"
//The function is not specified to work with any other operator symbols
//Any string in infix may be assumed to be an integer operand if none
// of the above symbols


//Method that tests if an infix element is a digit
bool isDigit(string number) {
    for (int i = 0; i < number.length(); i++) {
        if (!isdigit(number[i])) {
            return false;
        }
    }
    return true;
}

//Method that converts an operator to a number according to their precedence
int precedence(string symbol) {
    if (symbol == "*" || symbol == "/" || symbol == "%") {
        return 2;
    }
    else if (symbol == "+" || symbol == "-") {
        return 1;
    }
    else {
        return 0;
    }
}

int infixToPostfix(string infix[], int length, string postfix[]) {
    int postfixElement = 0;
    stack<string> operators;

    //Testing parenthesis
    int parenthesis = 0;
    for (int i = 0; i < length; i++) {
        if (infix[i] == "(" || infix[i] == ")") {
            parenthesis++;
        }
    }

    if (parenthesis % 2 == 1) {
        return 0;
    }
    else {
        for (int j = 0; j < length; j++) {
            //Adds digits to the postfix array
            if (isDigit(infix[j])) {
                postfix[postfixElement] = infix[j];
                postfixElement++;
            }
            //Adds open parenthesis to the stack
            else if (infix[j] == "(") {
                operators.push(infix[j]);
            }
            /*When closing parenthesis is detected it moves the
            operators from the stack to the postfix array until
            an open bracket is detected*/
            else if (infix[j] == ")") {
                while (operators.top() != "(") {
                    postfix[postfixElement] = operators.top();
                    postfixElement++;
                    operators.pop();
                }
                operators.pop();
            }
            //Adds operators to the stack according to their precedence
            else {
                while (!operators.empty() && (precedence(infix[j]) <= precedence(operators.top()))) {
                    postfix[postfixElement] = operators.top();
                    postfixElement++;
                    operators.pop();
                }
                operators.push(infix[j]);
            }
        }
        //Adds the last operators to the postfix array
        while (!operators.empty()) {
            postfix[postfixElement] = operators.top();
            postfixElement++;
            operators.pop();
        }

        return length - parenthesis;
    }
}

//Main function to test infixToPostfix()
//Should convert 2 + 3 * 4 + ( 5 - 6 + 7 ) * 8
//            to 2 3 4 * + 5 6 - 7 + 8 * +
/*int main() {
    string infixExp[] = {"5", "+", "42", "/", "(", "30", "/",
                         "(", "20", "/", "(", "12", "/", "(",
                         "6", "/", "(", "4", "/", "2", ")",
                         ")", ")", ")"}; //one more left parenthesis
    string postfixExp[24] = {"5", "42", "30", "20", "12", "6", "4",
                             "2", "/", "/", "/", "/", "/", "/",
                             "+"};
    int postfixLength;

    cout << "Infix expression: ";
    for (int i=0; i<25; i++) {
        cout << infixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: 15" << endl << endl;

    postfixLength = infixToPostfix(infixExp, 24, postfixExp);

    cout << "Postfix expression: ";
    for (int i=0; i<postfixLength; i++) {
        cout << postfixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: " << postfixLength << endl;
    
    return 0;
}*/