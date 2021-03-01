#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <locale>

using namespace std;

string read();

int main()
{
	setlocale(LC_ALL, "Russian");
	string textFromFile = read();
	cout << textFromFile << endl;
	regex reg("[VXI]+|\\(|\\)|\\+|-|\\*|:|;");
	for (sregex_iterator iter(textFromFile.begin(), textFromFile.end(), reg), end; iter != end; iter++)
	{
		string strType = "";
		if (iter->str().length() > 1 || iter->str() == "X" || iter->str() == "V" || iter->str() == "I") {
			strType = "�����";
		}
		else if (iter->str() == "(") strType = "��������� ������";
		else if (iter->str() == ")") strType = "�������� ������";
		else if (iter->str() == "*") strType = "���� ���������";
		else if (iter->str() == ":") strType = "���� �������";
		else if (iter->str() == "+") strType = "���� ��������";
		else if (iter->str() == "-") strType = "���� ���������";
		else if (iter->str() == ";") strType = "����� � �������";
		cout << setw(10) << iter->str() << string(10, ' ') << strType << endl;
	}
	return 0;
}

string read()
{
	string textFromFile;
	ifstream fin("input.txt");
	fin >> textFromFile;
	return textFromFile;
}