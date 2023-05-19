#include <iostream>
#include <map>
#include <list>
#include <string>

using namespace std;

void symbolCheck(string str) {
    if (str[0] == ' ') {
        str.erase(0, 1);
    }
    else {
        str.erase(str.size() - 1);
    }
    int count = 0;
    string symbol, goodstr;
    int number;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            symbol = str.substr(count, i - count);
            count = i + 1;
            if (symbol != "+" && symbol != "-" && symbol != "*" && symbol != "/") {
                try {
                    number = stoi(symbol);
                    goodstr += symbol;
                    goodstr += " ";
                }
                catch (...) {
                    cout << symbol << " = ";
                    symbol.erase();
                    cin >> symbol;
                    goodstr += symbol;
                    goodstr += " ";
                }
            }
            else {
                goodstr += symbol;
                goodstr += " ";
            }
        }
    }
    symbol = str.substr(count);
    if (symbol != "+" && symbol != "-" && symbol != "*" && symbol != "/") {
        try {
            number = stoi(symbol);
            goodstr += symbol;
            goodstr += " ";
        }
        catch (...) {
            cout << symbol << " = ";
            symbol.erase();
            cin.ignore();
            getline(cin, symbol);
            goodstr += symbol;
            goodstr += " ";
        }
    }
    else {
        goodstr += symbol;
        goodstr += " ";
    }

    cout << "\nИтог: " << goodstr << "\n";
}

void definePost(string symbol, string& polishNote, list <string>& stackOp) {
    map <string, int> priority = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"(", 0}, {")", 0} };
    if (symbol != "+" && symbol != "-" && symbol != "*" && symbol != "/" && symbol != "(" && symbol != ")") {
        polishNote += symbol;
        polishNote += " ";
    }
    else if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/") {
        bool check = false;
        while (check == false) {
            if ((stackOp.begin() == stackOp.end()) || (priority[symbol] > priority[stackOp.back()])) {
                stackOp.push_back(symbol);
                check = true;
            }
            else if (priority[stackOp.back()] >= priority[symbol]) {
                polishNote += stackOp.back();
                polishNote += " ";
                stackOp.pop_back();
            }
        }
    }
    else if (symbol == "(") {
        stackOp.push_back(symbol);
    }
    else if (symbol == ")") {
        while (stackOp.back() != "(") {
            polishNote += stackOp.back();
            polishNote += " ";
            stackOp.pop_back();
        }
        stackOp.pop_back();
    }
    return;
}

void definePref(string symbol, string& polishNote, list <string>& stackOp) {
    map <string, int> priority = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"(", 0}, {")", 0} };
    if (symbol != "+" && symbol != "-" && symbol != "*" && symbol != "/" && symbol != "(" && symbol != ")") {
        polishNote += symbol;
        polishNote += " ";
    }
    else if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/") {
        bool check = false;
        while (check == false) {
            if ((stackOp.begin() == stackOp.end()) || (priority[symbol] > priority[stackOp.back()])) {
                stackOp.push_back(symbol);
                check = true;
            }
            else if (priority[stackOp.back()] >= priority[symbol]) {
                polishNote += stackOp.back();
                polishNote += " ";
                stackOp.pop_back();
            }
        }
    }
    else if (symbol == "(") {
        stackOp.push_back(symbol);
    }
    else if (symbol == ")") {
        while (stackOp.back() != "(") {
            polishNote += stackOp.back();
            polishNote += " ";
            stackOp.pop_back();
        }
        stackOp.pop_back();
    }
    return;
}

void post(string& polishNote) {
    list <string> stackOp;
    string symbol;

    cout << "Введите выражение(Каждый символ нужно писать через пробел)\n"
        << "Например: ( 1 + 2 ) * 3\n";

    cin >> symbol;
    definePost(symbol, polishNote, stackOp);
    // Вывод прогресса решения
    cout << "Строка: " << polishNote << "\t\tСтэк: ";
    for (auto it = stackOp.begin(); it != stackOp.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";
    // Вывод прогресса решения
    while (cin.get() != '\n') {
        cin >> symbol;
        definePost(symbol, polishNote, stackOp);
        // Вывод прогресса решения
        cout << "Строка: " << polishNote << "\t\tСтэк: ";
        for (auto it = stackOp.begin(); it != stackOp.end(); it++) {
            cout << *it << " ";
        }
        cout << "\n";
        // Вывод прогресса решения
    }
    while (stackOp.begin() != stackOp.end()) {
        polishNote += stackOp.back();
        polishNote += " ";
        stackOp.pop_back();
    }

}

void pref() {
    list <string> stackOp;
    string polishNote;
    string str;

    cout << "Введите выражение(Каждый символ нужно писать через пробел)\n"
        << "Например: ( 1 + 2 ) * 3\n";
    cin.ignore();
    getline(cin, str);
    reverse(str.begin(), str.end());
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(')
            str[i] = ')';
        else if (str[i] == ')')
            str[i] = '(';
    }

    cout << "\n" << str << "\n";

    int count = 0;
    string symbol;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            symbol = str.substr(count, i - count);
            count = i + 1;
            definePref(symbol, polishNote, stackOp);
            // Вывод прогресса решения
            cout << "Строка: " << polishNote << "\t\tСтэк: ";
            for (auto it = stackOp.begin(); it != stackOp.end(); it++) {
                cout << *it << " ";
            }
            cout << "\n";
            // Вывод прогресса решения
        }
    }
    symbol = str.substr(count);
    definePref(symbol, polishNote, stackOp);
    // Вывод прогресса решения
    cout << "Строка: " << polishNote << "\t\tСтэк: ";
    for (auto it = stackOp.begin(); it != stackOp.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";
    // Вывод прогресса решения

    while (stackOp.begin() != stackOp.end()) {
        polishNote += stackOp.back();
        polishNote += " ";
        stackOp.pop_back();
    }
    reverse(polishNote.begin(), polishNote.end());
    symbolCheck(polishNote);
}

void check(list <int>& stack, string symbol) {
    map <string, int> priority = { {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4} };
    int num1;
    if (stack.begin() != stack.end())
        num1 = stack.back();
    else {
        cout << "ERROR\n";
        return;
    }
    stack.pop_back();

    int num2;
    if (stack.begin() != stack.end())
        num2 = stack.back();
    else {
        cout << "ERROR\n";
        return;
    }
    stack.pop_back();

    switch (priority[symbol]) {
        case 1: { //+
            num1 += num2;
            stack.push_back(num1);
            break;
        }
        case 2: { //-
            num2 -= num1;
            stack.push_back(num2);
            break;
        }
        case 3: { //*
            num1 *= num2;
            stack.push_back(num1);
            break;
        }
        case 4: { //ДЕЛИТЬ
            double num = num1 / num2;
            stack.push_back(int(num));
            break;
        }
    }
}

void postSolve(string& str) {
    list <int> stack;

    int count = 0;
    string symbol;
    int number;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            symbol = str.substr(count, i - count);
            count = i + 1;
            if (symbol != "+" && symbol != "-" && symbol != "*" && symbol != "/") {
                try {
                    number = stoi(symbol);
                }
                catch (...) {
                    cout << "ERROR\n";
                    return;
                }
                stack.push_back(number);
            }
            else
                check(stack, symbol);
        }
    }
    symbol = str.substr(count);
    check(stack, symbol);

    if (stack.size() != 1)
        cout << "ERROR\n";
    else
        cout << "Ответ: " << stack.back() << "\n";
}

void prefSolve(string& str) {
    list <int> stack;

    int count = 0;
    string symbol;
    int number;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            symbol = str.substr(count, i - count);
            count = i + 1;
            if (symbol != "+" && symbol != "-" && symbol != "*" && symbol != "/") {
                try {
                    number = stoi(symbol);
                }
                catch (...) {
                    cout << "ERROR\n";
                    return;
                }
                stack.push_back(number);
            }
            else
                check(stack, symbol);
        }
    }
    symbol = str.substr(count);
    check(stack, symbol);

    if (stack.size() != 1)
        cout << "ERROR\n";
    else {
        reverse(str.begin(), str.end());
        cout << "Ответ: " << stack.back() << "\n";
    }
}

int main() {
    setlocale(0, "");
    int input;

    Menu: {
        system("cls");
        cout << "Что желаете сделать?:\n"
            << "1. Преобразовать выражение.\n"
            << "2. Вычислить выражение.\n"
            << "0. Выход.\n";
    }
    cin >> input;
    switch (input) {
        case 1: {
            int input1;

            Menu1: {
                system("cls");
                cout << "В какую форму?:\n"
                    << "1. Прямая польская нотация.\n"
                    << "2. Обратная польская нотация.\n"
                    << "0. Выход.\n";
            }
            cin >> input1;
            switch (input1) {
                case 1: {
                    system("cls");
                    pref();
                    system("pause");
                    goto Menu;
                }
                case 2: {
                    system("cls");
                    string polishNote;
                    post(polishNote);
                    symbolCheck(polishNote);
                    system("pause");
                    goto Menu;
                }
                case 0: {
                    goto Menu;
                }
                default: {
                    cout << "\nНеверный ввод.\n\n";
                    cin.clear();
                    while (cin.get() != '\n');
                    system("pause");
                    goto Menu1;
                }
            }
        }
        case 2: {
            int input2;

            Menu2: {
                system("cls");
                cout << "Какое выражение?:\n"
                    << "1. Обычное.\n"
                    << "2. Прямое.\n"
                    << "3. Обратное.\n"
                    << "0. Выход.\n";
            }
            cin >> input2;
            switch (input2) {
                case 1: {
                    system("cls");
                    string str;
                    post(str);
                    str.erase(str.size() - 1);
                    postSolve(str);

                    system("pause");
                    goto Menu;
                }
                case 2: {
                    system("cls");
                    string str;
                    cout << "Введите выражение(Каждый символ нужно писать через пробел)\n";
                    cin.ignore();
                    getline(cin, str);
                    reverse(str.begin(), str.end());
                    prefSolve(str);
                    system("pause");
                    goto Menu;
                }
                case 3: {
                    system("cls");
                    string str;
                    cout << "Введите выражение(Каждый символ нужно писать через пробел)\n";
                    cin.ignore();
                    getline(cin, str);
                    postSolve(str);
                    system("pause");
                    goto Menu;
                }
                case 0: {
                    goto Menu;
                }
                default: {
                    cout << "\nНеверный ввод.\n\n";
                    cin.clear();
                    while (cin.get() != '\n');
                    system("pause");
                    goto Menu2;
                }
            }
            system("pause");
            goto Menu;
        }
        case 0: {
            cout << "\n*Смэрть*\n";
            break;;
        }
        default: {
            cout << "\nНеверный ввод.\n\n";
            cin.clear();
            while (cin.get() != '\n');
            system("pause");
            goto Menu;
        }
    }
}