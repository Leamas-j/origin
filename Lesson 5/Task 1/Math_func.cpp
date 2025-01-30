#include <iostream>
#include "Math_func.h"

double summ(double a, double b){
    return a + b;
}

double subtract(double a, double b){
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {   
    return  (b != 0) ? a / b : 0;
}

double exponent(double a, double b) {
    double tmp{1};
    for (int i = 0; i < b; ++i) {
        tmp *= a;
    }
    return  tmp;
}
