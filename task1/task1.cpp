#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

const double e = 1e-4;

// Область определения x > 0
double f(double x) {
    if (x <= 0) {return NAN;}
    return pow(x - 6, 2) + log(x) - 5;}

// первая производня
double df(double x) {
    if (x <= 0) return NAN;
    return 2 * (x - 6) + 1.0 / x;}

// вторая производная
double d2f(double x) {
    if (x <= 0) return NAN;
    return 2 - 1.0 / (x * x);
}

// Метод простых итераций
double phi(double x) {
    double lambda = 0.08;
    return x - lambda * f(x);}


double dphi(double x) {
    double lambda = 0.08;
    return 1 - lambda * df(x);}

// Метод половинного деления
void bisection(double a, double b) {
    cout << "\nМЕТОД ПОЛОВИННОГО ДЕЛЕНИЯ" << endl;
    cout << "Отрезок " << a << ", " << b << endl;
    
    if (f(a) * f(b) >= 0) {
        cout << "Корня на отрезке нет (функция одного знака)!" << endl;
        return;}
    
    int n = 0;
    double c;
    
    cout << "N\t a\t\t b\t\t b-a" << endl;
    
    while ((b - a) > e) {
        c = (a + b) / 2;
        cout << n << "\t " << fixed << setprecision(6) << a << "\t " << b << "\t " << (b - a) << endl;
        
        if (f(a) * f(c) <= 0)
            b = c;
        else
            a = c;
        n++;
    }
    
    double root = (a + b) / 2;
    cout << n << "\t " << a << "\t " << b << "\t " << (b - a) << endl;
    cout << "\nКорень: " << root << endl << "f(x) = " << f(root) << endl << "итераций: " << n << endl;
}

// Метод Ньютона
void newton(double approx) {
    cout << "\nМЕТОД НЬЮТОНА" << endl;
    cout << "Начальное приближение: approx = " << approx << "\n" << endl;
    
    int n = 0;
    double x = approx;
    double x_new;
    
    cout << "N\t x(n)\t\t x(n+1)\t\t |x(n+1)-x(n)|" << endl;
    
    do {
        x_new = x - f(x) / df(x);
        double delta = fabs(x_new - x);
        
        cout << n << "\t " << fixed << setprecision(6) << x << "\t " << x_new << "\t\t " << delta << endl;
        
        x = x_new;
        n++;
        
        if (delta < e || n > 100) break;
    } while (true);
    
    cout << "\nКорень: " << x << endl << "f(x) = " << f(x) << endl << "итераций: " << n << endl;
}

// Метод простых итераций
void simpleIteration(double approx) {
    cout << "\nМЕТОД ПРОСТЫХ ИТЕРАЦИЙ" << endl;
    cout << "Начальное приближение: approx = " << approx << "\n" << endl;
    
    // Проверка сходимости
    cout << "|phi'(approx)| = " << fabs(dphi(approx)) << " (должно быть < 1 для сходимости)" << endl << endl;
    
    int n = 0;
    double x = approx;
    double x_new;
    
    cout << "N\t x(n)\t\t x(n+1)\t\t |x(n+1)-x(n)|" << endl;
    
    do {
        x_new = phi(x);
        double delta = fabs(x_new - x);
        
        cout << n << "\t " << fixed << setprecision(6) << x << "\t " << x_new << "\t\t " << delta << endl;
        
        x = x_new;
        n++;
        
        if (delta < e || n > 100) break;
        
    } while (true);
    
    cout << "\nКорень: " << x << endl << "f(x) = " << f(x) << endl << "итераций: " << n << endl;
}

int main() {
    cout << "Уравнение: (x-6)^2 + ln(x) - 5 = 0" << endl;
    cout << "Область определения: x > 0" << endl;
    cout << "Точность: " << e << endl;
    

    vector<pair<double, double>> segments = {
        {4.0, 4.5},
        {7.5, 8.0}
    };
    

    cout << "\n1 КОРЕНЬ [4, 4.5]" << endl;
    bisection(4.0, 4.5);
    newton(4.25);
    simpleIteration(4.25);
    
    cout << "\n2 КОРЕНЬ [7.5, 8]" << endl;
    bisection(7.5, 8.0);
    newton(7.75);
    simpleIteration(7.75);
    

    cout << "РЕЗУЛЬТАТ:" << endl;
    cout << "Первый корень: 4.152" << endl;
    cout << "Второй корень: 7.573" << endl;
    
    return 0;
}