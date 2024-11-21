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
            // ������ ��� ����� istringstream
            string input_data = "2 3\n1 2 3\n4 5 6\n"; // ������ ��� ��� �����
            stringstream input_stream(input_data);
            cin.rdbuf(input_stream.rdbuf()); // ���������� ��� �� ��� ���������� ����

            // ���� ��� ���������� �������
            string filename = "testMatrix.txt";

            // ��������� ������� CreateMatrixFile
            CreateMatrixFile(filename);

            // �������� ����� �����
            ifstream fin(filename);
            Assert::IsTrue(fin.is_open(), L"�� ������� ������� ���� ��� ��������.");

            string line;
            // ������� ������� �����
            getline(fin, line);
            Assert::AreEqual(string("2 3"), line, L"������� ������ ����� � ����.");

            // ������� ������� �����
            getline(fin, line);
            // ��������� ���� ������ � ���� ����� ����� ����������
            line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
            Assert::AreEqual(string("1 2 3"), line, L"������� ���� ������� ����� �����.");

            // ������� �������� �����
            getline(fin, line);
            line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
            Assert::AreEqual(string("4 5 6"), line, L"������� ���� �������� ����� �����.");

            fin.close();

            // ��������� ����� ���� �����
            Assert::IsTrue(remove(filename.c_str()) == 0, L"�� ������� �������� ���� ���� �����.");
        }

        TEST_METHOD(Test_ProcessMaxInRows)
        {
            // ������ ���������� ��� ����� istringstream
            string input_data = "3 3\n1 2 3\n4 5 6\n7 8 9\n";
            stringstream input_stream(input_data);
            cin.rdbuf(input_stream.rdbuf()); // ����������� ����� �� ��� ���������� ����

            string inputFile = "testInput.txt";
            string outputFile = "testOutput.txt";

            // ��������� ������� ����
            ofstream fout(inputFile);
            fout << "3 3\n1 2 3\n4 5 6\n7 8 9\n";
            fout.close();

            // ��������� ������� ��� ������� �������
            ProcessMaxInRows(inputFile, outputFile);

            // �������� ����� ��������� �����
            ifstream fin(outputFile);
            Assert::IsTrue(fin.is_open(), L"�� ������� ������� �������� ���� ��� ��������.");

            string line;
            // �������� ������� �����
            getline(fin, line);
            Assert::AreEqual(string("3 3"), line, L"������� ����� ������� � ������� ����� ��������� �����.");

            // �������� ������� ����� (������������ ������� ����� 3)
            getline(fin, line);
            Assert::AreEqual(string("1 2 3 3"), line, L"������� ���� ������� ����� ��������� �����.");

            // �������� �������� ����� (������������ ������� ����� 6)
            getline(fin, line);
            Assert::AreEqual(string("4 5 6 6"), line, L"������� ���� �������� ����� ��������� �����.");

            // �������� ���������� ����� (������������ ������� ����� 9)
            getline(fin, line);
            Assert::AreEqual(string("7 8 9 9"), line, L"������� ���� ���������� ����� ��������� �����.");

            fin.close();

            // ��������� ����� ���� �����
            Assert::IsTrue(remove(inputFile.c_str()) == 0, L"�� ������� �������� ������� ���� ���� �����.");
            Assert::IsTrue(remove(outputFile.c_str()) == 0, L"�� ������� �������� �������� ���� ���� �����.");
        }

        
	};
}
