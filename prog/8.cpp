#include <iostream>
#include <vector>

using namespace std;

// Функция объединения двух отсортированных подмассивов и подсчета инверсий
long long merge(vector<int>& arr, int left, int middle, int right) 
{
    long long inversions = 0;

    // временные вспомогательные массивы
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    // Копирование данных во временные массивы
    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[middle + 1 + j];

    // Объединение двух подмассивов в основной массив
    int i = 0;
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        }
        else {
            // Если элемент из второго подмассива меньше, чем из первого,
            // это означает наличие инверсии.
            arr[k] = rightArr[j];
            ++j;
            inversions += n1 - i;
        }
        ++k;
    }

    // Копирование оставшихся элементов первого подмассива
    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    // Копирование оставшихся элементов второго подмассива
    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }

    return inversions;
}

// Функция для сортировки массива и подсчета общего количества инверсий
long long mergeSort(vector<int>& arr, int left, int right) {
    long long inversions = 0;

    if (left < right) {
        int middle = left + (right - left) / 2;

        // Рекурсивная сортировка двух половинных подмассива
        inversions += mergeSort(arr, left, middle);
        inversions += mergeSort(arr, middle + 1, right);

        // Слияние двух отсортированных подмассивов и подсчет инверсий
        inversions += merge(arr, left, middle, right);
    }

    return inversions;
}

// Функция для подсчета количества инверсий в массиве
long long countInversions(vector<int>& arr) {
    int size = arr.size();
    return mergeSort(arr, 0, size - 1);
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<int> arr = { 8, 8, 3, 5, 1, 3, 9 };
    long long inversions = countInversions(arr);

    cout << "Количество инверсий: " << inversions << endl;

    return 0;
}