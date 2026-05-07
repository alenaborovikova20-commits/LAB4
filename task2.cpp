#include <iostream>
#include <random>
#include <algorithm>
#include <map>

using namespace std;

vector<int> first_move(int n){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100, 150);

    vector<int> arr(n);
    for (int& elem : arr){elem = dist(gen);}
    return arr;
}

void second_move(const vector<int>& arr){
    int max1 = -1, max2 = -1, min_val = *min_element(arr.begin(), arr.end());
    int min_ind = -1, max2_ind = -1;

    for (int i : arr){
        if (i > max1){
            max2 = max1;
            max1 = i;
        } else if (i > max2 && i != max1){max2 = i;}
    }
    
    for (size_t i = 0; i < arr.size(); ++i){
        if (min_val == arr[i] && min_ind == -1){min_ind = i;}
        if (max2 == arr[i]){max2_ind = i;}
    }

    int sum = 0;
    int start = min(min_ind, max2_ind);
    int end = max(min_ind, max2_ind);
    for (int i = start + 1; i < end; ++i){
        sum += arr[i];
    }
    cout << "\n\t\t2 пункт"<< endl;
    cout << "Минимальный элемент: " << min_val << ". Его индекс: " << min_ind << endl;
    cout << "Второй максимальный элемент: " << max2 << ". Его индекс: " << max2_ind << endl;
    cout << "Cумма элементов между ними: " << sum << endl;
}

void third_move(int n){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist1(-50, 50);

    vector<int> arr1(n), arr2(n), arr(n);
    
    for (int& elem : arr1){
        elem = dist1(gen);
    }
    for (int& elem : arr2){
        elem = dist1(gen);
    }

    for (int i = 0; i < n; ++i){
        if (i % 2 == 0){arr[i] = arr2[i] + arr1[i];
        } else {arr[i] = arr1[i] - arr2[i];}}

    cout << "\n\t\t 3 пункт" << endl;
    cout << "Первый массив: " << endl;
    for (int i : arr1){cout << i << " ";}
    cout << "\nВторой массив: " << endl;
    for (int i : arr2){cout << i << " ";}
    cout << "\nПолучившийся массив: " << endl;
    for (int i : arr){cout << i << " ";}
}

void fourth_move(const vector<int>& arr){
    map<int, int> dict;
    for (int i : arr){
        dict[i]++;
    }
    cout << "\n\n\t\t 4 пункт" << endl;
    cout << "элемент : количество повторений" << endl;
    for (pair<int, int> i : dict){
        cout << i.first << " : " << i.second << ", ";
    }
}

bool leapYear(int year){return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);}

void fifth_move(){
    cout << "\n\t\t 5 пункт" << endl;
    int start, end;
    while (1){
        cout << "Введите начальный год: "<< endl;
        cin >> start;
        cout << "Введите конечный год: "<< endl;
        cin >> end;
        if ( end >= start){break;}else{cout << "Некорректные данные! Попробуйте еще раз" << endl;}
    }
    vector<int> leap_years;
    for (int i = start; i <= end; ++i){
        if(leapYear(i)){leap_years.push_back(i);}}
    cout << "Високосные годы с " << start << " по " << end << endl;
    if (leap_years.empty()){
        cout << "В этом диапазоне нет високосных годов." << endl;
    }
    for (int year : leap_years){
        cout << year << " ";
    }
}

int main(){
    int n;
    while (1){
        cout << "Введите число n: ";
        cin >> n;
        if (n >= 10){break;}
        else{cout << "Некорректные данные! Попробуйте еще раз" << endl;}
    }
    cout << "\t\t1 пункт" << endl;
    vector<int> arr = first_move(n);
    for (int i : arr){cout << i << " ";}
    second_move(arr);
    third_move(n);
    fourth_move(arr);
    fifth_move();
    return 0;
}