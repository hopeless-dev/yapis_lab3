#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <locale>

using namespace std;

string read();
bool checkSpelling(const string);
vector<string> getLexems(const string, regex);

int main()
{
    setlocale(LC_ALL, "Russian");
    string textFromFile = read();
    cout << textFromFile << endl;
    if (checkSpelling(textFromFile)) {
        regex reg("[VXI]+|\\(|\\)|\\+|-|\\*|:|;");
        for (sregex_iterator iter(textFromFile.begin(), textFromFile.end(), reg), end; iter != end; iter++)
        {
            string strType = "";
            if (iter->str().length() > 1 || iter->str() == "X" || iter->str() == "V" || iter->str() == "I") {
                strType = "Number";
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

vector<string> getLexems(const string stringLine, regex rgx) {
    vector<string> elems;

    sregex_token_iterator iter(stringLine.begin(), stringLine.end(), rgx, -1);
    sregex_token_iterator end;

    while (iter != end) {
        if (*iter != "") {
            elems.push_back(*iter);
        }
        ++iter;
    }
    return elems;
}

bool checkSpelling(const string text) {
    vector<string> dlms = getLexems(text, regex("[VXI]"));
    vector<string> str = getLexems(text, regex("\\(|\\)|\\+|-|\\*|:|;"));

    bool numberNext = true;
    int openBracket = 0, closeBracket = 0;
    for (size_t i = 0, j = 0; i < str.size() || j < dlms.size(); i++, j++) {
        if (j < dlms.size())
            for (const auto& delimeter : dlms[j]) {
                if (delimeter == '(') {
                    openBracket++;
                }
                else if (delimeter == ')') {
                    closeBracket++;
                }
                else if (delimeter == '+' || delimeter == '-' || delimeter == '*' || delimeter == ':') {
                    if (numberNext) {
                        cout << "[ERROR] ��� �����/�������� ����� ��������\n";
                        return false;
                    }
                    numberNext = true;
                }
                else if (delimeter == ';') {
                    if (openBracket != closeBracket) {
                        cout << "[ERROR] ����� � �������: ����������� ������� ������\n";
                        return false;
                    }
                }
                else {
                    cout << "[ERROR] ����������� ������\n";
                    return false;
                }
            }
        if (i < str.size()) {
            for (const auto& str : str[i]) {
                numberNext = false;
                if (str != 'X' && str != 'V' && str != 'I') {
                    cout << "[ERROR] ������������ ��������� ��������\n";
                    return false;
                }
            }
        }
    }
    if (closeBracket != openBracket) {
        cout << "[ERROR] ����������� ������� ������\n";
        return false;
    }
    return true;
}