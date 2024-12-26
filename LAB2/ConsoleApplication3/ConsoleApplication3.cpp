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
string convertFromQtoP(string OldNumber, int q, int p);





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
	double znak = stod(str);
	string number = convertFromQtoP(str, 10, 2);
 
	int k = 0;

	if (number[0] == '-') {
		res.sign = "11";
		number.replace(0, 1, "");
	}
	else res.sign = "00";
	for (int i = 0; i < number.length(); i++) {
		if (number[i] != '.') {
			k += 1;
		}
		else {
			number.replace(i, 1, "");
			break;
		}
	}
	res.p = ToDoublePor(k);
	res.M = number;
	int len = res.M.length();
	if (res.M.length() < k) {
		while (res.M.length() != k) {
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

	if ((max(a.M.length(), b.M.length()) < res.M.length()) or (res.M[0] == '0')) {
		res.sign = Sum(res.sign, "1");
		//res.M.erase(0, 1);
	}
	if (res.sign == "00" or res.sign == "11") {
		return res;
	}
	else {
		if (res.sign == "01") {
			res.M = '1' + res.M;
			res.sign = "00";
			res.p = Sum(res.p, "1");
			res.M.erase(0, 1);
		}
		if (res.sign == "10")
		{
			res.M = '0' + res.M;
			res.sign == "11";
			res.p = Sum(res.p, "1");
		}
		if (res.sign == "110") {
			res.M[0] = '0';
			res.sign = "11";
			res.p = Sum(res.p, "1");
		}
		if (res.sign == "100") {
			res.M.replace(0, 1, "");
			res.M = Sum(res.M, "1");
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
double getDoubleFromString(const string& str, int q, int& index) {
	double res = 0, coef = 1.0 / q;
	for (index; index < str.length(); ++index) {
		res += (str[index] - '0') * coef;
		coef /= q;
	}
	return res;
}

bool getFractionalPart(string numberOld, int q, int p, int i, string& numberNew) {
	numberNew.push_back('.');
	i += 1;
	//proverka
	int j = i;
	for (j; j < numberOld.length(); j++)
		if (!isdigit(numberOld[j]))
			return false;
	///
	double eps = 0.5 * pow(q, -(double)(numberOld.length() - i));
	double fractional = getDoubleFromString(numberOld, q, i);
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

int getIntFromString(string str, int q, int& index) {
	int res = 0;
	for (index; index < str.length() && str[index] != '.'; ++index) {
		res = res * q + (str[index] - '0');
	}
	return res;
}

bool getWholePart(string numberOld, int q, int p, int& i, string& numberNew) {
	//proverka
	int j = i;
	for (j; j < numberOld.length() && numberOld[j] != '.'; j++)
		if (!isdigit(numberOld[j]))
			return false;
	///
	int whole = getIntFromString(numberOld, q, i);
	while (whole != 0) {
		numberNew = (char)('0' + whole % p) + numberNew;
		whole /= p;
	}
	if (numberNew.empty())
		numberNew = "0";
	return true;
}

string convertFromQtoP(string OldNumber, int q, int p) {
	bool isNegative = (OldNumber[0] == '-');
	int i = isNegative ? 1 : 0;
	string numberNew;
	if (!getWholePart(OldNumber, q, p, i, numberNew))
		return "error";
	if (i < OldNumber.length()) {
		if (!getFractionalPart(OldNumber, q, p, i, numberNew))
			return "error";
	}
	return isNegative ? "-" + numberNew : numberNew;
}

double octalToDecimal(const std::string& octalStr) {
	double decimalNum = 0.0;
	int base = 8;
	int pos = 0;

	// Проверяем, есть ли в строке точка
	size_t dotPos = octalStr.find('.');
	if (dotPos != std::string::npos) {
		// Преобразуем целую часть
		string intPart = octalStr.substr(0, dotPos);
		for (char c : intPart) {
			decimalNum = decimalNum * base + (c - '0');
		}

		// Преобразуем дробную часть
		string fracPart = octalStr.substr(dotPos + 1);
		for (char c : fracPart) {
			decimalNum += (c - '0') / pow(base, ++pos);
		}
	}
	else {
		// Преобразуем целое число
		for (char c : octalStr) {
			decimalNum = decimalNum * base + (c - '0');
		}
	}

	return decimalNum;
}




int main() {
	//setlocale(LC_ALL, "Russian");
	//setlocale(LC_NUMERIC, "POSIX");
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

				

				c.sign = Sum(a.sign, b.sign);

				if (ToTenPor(a.p) > ToTenPor(b.p)) {
					int r = ToTenPor(a.p) - ToTenPor(b.p);
					b.M = Rovn(b.M, r);
					c.p = a.p;
				}
				if (ToTenPor(a.p) < ToTenPor(b.p)) {
					int r = ToTenPor(b.p) - ToTenPor(a.p);
					c.p = b.p;
					a.M = Rovn(a.M, r);
				}

				else {
					c.p = a.p;
				}
				//Сложение мантисс


				a = Convert(a);
				b = Convert(b);

				cout << s1 << " = " << a.sign << " " << a.M << " " << a.p << endl;
				cout << s2 << " = " << b.sign << " " << b.M << " " << b.p << endl;


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
				float c1 = stof(s1);
				float c2 = stof(s2);
				//cout << c1+c2 << endl;
				fout << "Проверка вычислением в 10 сс " << s1 << "+" << s2 << " = " << to_string(c1+c2) << endl;
				fout << "\n";
			}
		}
	}
	return 0;
}




