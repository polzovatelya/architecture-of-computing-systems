
#include <iostream>

#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <utility>
#include <vector>

using namespace std;
void Mas(int n, char M[16][4]);
vector<string> Num(string perem);
string Makenormal(string str, vector<string> perem);
void Mas(int n, char M[16][4]);
char AND(char a, char b);
char OR(char a, char b);
char NOT(char a);
char Shef(char a, char b);
char Pirs(char a, char b);
char Sled(char a, char b);
char Iskl(char a, char b);
char Toz(char a, char b);
char Reh(string parse, int n, char M[4]);



vector<string> Num(string perem) {

    vector <string> res = {};
    string r = "";
    for (int i = 0; i < perem.size(); i++) {
        if (perem[i] != ' ') r += perem[i];
        else {
            res.push_back(r);
            r = "";
        }
    }
    res.push_back(r);
    return res;
}

string Makenormal(string str, vector<string> perem) {
    if (perem[0] != "a" && perem[0] != "b" && perem[0] != "c" && perem[0] != "d") {
        vector<string> norm = { "a","b","c", "d" };
        int index;
        for (int i = 0; i < perem.size(); i++) {
            string s = perem[i];

            while ((index = str.find(s)) != std::string::npos)
                str.replace(index, s.size(), norm[i]);
        }
    }
    return str;
}

bool CorrectF(string s) {
    bool fl = true;
    for (auto i : s) {
        if (i != ' ' && i != 'a' && i != 'b' && i != 'c' && i != 'd' && i != '!' && i != '&' && i != '+' && i != '>' && i != '~' && i != '*' && i != '/' && i != '|' && i != '{' && i != '[' && i != '(' && i != ')' && i != ']' && i != '}' && i!='=')
        {
            fl = false;
        }
    }
    return fl;
}


void Mas(int n, char M[16][4])
{
    int n1 = pow(2, n);
    int k = n1 / 2;
    for (int j = 0; j < n; j++) {
        int i = 0;
        do {
            for (int ii = 0; ii < k; i++, ii++) {
                M[i][j] = '0';
             }
            for (int ii = 0; ii < k; i++, ii++) {
                M[i][j] = '1';
            }
        } while (i < n1);
            k /= 2;
     }
    return;
}

vector<string> Solving(char M[16][4], int n, string f) {

    int m = pow(2, n);
    vector<string> Y(m);
    fill(Y.begin(), Y.end(), f);
    int ii;
    for (int j = 0; j < m; j++) {//построчная обработка

        while ((ii = Y[j].find('(')) != std::string::npos) {
            int jj = Y[j].find(')');

            string s = Y[j].substr(ii + 1, jj - ii - 1);

            s = Reh(s, n, M[j]);

            Y[j].replace(ii, jj - ii + 1, s);

        }
        while ((ii = Y[j].find('[')) != std::string::npos) {
            int jj = Y[j].find(']');

            string s = Y[j].substr(ii + 1, jj - ii - 1);
            s = Reh(s, n, M[j]);

            Y[j].replace(ii, jj - ii + 1, s);
        }
        while ((ii = Y[j].find('{')) != std::string::npos) {
            int jj = Y[j].find('}');
            string s = Y[j].substr(ii + 1, jj - ii - 1);
            s = Reh(s, n, M[j]);
            Y[j].replace(ii, jj - ii + 1, s);
        }
        Y[j] = Reh(Y[j], n, M[j]);
    }


    return Y;
}


char Reh(string parse, int n, char M[4]) {
    char fl;
    char k;
    int i;
    while ((i = parse.find('!')) != std::string::npos) {
        char x = parse[i + 1];
        switch (x) {
        case 'a': { x = M[0]; break; }
        case 'b': { x = M[1]; break; }
        case'c': { x = M[2]; break; }
        case 'd': { x = M[3]; break; }
        }
        k = NOT(x);
        parse.replace(i, 2, string(1, k));
    }

    while ((i = parse.find('&')) != std::string::npos) {
        char a = parse[i - 1];
        char b = parse[i + 1];
        switch (a) {
        case 'a': { a = M[0]; break; }
        case 'b': { a = M[1]; break; }
        case'c': { a = M[2]; break; }
        case 'd': { a = M[3]; break; }
        }
        switch (b) {
        case 'a': { b = M[0]; break; }
        case 'b': { b = M[1]; break; }
        case'c': { b = M[2]; break; }
        case 'd': { b = M[3]; break; }
        }
        k = AND(a, b);
        parse.replace(i - 1, 3, string(1, k));
    }
   
    int q;
    while ((i = parse.find('+')) != std::string::npos || (q = parse.find('*')) != std::string::npos) {
        q = parse.find('*');
        i = parse.find('+');

        if (i > 0 && q > 0) {
            if (i < q) {
                char a = parse[i - 1];
                char b = parse[i + 1];
                switch (a) {
                case 'a': { a = M[0]; break; }
                case 'b': { a = M[1]; break; }
                case'c': { a = M[2]; break; }
                case 'd': { a = M[3]; break; }
                }
                switch (b) {
                case 'a': { b = M[0]; break; }
                case 'b': { b = M[1]; break; }
                case'c': { b = M[2]; break; }
                case 'd': { b = M[3]; break; }
                }
                k = OR(a, b);
                parse.replace(i - 1, 3, string(1, k));
            }
            else {
                char a = parse[q - 1];
                char b = parse[q + 1];
                switch (a) {
                case 'a': { a = M[0]; break; }
                case 'b': { a = M[1]; break; }
                case'c': { a = M[2]; break; }
                case 'd': { a = M[3]; break; }
                }
                switch (b) {
                case 'a': { b = M[0]; break; }
                case 'b': { b = M[1]; break; }
                case'c': { b = M[2]; break; }
                case 'd': { b = M[3]; break; }
                }
                k = Iskl(a, b);
                parse.replace(q - 1, 3, string(1, k));
            }
        }
        else {
            if (i > 0) {
                char a = parse[i - 1];
                char b = parse[i + 1];
                switch (a) {
                case 'a': { a = M[0]; break; }
                case 'b': { a = M[1]; break; }
                case'c': { a = M[2]; break; }
                case 'd': { a = M[3]; break; }
                }
                switch (b) {
                case 'a': { b = M[0]; break; }
                case 'b': { b = M[1]; break; }
                case'c': { b = M[2]; break; }
                case 'd': { b = M[3]; break; }
                }
                k = OR(a, b); parse.replace(i - 1, 3, string(1, k));
            }
            else {
                char a = parse[q - 1];
                char b = parse[q + 1];
                switch (a) {
                case 'a': { a = M[0]; break; }
                case 'b': { a = M[1]; break; }
                case'c': { a = M[2]; break; }
                case 'd': { a = M[3]; break; }
                }
                switch (b) {
                case 'a': { b = M[0]; break; }
                case 'b': { b = M[1]; break; }
                case'c': { b = M[2]; break; }
                case 'd': { b = M[3]; break; }
                }
                k = Iskl(a, b);
                parse.replace(q - 1, 3, string(1, k));
            }
        }
    }
    while ((i = parse.find('>')) != std::string::npos) {
        char a = parse[i - 1];
        char b = parse[i + 1];
        switch (a) {
        case 'a': { a = M[0]; break; }
        case 'b': { a = M[1]; break; }
        case'c': { a = M[2]; break; }
        case 'd': { a = M[3]; break; }
        }
        switch (b) {
        case 'a': { b = M[0]; break; }
        case 'b': { b = M[1]; break; }
        case'c': { b = M[2]; break; }
        case 'd': { b = M[3]; break; }
        }
        k = Sled(a, b);

        parse.replace(i - 1, 3, string(1, k));

    }
    while ((i = parse.find('~')) != std::string::npos) {
        char a = parse[i - 1];
        char b = parse[i + 1];
        switch (a) {
        case 'a': { a = M[0]; break; }
        case 'b': { a = M[1]; break; }
        case'c': { a = M[2]; break; }
        case 'd': { a = M[3]; break; }
        }
        switch (b) {
        case 'a': { b = M[0]; break; }
        case 'b': { b = M[1]; break; }
        case'c': { b = M[2]; break; }
        case 'd': { b = M[3]; break; }
        }
        k = Toz(a, b);
        parse.replace(i - 1, 3, string(1, k));
    }
    while ((i = parse.find('|')) != std::string::npos || (q = parse.find('/')) != std::string::npos) {
        q = parse.find('/');
        i = parse.find('|');
        if (i > 0 && q > 0) {
            if (i < q) {
                char a = parse[i - 1];
                char b = parse[i + 1];
                switch (a) {
                case 'a': { a = M[0]; break; }
                case 'b': { a = M[1]; break; }
                case'c': { a = M[2]; break; }
                case 'd': { a = M[3]; break; }
                }
                switch (b) {
                case 'a': { b = M[0]; break; }
                case 'b': { b = M[1]; break; }
                case'c': { b = M[2]; break; }
                case 'd': { b = M[3]; break; }
                }
                k = Shef(a, b);
                parse.replace(i - 1, 3, string(1, k));
            }
            else {
                char a = parse[q - 1];
                char b = parse[q + 1];
                switch (a) {
                case 'a': { a = M[0]; break; }
                case 'b': { a = M[1]; break; }
                case'c': { a = M[2]; break; }
                case 'd': { a = M[3]; break; }
                }
                switch (b) {
                case 'a': { b = M[0]; break; }
                case 'b': { b = M[1]; break; }
                case'c': { b = M[2]; break; }
                case 'd': { b = M[3]; break; }
                }
                k = Pirs(a, b);
                parse.replace(q - 1, 3, string(1, k));
            }
        }
        else {
            if (i > 0) {
                char a = parse[i - 1];
                char b = parse[i + 1];
                switch (a) {
                case 'a': { a = M[0]; break; }
                case 'b': { a = M[1]; break; }
                case'c': { a = M[2]; break; }
                case 'd': { a = M[3]; break; }
                }
                switch (b) {
                case 'a': { b = M[0]; break; }
                case 'b': { b = M[1]; break; }
                case'c': { b = M[2]; break; }
                case 'd': { b = M[3]; break; }
                }
                k = Shef(a, b); parse.replace(i - 1, 3, string(1, k));
            }
            else {
                char a = parse[q - 1];
                char b = parse[q + 1];
                switch (a) {
                case 'a': { a = M[0]; break; }
                case 'b': { a = M[1]; break; }
                case'c': { a = M[2]; break; }
                case 'd': { a = M[3]; break; }
                }
                switch (b) {
                case 'a': { b = M[0]; break; }
                case 'b': { b = M[1]; break; }
                case'c': { b = M[2]; break; }
                case 'd': { b = M[3]; break; }
                }
                k = Pirs(a, b);
                parse.replace(q - 1, 3, string(1, k));
            }
        }
    }
    return parse[0];
}
char AND(char a, char b) {
    int fl = (a == b && a == '1');
    return to_string(fl)[0];
}
char OR(char a, char b) {
    int fl = ((a == '1') || (b == '1'));
    return to_string(fl)[0];
}
char NOT(char a) {
    int fl = !('1' == a);
    return to_string(fl)[0];
}

char Shef(char a, char b) {
    char fl;
    fl = OR(NOT(a), NOT(b));
    return fl;
}
char Pirs(char a, char b) {
    char fl;
    fl = (AND(NOT(a), NOT(b)));
    return fl;
}
char Sled(char a, char b) {
    char fl;
    fl = OR(NOT(a), b);
    return fl;
}
char Iskl(char a, char b) {
    char fl;
    fl = OR(AND(NOT(a), b), AND((a), NOT(b)));
    return fl;
}
char Toz(char a, char b) {
    char fl;
    fl = OR(AND(NOT(a), NOT(b)), AND((a), b));
    return fl;
}
void Print(string func, vector<string> perem, char M[16][4], vector<string> Y, int m, ofstream& fout) {
    int n = pow(2, m);
    string top = " ";
    for (int i = 0; i < perem.size(); i++) {
        top += perem[i] + " | ";
    }
    fout << "Функция \t";
    fout << "Y= " << func << "\n";
    fout << "Таблица истинности\n";

    string st(top.size() + 2, ' ');
    st += "\n";
    fout << st;
    fout << top << "Y \n";
    fout << st;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            string r(perem[j].size(), ' ');
            fout << r << M[i][j] << " |";
        }
        fout << " " << Y[i] << "\n";
        fout << st;
    }
}



int main()
{
    setlocale(LC_ALL, "rus");
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    if (!fin) { 
        cout << "Невозможно открыть файл ввода\n"; 
    }

    else {
        if (!fout) cout << "Невозможно открыть файл вывода\n";
        else {
            char b[16][4];
            vector<string> v;
            string perem;
            string function, function_;
            int len_vector;
            getline(fin, perem);
            vector<string> first_vector = Num(perem);
            len_vector = first_vector.size();
            if (len_vector < 5) {
                getline(fin, function_);
                function = Makenormal(function_, first_vector);
                if (CorrectF(function)) {
                    Mas(len_vector, b);
                    v = Solving(b, len_vector, function);
                    Print(function_, first_vector, b, v, len_vector, fout);
                }
                else {
                    cout << "Недопустимые символы для функции";
                }
            }
            else { cout << "Слишком много переменных"; }
            fout.close();
            fin.close();
        }
        system("pause");

    }

}
