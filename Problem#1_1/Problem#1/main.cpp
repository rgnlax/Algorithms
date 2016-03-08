// Педченко Максим
// 1_3. Даны две рациональные дроби: a/b и c/d. Сложить их и результат представьте в виде несократимой дроби m/n. Вывести числа m и n.

#include <iostream>

void reduction( int&,  int& );
int greaterCommonDiveder ( int, int );

int main()
{
    int firstFractionNumerator, firstFractionDenominator, secondFractionNumerator, secondFractionDenominator;
    std::cin >> firstFractionNumerator >> firstFractionDenominator >> secondFractionNumerator >> secondFractionDenominator;
    
    //Определяем числитель и знаменатель конечной дроби
    int resultFractionNumerator = firstFractionNumerator * secondFractionDenominator + secondFractionNumerator * firstFractionDenominator;
    int resultFractionDenominator = firstFractionDenominator * secondFractionDenominator;
    
    //Сокращаем дробь
    reduction(resultFractionNumerator, resultFractionDenominator);
    
    std::cout << resultFractionNumerator << " " << resultFractionDenominator;

    return 0;
}

void reduction ( int& numerator, int& denominator )
{
    int gcd = greaterCommonDiveder(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

int greaterCommonDiveder ( int firstNumber, int secondNumber)
{
    //Алгоритм Евклида
    while (firstNumber && secondNumber) {
        
        if (firstNumber >= secondNumber)
            firstNumber %= secondNumber;
        else
            secondNumber %= firstNumber;
        
    }
    
    return firstNumber | secondNumber;
}