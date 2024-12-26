// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
bool readFile(const char* name, vector<string>& Number);
void writeFile(const char* name, vector<string>oldNumber, vector<string> newNumber);
string Convert(string numberOld, int q, int p);
bool Fractional(const string& numberOld, int q, int p, int i, string& numberNew);
bool Whole(const string& numberOld, int q, int p, int& i, string& str);


double DoubleToString(const string& str, int q, int& index);
int IntToString(const string& str, int q, int& index);

bool readFile(const char* name, vector<string>& Number) {
    string str;
    ifstream fin(name);
    if (!fin) {
        cout << "Невозможно открыть файл "<< name<< endl;
        return 0;
    }
    else {
        while (fin >> str) {
            Number.push_back(str);
        }
        fin.close();
        return 1;
    }
}

void writeFile(const char* name, vector<string>oldNumber, vector<string> newNumber) {
    ofstream fout(name);
    if (!fout) {
        cout << "Невозможно открыть файл " << name << endl;
    }
    else {
        fout << "В десятичной --- В четверичной \n";
        for (int i = 0; i < oldNumber.size(); i++) {
            fout << oldNumber[i] << " ------------ " << newNumber[i] << "\n";
        }
        fout.close();
    }
}

string Convert(string numberOld, int q, int p)
{
    bool isNegative = (numberOld[0] == '-');
    int i = isNegative ? 1 : 0;
    std::string numberNew;
    if (!Whole(numberOld, q, p, i, numberNew)) return "error";
        if (i < numberOld.length()) {
            if (!Fractional(numberOld, q, p, i, numberNew)) return "error";
        }
    return isNegative ? "-" + numberNew : numberNew;
}


bool Fractional(const string& numberOld, int q, int p, int i,string& numberNew)
{
    numberNew.push_back('.');
    i += 1;
    //proverka
    int j = i;
    for (j; j < numberOld.length(); j++)
        if (!isdigit(numberOld[j]))
            return false;
    ///
    double eps = 0.5 * pow(q, -(double)(numberOld.length() - i));
    double fractional = DoubleToString(numberOld, q, i);
    double fr = fractional, tmp = 0;
    for (int n = -1; eps < abs(fractional - tmp); n--) {
        fr *= p;
        numberNew.push_back('0' + trunc(fr));
        if (trunc(fr)) {
            tmp += trunc(fr) * pow(p, n);
            fr -= trunc(fr);
        }
    }
    return true;
}
double DoubleToString(const string& str, int q, int & index)
{
    double res = 0, coef = 1. / q;
    for (index; index < str.length(); ++index) {
        res += (str[index] - '0') * coef;
        coef /= q;
    }
    return res;
}

bool Whole(const string & numberOld, int q, int p, int & i, string& str) {
    int j = i;
    for (j; j < numberOld.length() && numberOld[j] != '.'; j++)
        if (!isdigit(numberOld[j]))
            return false;
    ///
    int whole = IntToString(numberOld, q, i);
    while (whole != 0) {
        str = (char)('0' + whole % p) + str;
        whole /= p;
    }
    if (str.empty())
        str = "0";
    return true;
}
int IntToString(const string& str, int q, int& index) {
    int res = 0;
    for (index; index < str.length() && str[index] != '.' && str[index] != ',' && res >= 0; ++index) {
        res = res * q + (str[index] - '0');
    }
    return res;
}


int main()
{   
    setlocale(LC_ALL, "Russian");
    vector <string> Num_10;
    vector <string> Num_4;
    const int p = 4, q = 10;
    const char* nameInputFile = "input.txt";
    const char* nameOutputFile = "output.txt";
//     Чтение файла
    readFile(nameInputFile, Num_10);
    

//     Конвертация
    for (int i = 0; i < Num_10.size(); i++) {
        Num_4.push_back(Convert(Num_10[i], q, p));
    }
//     Вывод в файл

    writeFile(nameOutputFile,Num_10, Num_4);
    cout << "Complete"<<endl;
    return 0;

}
