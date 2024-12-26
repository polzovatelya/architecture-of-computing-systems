// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


bool Check(string str);
string ToDoublePor(int x);
string ToDoubleM(double x);
double ToTenM(string M);
int ToTenPor(string ch);





class Normal
{
public:
	string sign;
	string p;
	string M;
	Normal() {};
	string normal_string() {
		string rez = "";
		if (sign == "11") rez += "-";
		else rez += '+';
		rez += "0." + M + " * " + "(10)^" + p;
		return rez;
	}
};

bool Check(string str)
{
	int i = 0;
	if ((int)str[i] == '-') i = 1;
	bool res = true;
	bool fl = false; //наличие одной точки
	for (int j = i; j < str.size(); j++)
	{
		if (!isdigit((int)str[i]))
		{
			if (!fl && str[i] == '.')
			{
				fl = true;
			}
			else
			{
				res = false;
				break;
			}
		}
	}
	return res;
}

Normal to_double(string str)
{
	Normal res;
	double number = stod(str);
	if (number < 0) {
		res.sign = "11";
		number = -number;
	}
	else res.sign = "00";
	int k = 0;
	if (number >= 1) {
		while (pow(2, k) <= number) { k += 1; }
	}
	else if (number < 1 / 2) {
		while (pow(2, k) >= number) { k -= 1; }
	}
	number = number / (pow(2, k));
	auto pos = str.find('.');
	if (pos != string::npos)
	{
		string newstr = str.substr(pos + 1);
		newstr.erase(newstr.begin() + 1, newstr.end());
		if (stoi(newstr) < 5)
			k--;
	}
	res.p = ToDoublePor(k);
	res.M = ToDoubleM(number);
	int len = res.M.length();
	if (res.M.length() < k) {
		while (res.M.length() != k){
			res.M += '0';
		}
	}
	return res;
}
string ToDoublePor(int x)
{
	if (x == 0)
		return "0";
	else {
		string s = "";
		int a, b;
		while (x > 0) {
			a = x / 2;
			b = x % 2;
			x = a;
			s += (b + '0');
		}
		reverse(s.begin(), s.end());
		return s;
	}
}

string ToDoubleM(double x)
{
	string res, str;
	while ((x * 2) != 1)
	{
		x = x * 2;
		str = to_string(x);
		res += str[0];
		if (str[0] == '1') { x -= 1; }
	}
	res += '1';
	return res;
}



string Sum(string str1, string str2)
{
	string res;
	//выравние по количеству символов строки
	while (str1.size() > str2.size())
		str2 = "0" + str2;
	while (str2.size() > str1.size())
		str1 = "0" + str1;
	//сумма
	bool flag = false;
	for (long int i = str1.size() - 1; i >= 0; i--)
	{
		if (str1[i] == '0' && str2[i] == '0') {
			if (!flag) {
				res += '0';
				flag = false;
			}
			else {
				res += '1';
				flag = false;
			}
		}
		else if (str1[i] == '1' && str2[i] == '1') {
			if (!flag) {
				res += '0';
				flag = true;
			}
			else {
				res += '1';
				flag = true;
			}
		}
		else if (flag) {
			res += '0';
			flag = true;
		}
		else {
			res += '1';
			flag = false;
		}
	}
	if (flag) res += '1';
	reverse(res.begin(), res.end());
	return res;
}
Normal Convert(Normal x) {
	if (x.sign == "11") {
		for (int i = 0; i <= x.M.length(); i++) {
			if (x.M[i] == '1') {
				x.M[i] = '0';
			}
			else {
				x.M[i] = '1';
			}
		}
	}
	return x;
}



Normal Poryadok(Normal a, Normal b, Normal res) {
	
	if (max(a.M.length(), b.M.length()) < res.M.length()) {
		res.sign = Sum(res.sign, "1");
		res.M.erase(0, 1);
	}
	if (res.sign == "00" or res.sign == "11") {
		return res;
	}
	else {
		if (res.sign == "01") {
			res.M = '1' + res.M;
			res.sign = "00";
			res.M.erase(0, 1);
		}
		if (res.sign == "10")
		{
			res.M = '0' + res.M;
			res.sign == "11";
			res.p = Sum(res.p, "1");
		}
		if (res.sign == "110"){
			res.M[0] = '0';
			res.sign = "11";
			res.p = Sum(res.p, "1");
		}
		if (res.sign == "100") {
			res.M[res.M.length()-1] = '1';
			res.sign = "00";
		}
	}
	return res;
}

string Rovn(string str1, int r) {
	for (int i = 0; i < r; i++) {
		str1 = '0' + str1;
	}
	return str1;
}

double ToTenM(string M)
{
	double k = 0;
	int n = M.size() - 1;
	for (int j = 0; j <= n; j++) {
		k += ((M[j]) - '0') * pow(2, -(j + 1));
	}
	return k;
}
int ToTenPor(string ch)
{
	int result = 0;
	for (int i = 1; i <= ch.size(); i++)
		result += (ch[ch.size() - i] - '0') * (pow(2, i - 1));
	//знак
	if (ch[0] == '-') result = -result;
	return result;
}
double ToTenNormal(Normal ch) {
	double res;
	double res_M = ToTenM(ch.M);
	res = pow(2, ToTenPor(ch.p)) * res_M;
	if (ch.sign == "11") res = -res;
	return res;
}


int main() {
	setlocale(LC_ALL, "Russian");
	ifstream fin("input.txt");
	if (!fin) {
		cout << "Невозможно открыть файл input.txt" << endl;
	}
	else {
		ofstream fout("output.txt");
		if (!fout) {
			cout << "Невозможно открыть файл output.txt" << endl;
		}
		else {
			string chisla;
			while (!fin.eof()) {
				string s1, s2;
				fin >> s1 >> s2;
				if (!Check(s1) || !Check(s2)) {
					fout << "Исходные данные " << s1 << " " << s2 << " error\n";
					continue;
				}
				Normal a, b, c;

				a = to_double(s1);
				b = to_double(s2);

				cout << "Результат: " << a.normal_string() << " = " << ToTenNormal(a) << "\n";
				cout << "Результат: " << b.normal_string() << " = " << ToTenNormal(b) << "\n";

				c.sign = Sum(a.sign, b.sign);

				if (ToTenPor(a.p) > ToTenPor(b.p)) {
					int r = ToTenPor(a.p) - ToTenPor(b.p);
					b.M = Rovn(b.M, r);
					c.p = a.p;
				}
				if (ToTenPor(a.p) < ToTenPor(b.p)) {
					int r = ToTenPor(b.p) - ToTenPor(a.p);
					c.p = b.p;
					a.M = Rovn(a.M,r);
				}
				else {
					c.p = a.p;
				}
				//Сложение мантисс


				a = Convert(a);
				b = Convert(b);

				c.M = Sum(a.M, b.M);

				c = Poryadok(a, b, c);

				//c = Convert(c);

				



				//c.M = Umnozh(a.M, b.M);

				int cp = ToTenPor(c.p);
				int ap = ToTenPor(a.p);
				int bp = ToTenPor(b.p);
				
				c.p = ToDoublePor(cp);

				c.p = ToDoublePor(cp);
				fout << "Исходные числа \n";
				fout << s1 << " = " << a.normal_string() << "\n";
				fout << s2 << "=" << b.normal_string() << "\n";
				fout << "Результат: " << c.normal_string() << " = " << ToTenNormal(c) << "\n";
				fout << "Проверка вычислением в 10 сс " << s1 << "+" << s2 << " = " << stod(s1) + stod(s2) << endl;
				fout << "\n";
			}
		}
	}
	return 0;
}
			
		


