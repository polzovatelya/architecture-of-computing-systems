// Laba2Arch.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <sstream>

using namespace std;


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





void writeFile(const char* name, vector<string>oldNumber, vector<string> newNumber) {
	ofstream fout(name);
	if (!fout) {
		fout << "Невозможно открыть файл вывода\n";
	}
	else {
		fout << "Перевод чисел из десятичной системы счисления в семеричную .\n";
		for (int i = 0; i < oldNumber.size(); i++) {
			fout << oldNumber[i] << " --> " << newNumber[i] << "\n";
		}
		fout.close();
	}
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



int OctSum(int a, int b) {
	int sum = 0, carry = 0, d = 0, m = 1;
	while (a || b || carry) {
		d = 0;
		d = carry + (a % 10) + (b % 10);
		a /= 10; b /= 10;
		if (d > 7) {
			carry = 1;
			d = d % 8;
		}
		else {
			carry = 0;
		}
		sum += d * m;
		m *= 10;
	}
	return sum;     
}

string Summer(string left, string right, int q, int i) {
	int poridok1 = 0, poridok2 = 0;
	int a = 0, b= 0, a1 = 0, b1 = 0;
	string s;
	a = getIntFromString(left, q, i);
	if (i < left.length()) {
		i += 1;
		poridok1 = left.length() - i;
		a1 = getIntFromString(left, q, i);
	}
	i = 0;
	b = getIntFromString(right, q, i);
	if (i < right.length()) {
		i += 1;
		poridok2 = right.length() - i;
		b1 = getIntFromString(right, q, i);
	}
	int maxPoridok = max(poridok1, poridok2);
	if (poridok2 == maxPoridok) {
		a1 = a1 * pow(10, (maxPoridok - poridok1));
	}
	else
		b1 = b1 * pow(10, (maxPoridok - poridok2));

	int res = OctSum(a, b);
	int frac = OctSum(a1, b1);
	cout << frac << endl;
	res = res + frac* pow(10, -maxPoridok);
	if (frac != 0)
		 s = to_string(res) + '.' + to_string(frac);
	else
		 s = to_string(res);
	cout << s << endl;
	return s;
}


double octalToDecimal(const std::string& octalStr) {
	double decimalNum = 0.0;
	int base = 8;
	int pos = 0;

	// Проверяем, есть ли в строке точка
	size_t dotPos = octalStr.find('.');
	if (dotPos != std::string::npos) {
		// Преобразуем целую часть
		std::string intPart = octalStr.substr(0, dotPos);
		for (char c : intPart) {
			decimalNum = decimalNum * base + (c - '0');
		}

		// Преобразуем дробную часть
		std::string fracPart = octalStr.substr(dotPos + 1);
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





int main()
{
	const int p = 8, q = 10;
	setlocale(LC_ALL, "rus");
	string Numbers1;
	string Numbers2;
	stringstream ss, ss1;
	double num1, num2;
	string res;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	if (fin){
		while (getline(fin, Numbers1) && getline(fin, Numbers2)) {
			ss.clear();
			ss1.clear();

			string convertNumber1 = convertFromQtoP(Numbers1, q, p);
			string convertNumber2 = convertFromQtoP(Numbers2, q, p);

			//if (convertNumber1.length() == convertNumber2.length()) {
			//	string dif = octalSubtraction(convertNumber1, convertNumber2);
			//	cout << "dif" << dif << endl;
			//}

			bool isNegative1 = (Numbers1[0] == '-');
			bool isNegative2 = (Numbers2[0] == '-');
			if (convertNumber1 != "error" && convertNumber2 != "error" && isNegative1 == isNegative2) {
				if (isNegative1)
					convertNumber1 = convertNumber1.erase(0, 1);
				if (isNegative2)
					convertNumber2 = convertNumber2.erase(0, 1);
				res = Summer(convertNumber1, convertNumber2, q, 0);
				ss << Numbers1;
				ss >> num1;
				ss1 << Numbers2;
				ss1 >> num2;
				fout << " Сумма в 10 с.с " << "\n";
				fout << Numbers1 << " + " << Numbers2 << " = " << num1 + num2 << "\n";
			}
			else
			{
				fout << " Сумма в 10 с.с " << "\n";
				fout << Numbers1 << " + " << Numbers2 << " = " << "error" << "\n";
				res = "error";
			}
			if (isNegative1 && isNegative2) {
				res = "-" + res;
				convertNumber1 = "-" + convertNumber1;
				convertNumber2 = "-" + convertNumber2;
			}
				
			fout << " Сумма в 8 с.с " << "\n";
			fout << convertNumber1 << " + " << convertNumber2 << " = " << res << "\n";
			fout << "\n";
			if (res != "error") {
				
				//int decimalNum = stoi(res, 0, 8);
				//if (decimalNum - num1 + num2 != 0) {
				//	string str = res.erase(res.find('.'), res.length());
				//	int fracNum = stoi(str, 0, 8);
				//	cout << fracNum << endl;
				//}
				//decimalNum = decimalNum + fracNum * pow(10, res.length() - res.find('.') + 1);
				double decimalNum;
				if (res[0] == '-') {
					decimalNum = octalToDecimal(res.erase(0, 1));
					decimalNum = -decimalNum;

				}
				else {
					decimalNum = octalToDecimal(res);
				}
				fout << " Проверка = " << to_string(decimalNum) << "\n";
				fout << "\n";
			}
		}
	}
	else
	{
		cout << "Файл со входными данными не был открыт\n";
		return 0;
	}

}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
