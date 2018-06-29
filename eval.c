#include "eval.h"

#define SIZE 100



int eval(char*expression) {
    
    int length = 1;
    
    int operations = 0;
    int values = 0;
    
    for (int i = 1; i < SIZE; i++) {
        char current = expression[i];
        
        if (isOperation(current) != isOperation(expression[i-1])) {
            length++;
        }
        if (isOperation(current) == 1) {
            operations++;
            
        }
    }
    
    values = length - operations;
    
    int v[values];
    int o[operations];
    
    int vpointer = -1;
    int opointer = -1;
    
    for (int i = 0; i < SIZE; i++) {
        if (expression[i] == '\0') {
            break;
        }
        if (isOperation(expression[i])) {
            int numeric = getNumeric(expression[i]);
            
            while (opointer >= 0 && numeric < o[opointer]) {
                v[vpointer-1] = modify(v[vpointer-1], v[vpointer], o[opointer]);
                v[vpointer] = 0;
                o[opointer] = 0;
                vpointer--;
                opointer--;
            }
            
            opointer++;
            o[opointer] = numeric;
            
        }else {
            
            int construct = 0;
            
            construct = (int)(expression[i]-'0');
            
            while (i+1 < SIZE && expression[i+1] != '\0' && isOperation(expression[i+1]) == 0){
                construct *= 10;
                i++;
                construct += (int)(expression[i]-'0');
            }
            
            vpointer++;
            v[vpointer] = construct;
        }
    }
    
    while (opointer >= 0) {
        v[vpointer-1] = modify(v[vpointer-1], v[vpointer], o[opointer]);
        v[vpointer] = 0;
        o[opointer] = 0;
        vpointer--;
        opointer--;
    }
    
    return v[0];
    
}

int getNumeric(char in) {
    
    if (in == '+') {
        return 1;
    }
    if (in == '-') {
        return 2;
    }
    if (in == '*') {
        return 3;
    }
    if (in == '/') {
        return 4;
    }
    
    
    return 0;
}

int modify(int a, int b, int op) {
    
    if (op == 1) {
        return a + b;
    }
    if (op == 2) {
        return a - b;
    }
    if (op == 3) {
        return a * b;
    }
    if (op == 4) {
        return a / b;
    }
    
    return 0;
}

int isOperation(char in) {
    return (in == '+' || in == '-' || in == '/' || in == '*') ? 1 : 0;
}
