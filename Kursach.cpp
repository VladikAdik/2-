#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream> 
#include <Windows.h>

using namespace std;
using namespace chrono;

struct node {
    node* left;
    node* right;
    int data;
};

struct Trunk {
    Trunk* prev;
    string str;

    Trunk(Trunk* prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

int height(node* tree) {
    if (tree == 0)
        return 0;
    int hLeft = height(tree->left);
    int hRight = height(tree->right);
    if (hLeft > hRight)
        return hLeft + 1;
    else
        return hRight + 1;
}

void turnLeft(node*& tree) {
    node* p, * q;
    p = tree->right;
    q = p->left;
    p->left = tree;
    tree->right = q;
    tree = p;
}

void turnRight(node*& tree) {
    node* q, * p;
    q = tree->left;
    p = q->right;
    q->right = tree;
    tree->left = p;
    tree = q;
}

void bigLeftTurn(node*& tree) {
    turnRight(tree->right);
    turnLeft(tree);
}

void bigRightTurn(node*& tree) {
    turnLeft(tree->left);
    turnRight(tree);
}

void balancing(node* &tree) {
    if (tree == 0)
        return;
    if (height(tree->left) - height(tree->right) > 1) {
        if (height(tree->left->left) < height(tree->left->right))
            bigRightTurn(tree);
        else
            turnRight(tree);
    }
    else if (height(tree->right) - height(tree->left) > 1) {
        if (height(tree->right->right) < height(tree->right->left))
            bigLeftTurn(tree);
        else
            turnLeft(tree);
    }
}

void insert(node*& tree, int data) {
    if (tree == 0) {
        tree = new node;
        tree->data = data;
        tree->left = tree->right = 0;
    }
    else {
        if (tree->data == data)
            return;
        if (data < tree->data) {
            insert(tree->left, data);
            balancing(tree);
        }
        else if (data > tree->data) {
            insert(tree->right, data);
            balancing(tree);
        }
    }
}

int maxData(node* tree) {
    if (tree->right == 0)
        return tree->data;
    else
        return maxData(tree->right);
}

void deleteEl(node*& tree, int data) {
    if (tree) {
        if (data > tree->data)
            deleteEl(tree->right, data);
        else if (data < tree->data)
            deleteEl(tree->left, data);
        else {
            if (tree->left == 0 && tree->right == 0) {
                delete tree;
                tree = 0;
            }
            else if (tree->right == 0) {
                node* a = tree;
                tree = tree->left;
                delete a;
            }
            else if (tree->left == 0) {
                node* a = tree;
                tree = tree->right;
                delete a;
            }
            else {
                int max = maxData(tree->left);
                tree->data = max;
                deleteEl(tree->left, max);
            }
        }
    }
    else {
        cout << "Данного элемента нет в дереве\n";
        return;
    }
}

void showTrunks(Trunk* &trunk) {
    if (trunk == NULL)
        return;
    showTrunks(trunk->prev);
    cout << trunk->str;
}

void showTree(node* &tree, Trunk* prev, bool isRight) {
    if (tree == NULL) return;
    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);
    showTree(tree->right, trunk, true);
    if (!prev) {
        trunk->str = "--->";
    }
    else if (isRight) {
        trunk->str = ".-->";
        prev_str = "   |";
    }
    else {
        trunk->str = "`-->";
        prev->str = prev_str;
    }
    showTrunks(trunk);
    cout << tree->data << endl;
    if (prev) prev->str = prev_str;
    trunk->str = "   |";
    showTree(tree->left, trunk, false);
}

void search(node* tree, int data) {
    if (tree) {
        if (data == tree->data) {
            cout << "Элемент " << data << " есть в дереве.\n";
            return;
        }
        else if (data > tree->data)
            search(tree->right, data);
        else if (data < tree->data)
            search(tree->left, data);
    }
    else {
        cout << "Данного элемента нет в дереве\n";
        return;
    }
}

void trunksFile(Trunk* (&trunk), ofstream& file) {
    if (trunk == 0)
        return;
    trunksFile(trunk->prev, file);
    file << trunk->str;
}

void treeFile(node* &tree, Trunk* prev, bool isRight, ofstream& file) {
    if (tree == 0)
        return;
    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);
    treeFile(tree->right, trunk, true, file);
    if (!prev) {
        trunk->str = "--->";
    }
    else if (isRight) {
        trunk->str = ".-->";
        prev_str = "   |";
    }
    else {
        trunk->str = "`-->";
        prev->str = prev_str;
    }
    trunksFile(trunk, file);
    file << tree->data << endl;
    if (prev) prev->str = prev_str;
    trunk->str = "   |";
    treeFile(tree->left, trunk, false, file);
}

void task() {
    system("cls");
    node* tree = 0;
    cout << "Сколько заданий сгенерировать?\n";
    int N;
    cin >> N;

    ofstream output_task;
    ofstream output_key;
    ofstream output_ans;
    output_task.open("output_task.txt");
    output_key.open("output_key.txt");
    output_ans.open("output_ans.txt");

    srand(time(0));
    for (int i = 0; i < N; i++) {
        int key = rand() % 3; //    0 - создание   1 - удаление    2 - вставка 
        output_key << "\n" << i + 1 << ".\n";
        switch (key) {
            case 0: {
                int length = rand() % 10 + 1;
                output_task << i + 1 << ". Создать АВЛ - дерево из " << length << " элементов: ";
                for (int j = 0; j < length; j++) {
                    int data = 99 - (rand() % 199);
                    insert(tree, data);
                    output_task << data << " ";
                    treeFile(tree, 0, false, output_key);
                    output_key << "\n\n";
                }
                output_task << "\n";
                output_ans << "\n" << i + 1 << ".\n";
                treeFile(tree, 0, false, output_ans);
                break;
            }
            case 1: {
                int length = rand() % 10 + 1;
                int num;
                for (int j = 0; j < length; j++) {
                    int data = 99 - (rand() % 199);
                    num = data;
                    insert(tree, data);
                }
                output_ans << "\n" << i + 1 << ".\n";
                treeFile(tree, 0, false, output_ans);
                output_ans << "\n";

                treeFile(tree, 0, false, output_key);
                output_key << "\n";

                output_task << i + 1 << ". Удалить число " << num << " из дерева.\n";

                deleteEl(tree, num);
                treeFile(tree, 0, false, output_ans);
                treeFile(tree, 0, false, output_key);
                break;
            }
            case 2: {
                int length = rand() % 10 + 1;
                for (int j = 0; j < length; j++) {
                    int data = 99 - (rand() % 199);
                    insert(tree, data);
                }
                output_ans << "\n" << i + 1 << ".\n";
                treeFile(tree, 0, false, output_ans);
                output_ans << "\n";

                treeFile(tree, 0, false, output_key);
                output_key << "\n";

                int num = 99 - (rand() % 199);
                output_task << i + 1 << ". Добавить число " << num << " в дерево.\n";

                insert(tree, num);
                treeFile(tree, 0, false, output_ans);
                treeFile(tree, 0, false, output_key);
                break;
            }
        }
    }
}

int main() {
    setlocale(0, "");
    node* tree = 0;

    cout << "Как создать АВЛ-дерево?\n"
        << "1. Автоматически из N элементов\n"
        << "2. В ручную\n";
    int input;
    cin >> input;
    switch (input) {
        case 1: {
            int N, data;
            system("cls");
            cout << "N = ";
            cin >> N;
            srand(time(0));
            auto time1 = steady_clock::now();
            for (int i = 0; i < N; i++) {
                data = 99 - (rand() % 199);
                insert(tree, data);
            }
            auto time2 = steady_clock::now();
            system("cls");
            showTree(tree, 0, false);
            cout << "Время создания " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
            system("pause");
            break;
        }
        case 2: {
            int data;
            system("cls");
            cout << "Введите через пробел числа:\n";
            auto time1 = steady_clock::now();
            do {
                cin >> data;
                insert(tree, data);
            } while (cin.get() != '\n');
            auto time2 = steady_clock::now();
            system("cls");
            showTree(tree, 0, false);
            cout << "Время создания " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
            system("pause");
            break;
        }
        default: {
            cout << "\n*Смэрть*\n";
            return 0;
        }
    }

    Menu: {
        system("cls");
        showTree(tree, 0, false);
        cout << "1. Удаление элемента\n"
            << "2. Вставка элемента\n"
            << "3. Нахождение элемента\n"
            << "4. Проверка на сбалансированность\n"
            << "5. Генерация задания\n"
            << "0. Выход\n";
    }
    cin >> input;
    switch (input) {
        case 1: {
            system("cls");
            showTree(tree, 0, false);
            cout << "Введите значение: ";
            int data;
            cin >> data;
            auto time1 = steady_clock::now();
            deleteEl(tree, data);
            auto time2 = steady_clock::now();
            cout << "Время: " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
            system("pause");
            balancing(tree);
            goto Menu;
        }
        case 2: {
            system("cls");
            showTree(tree, 0, false);
            cout << "Введите значение: ";
            int data;
            cin >> data;
            auto time1 = steady_clock::now();
            insert(tree, data);
            auto time2 = steady_clock::now();
            cout << "Время: " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
            system("pause");
            goto Menu;
        }
        case 3: {
            system("cls");
            showTree(tree, 0, false);
            cout << "Введите искомый элемент: ";
            int data;
            cin >> data;
            auto time1 = steady_clock::now();
            search(tree, data);
            auto time2 = steady_clock::now();
            cout << "Время: " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
            system("pause");
            goto Menu;
        }
        case 4: {
            system("cls");
            auto time1 = steady_clock::now();
            balancing(tree);
            auto time2 = steady_clock::now();
            cout << "Дерево сбалансировано.\n";
            cout << "Время: " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
            system("pause");
            goto Menu;
        }
        case 5: {
            task();
            cout << "Задания сгенерированы и сохранены в вайлах: output_ans.txt; output_ans.key; output_ans.task;\n";
            system("pause");
            goto Menu;
        }
        case 0: {
            cout << "\n*Смэрть*\n";
            return 0;
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