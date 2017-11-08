//
//  main.cpp
//  Infix to Postfix
//
//  Created by David Kleyman on 11/5/17.
//  Copyright © 2017 David Kleyman. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

struct node {
    char data;
    node* next;
};

class Stack {
public:
    void push(char data){
        node* newNode = new node;
        newNode->data = data;

        if (head == NULL){
            newNode->next = NULL;
        }else{
            node* temp = head;
            newNode->next = temp;
        }
        head = newNode;
        top = newNode;
    }
    void pop(){
        node* temp = head;
        head = temp->next;
        delete temp;

        if (head == NULL){
            top = NULL;
        }
    }
    char Top(){
        top = head;
        if (top == NULL){
            return '-1';
        }
        return top->data;
    }
    bool isEmpty(){
        if (head == NULL){
            return true;
        }else{
            return false;
        }
    }
    void display(){
        node* temp = head;
        while(temp){
            cout << temp->data << "\t";
            temp = temp->next;
        }
    }
private:
    node* head = NULL;
    node* top = NULL;
};

int getWeight(char symbol){
    switch (symbol) {
        case '*':
        case '/':
            return 2;
            break;

        case '+':
        case '-':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

bool determineOperator(char symbol){
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'){
        return true;
    }else{
        return false;
    }
}

bool isHigherOrder(char symbolOne, char symbolTwo){
    int one = getWeight(symbolOne);
    int two = getWeight(symbolTwo);

    if (one == two){
        return true;
    }

    return one < two ? true : false;
}

string convertToPostFix(string expression){
    Stack stack;
    string string = "";

    for (int i = 0; i < expression.length(); i++){
        if (expression[i] == '('){
            stack.push(expression[i]);
        }else if (expression[i] == ')'){
            stack.pop();
        }
    }
    if (!stack.isEmpty()){
        cout << "Unbalanced parenthesis" << endl;
        return "";
    }
    else{
        for (int i = 0; i < expression.length(); i++){
            if (expression[i] == ' '){
                continue;
            }
            else if (determineOperator(expression[i])){
                while (isHigherOrder(stack.Top(), expression[i]) && !stack.isEmpty() && stack.Top() != '('){
                    string += stack.Top();
                    stack.pop();
                }
                stack.push(expression[i]);
            }
            else if (expression[i] == '('){
                stack.push(expression[i]);
            }
            else if (expression[i] == ')'){
                while(!stack.isEmpty() && stack.Top() != '(') {
                    string += stack.Top();
                    stack.pop();
                }
                stack.pop();
            }else{
                string += expression[i];
            }

        }

        while (!stack.isEmpty()){
            string += stack.Top();
            stack.pop();
        }

    }
    return string;
}

int main(){
    string expression;

    cout << "Enter an expression to convert: ";
    getline(cin, expression);

    string postFix = convertToPostFix(expression) == "" ? "Error" : convertToPostFix(expression);

    cout << "Infix " << expression << " conversion to postfix is: " << postFix << endl;

}

