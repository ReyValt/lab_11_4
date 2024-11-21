#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_11_4/lab_11_4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
        TEST_METHOD(Test_CreateMatrixFile)
        {
            // Імітуємо ввід через istringstream
            string input_data = "2 3\n1 2 3\n4 5 6\n"; // Імітуємо дані для вводу
            stringstream input_stream(input_data);
            cin.rdbuf(input_stream.rdbuf()); // Перемикаємо ввід на наш фіксований потік

            // Файл для збереження матриці
            string filename = "testMatrix.txt";

            // Викликаємо функцію CreateMatrixFile
            CreateMatrixFile(filename);

            // Перевірка вмісту файлу
            ifstream fin(filename);
            Assert::IsTrue(fin.is_open(), L"Не вдалося відкрити файл для перевірки.");

            string line;
            // Читання першого рядка
            getline(fin, line);
            Assert::AreEqual(string("2 3"), line, L"Невірний перший рядок у файлі.");

            // Читання другого рядка
            getline(fin, line);
            // Видаляємо зайві пробіли з кінця рядка перед порівнянням
            line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
            Assert::AreEqual(string("1 2 3"), line, L"Невірний вміст другого рядка файлу.");

            // Читання третього рядка
            getline(fin, line);
            line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
            Assert::AreEqual(string("4 5 6"), line, L"Невірний вміст третього рядка файлу.");

            fin.close();

            // Видалення файлу після тесту
            Assert::IsTrue(remove(filename.c_str()) == 0, L"Не вдалося видалити файл після тесту.");
        }

        TEST_METHOD(Test_ProcessMaxInRows)
        {
            // Імітуємо консольний ввід через istringstream
            string input_data = "3 3\n1 2 3\n4 5 6\n7 8 9\n";
            stringstream input_stream(input_data);
            cin.rdbuf(input_stream.rdbuf()); // Перемикання вводу на наш фіксований потік

            string inputFile = "testInput.txt";
            string outputFile = "testOutput.txt";

            // Створюємо вхідний файл
            ofstream fout(inputFile);
            fout << "3 3\n1 2 3\n4 5 6\n7 8 9\n";
            fout.close();

            // Викликаємо функцію для обробки матриці
            ProcessMaxInRows(inputFile, outputFile);

            // Перевірка вмісту вихідного файлу
            ifstream fin(outputFile);
            Assert::IsTrue(fin.is_open(), L"Не вдалося відкрити вихідний файл для перевірки.");

            string line;
            // Перевірка першого рядка
            getline(fin, line);
            Assert::AreEqual(string("3 3"), line, L"Невірний розмір матриці в першому рядку вихідного файлу.");

            // Перевірка другого рядка (максимальний елемент рядка 3)
            getline(fin, line);
            Assert::AreEqual(string("1 2 3 3"), line, L"Невірний вміст другого рядка вихідного файлу.");

            // Перевірка третього рядка (максимальний елемент рядка 6)
            getline(fin, line);
            Assert::AreEqual(string("4 5 6 6"), line, L"Невірний вміст третього рядка вихідного файлу.");

            // Перевірка четвертого рядка (максимальний елемент рядка 9)
            getline(fin, line);
            Assert::AreEqual(string("7 8 9 9"), line, L"Невірний вміст четвертого рядка вихідного файлу.");

            fin.close();

            // Видалення файлів після тесту
            Assert::IsTrue(remove(inputFile.c_str()) == 0, L"Не вдалося видалити вхідний файл після тесту.");
            Assert::IsTrue(remove(outputFile.c_str()) == 0, L"Не вдалося видалити вихідний файл після тесту.");
        }

        
	};
}
