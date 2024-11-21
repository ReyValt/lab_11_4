#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

void CreateMatrixFile(const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Помилка: не вдалося створити файл.\n";
        return;
    }

    int n, m;
    cout << "Введіть кількість рядків (n) та стовпців (m): ";
    cin >> n >> m;

    fout << n << " " << m << endl;

    cout << "Введіть елементи матриці:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value;
            cin >> value;
            fout << value << " "; 
        }
        fout << endl;
    }

    fout.close();
}


void ProcessMaxInRows(const string& inputFile, const string& outputFile) {
    ifstream fin(inputFile);
    ofstream fout(outputFile);

    if (!fin || !fout) {
        cerr << "Помилка: не вдалося відкрити файли.\n";
        return;
    }

    int n, m;
    fin >> n >> m;
    fout << n << " " << m << endl; 

    vector<vector<int>> matrix(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> matrix[i][j];
        }
    }

  
    for (int i = 0; i < n; ++i) {
        int maxInRow = matrix[i][0];
        for (int j = 1; j < m; ++j) {
            if (matrix[i][j] > maxInRow) {
                maxInRow = matrix[i][j];
            }
        }

        for (int j = 0; j < m; ++j) {
            fout << matrix[i][j] << " ";
        }
        fout << maxInRow << endl;
    }

    fin.close();
    fout.close();
}


void PrintFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Помилка: не вдалося відкрити файл для виведення.\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    fin.close();
}

void Menu(const string& filename) {
    int choice;
    do {
        cout << "\nМеню:\n"
            << "1. Створити новий файл з матрицею\n"
            << "2. Обробити та записати максимальні елементи в новий файл\n"
            << "3. Переглянути файл\n"
            << "4. Вийти\n"
            << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            CreateMatrixFile(filename);
            break;
        case 2:
        {
            string outputFile;
            cout << "Введіть ім'я нового файлу для збереження результатів: ";
            cin >> outputFile;
            ProcessMaxInRows(filename, outputFile);
            cout << "\nВміст нового файлу з максимальними значеннями рядків:\n";
            PrintFile(outputFile);
        }
        break;
        case 3:
            PrintFile(filename);
            break;
        case 4:
            cout << "Завершення роботи програми.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 4);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ukr");

    string filename;
    cout << "Введіть ім'я файлу для роботи: ";
    cin >> filename;

    Menu(filename);

    return 0;
}
