#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

double add(double a, double b, int m) {return fmod(a + b, m);}

double sub(double a, double b, int m) {
    double result = a - b;
    if (result < 0) result += m;
    return fmod(result, m);
}

double mul(double a, double b, int m) {return fmod(a * b, m);}

double xor_op(double a, double b, int m) {
    int int_a = (int)a;
    int int_b = (int)b;
    return (double)((int_a ^ int_b) % m);
}

vector<double> fibonacci_generator(int a, int b, int m, const vector<double>& initial, char operation) {
    int n = max(a, b);
    vector<double> seq = initial;
    
    // Генерация последовательности
    for (int i = n; i < n + 6; i++) {
        double prev_a = seq[i - a];
        double prev_b = seq[i - b];
        double new_value;
        switch (operation) {
        case '+':
            new_value = add(prev_a, prev_b, m);
            break;
        case '-':
            new_value = sub(prev_a, prev_b, m);
            break;
        case '*':
            new_value = mul(prev_a, prev_b, m);
            break;
        case '^':
            new_value = xor_op(prev_a, prev_b, m);
            break;
        default:
            throw invalid_argument("Неверная операция. Используйте +, -, * или ^");}
        seq.push_back(new_value);
    }
    return seq;}

// Функция для проверки является ли чиисло целым
bool is_integer(double x) {return floor(x) == x;}

int main() {
    try {
        int a, b, m;
        char operation;
        
        // Ввод параметров a b m целых чисел
        cout << "Введите параметр a (целое положительное число, лаг): ";
        cin >> a;
        if (a <= 0) {
            throw invalid_argument("a должно быть положительным целым числом");
        }
        
        cout << "Введите параметр b (целое положительное число, лаг): ";
        cin >> b;
        if (b <= 0) {
            throw invalid_argument("b должно быть положительным целым числом");
        }
        
        cout << "Выберите операцию (+, -, *, ^ для XOR): ";
        cin >> operation;
        
        cout << "Введите модуль m (целое положительноечисло): ";
        cin >> m;
        if (m <= 0) {
            throw invalid_argument("m должно быть положительным целым числом");
        }
        
        int n = max(a, b);
        vector<double> initial_values;
        
        cout << "Введите " << n << " начальных значений (вещественные числа):" << endl;
        for (int i = 0; i < n; i++) {
            double value;
            cout << "S[" << i << "] = ";
            cin >> value;
            initial_values.push_back(value);
        }
        
        // Генерация последовательности
        vector<double> result;
        result = fibonacci_generator(a, b, m, initial_values, operation);

        
        cout << "\nСгенерированная последовательность:" << endl;
        for (const double& val : result) { 
            if (is_integer(val)) {
                cout << (int)val << " ";
            } else {
                cout << fixed << setprecision(3) << val << " ";
            }
        }
        cout << endl;
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}