#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

struct List {
	List* prev;
	List* next;
	int data;
	int index;
};

List* CreateListA(int N) {
	List* curr = 0,
		* next = 0;
	for (int i = 1; i <= N; ++i) {
		curr = new List;
		curr->index = i;
		curr->next = next;
		if (next)
			next->prev = curr;
		next = curr;
	}
	curr->prev = 0;
	return curr;
}

List* CreateListB(int& N) {
	List* curr = 0,
		* next = 0;
	int input = 1, i = 1;
	while (input) {
		cin >> input;
		if (input == 0)
			break;
		curr = new List;
		curr->index = i;
		curr->data = input;
		curr->next = next;
		if (next)
			next->prev = curr;
		next = curr;
		i++;
	}
	N = i - 1;
	curr->prev = 0;
	return curr;
}

void FillRandom(List* curr) {
	srand(time(0));
	while (curr) {
		curr->data = rand() % 100;
		curr = curr->next;
	}
}

void ShowList(List* curr, int N) {
	while (curr) {
		cout << curr->index << ") " << curr->data << "  ";
		curr = curr->prev;
	}
}

void FindStart(List* curr, List*& start) {
	while (curr) {
		if (curr->next == 0)
			start = curr;
		curr = curr->next;
	}
}

void FindEnd(List* start, List*& curr) {
	while (start) {
		if (start->prev == 0)
			curr = start;
		start = start->prev;
	}
}

List* AddLast(List* curr, int& N, int number, int index) {
	List* New = new List;
	New->data = number;
	New->index = index + 1;
	New->prev = 0;
	New->next = curr;
	curr->prev = New;
	N++;
	return New;
}

List* AddFirst(List* curr, int& N, int number, int index) {
	List* New = new List;
	New->data = number;
	New->index = index + 1;
	New->next = 0;
	New->prev = curr;
	curr->next = New;
	while (curr) {
		curr->index += 1;
		curr = curr->prev;
	}
	N++;
	return New;
}

List* AddMid(List* curr, int& N, int number, int index) {
	List* New = new List;
	New->index = index + 1;
	New->data = number;
	while (index != curr->index) {
		curr = curr->next;
	}

	New->next = curr;
	curr = curr->prev;
	curr->next = New;
	New->prev = curr;
	curr = curr->next;
	curr = curr->next;
	curr->prev = New;

	curr = curr->prev;
	curr = curr->prev;
	while (curr) {
		curr->index += 1;
		curr = curr->prev;
	}

	N++;
	return New;
}

void Switch(List*& curr, int index1, int index2) {
	List* curr1 = 0, * curr2 = 0;
	while (curr) {
		if (curr->index == index1)
			curr1 = curr;
		if (curr->index == index2)
			curr2 = curr;
		curr = curr->next;
	}
	swap(curr1->data, curr2->data);
}

void Get(List* curr) {
	int input;
	bool check = 0;
	GMenu: {
		cout << "\n1) Получение по индексу.\n"
			<< "2) Получение по значению.\n";
	}
	cin >> input;
	switch (input) {
		case 1: {
			int index;
			cout << "Введите значение индекса: ";
			cin >> index;
			auto time1 = steady_clock::now();
			while (curr) {
				if (curr->index == index) {
					cout << curr->index << ") " << curr->data << "\n";
					check = 1;
				}
				curr = curr->next;
			}
			auto time2 = steady_clock::now();
			cout << "\nВремя получения " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
			system("pause");
			break;
		}
		case 2: {
			int number;
			cout << "Введите значение: ";
			cin >> number;
			auto time1 = steady_clock::now();
			while (curr) {
				if (curr->data == number) {
					cout << curr->index << ") " << curr->data << "\n";
					check = 1;
				}
				curr = curr->next;
			}
			auto time2 = steady_clock::now();
			cout << "\nВремя получения " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
			system("pause");
			break;
		}
		default: {
			cout << "\nНеверный ввод.\n";
			cin.clear();
			while (cin.get() != '\n');
			system("pause");
			goto GMenu;
		}
	}
}

void DeleteIndex(List*& curr, int& N, int index) {
	List* A = 0;
	if (index == 1) {
		A = curr->prev;
		delete curr;
		curr = A;
		curr->next = 0;
		while (curr) {
			curr->index -= 1;
			curr = curr->prev;
		}
	}
	else if (index == N) {
		A = curr->next;
		delete curr;
		curr = A;
		curr->prev = 0;
	}
	else if ((1 < index) && (index < N)) {
		while (curr->index != index) {
			curr = curr->next;
		}
		A = curr->prev;
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
		delete curr;
		curr = A;
		while (curr) {
			curr->index -= 1;
			curr = curr->prev;
		}
	}
	else {
		cout << "\nНеверный ввод.\n";
		cin.clear();
		while (cin.get() != '\n');
		system("pause");
		return;
	}
	N--;
}

void DeleteData(List*& curr, List*& start, int& N, int number) {
	List* A = 0;
	while (curr) {
		if (curr->data == number) {
			if (curr->index == N) {
				A = curr->next;
				delete curr;
				curr = A;
				curr->prev = 0;
			}
			else if (curr->index == 1) {
				A = curr->prev;
				delete curr;
				curr = A;
				curr->next = 0;
				start = curr;
			}
			else {
				A = curr->prev;
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				delete curr;
				curr = A;
			}
			N--;
		}
		if (curr->next == 0) {
			break;
		}
		curr = curr->next;
	}
	int i = 0;
	while (start) {
		i++;
		start->index = i;
		start = start->prev;
	}
}

int main() {
	setlocale(0, "");
	int input, N;
	List* end = 0, * start = 0;

	Menu1: {
		system("cls");
		cout << "Как хотите создать список?\n"
			<< "1. Автоматически.\n"
			<< "2. В ручную.\n"
			<< "3. Выход.\n";
	}
	cin >> input;
	switch (input) {
		case 1: {
			system("cls");
			cout << "Введите размер списка: ";
			cin >> N;
			auto time1 = steady_clock::now();
			end = CreateListA(N);
			FillRandom(end);
			auto time2 = steady_clock::now();
			cout << "Время создания " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
			system("pause");
			FindStart(end, start);
			break;
		}
		case 2: {
			system("cls");
			cout << "Для выхода введите 0 (нуль)\n";
			cout << "Введите числа (после каждого нового числа жмите 'Enter'):\n";
			auto time1 = steady_clock::now();
			end = CreateListB(N);
			auto time2 = steady_clock::now();
			cout << "Время создания " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
			system("pause");
			FindStart(end, start);
			break;
		}
		case 3: {
			cout << "\n*Смэрть*\n";
			return 0;
		}
		default: {
			cout << "\nНеверный ввод.\n";
			cin.clear();
			while (cin.get() != '\n');
			system("pause");
			goto Menu1;
		}
	}

	Menu2: {
		system("cls");
		ShowList(start, N);
		cout << "\nЧто желаете сделать?\n"
			<< "1. Вставить элемент в список.\n"
			<< "2. Удалить элемент из списка.\n"
			<< "3. Поменять элементы списка местами.\n"
			<< "4. Получить элемент списка.\n"
			<< "5. Выход.\n";
	}
	cin >> input;
	switch (input) {
		case 1: {
			system("cls");
			ShowList(start, N);
			int number, index;

			cout << "\nВведите число: ";
			cin >> number;
			cout << "После какого элемента вставить число?: ";
			cin >> index;

			auto time1 = steady_clock::now();
			if (index == 0) {
				start = AddFirst(start, N, number, index);
			}
			else if (index == N) {
				end = AddLast(end, N, number, index);
			}
			else if ((0 < index) && (index < N)) {
				end = AddMid(end, N, number, index);
				FindEnd(start, end);
			}
			else {
				cout << "\nНеверный ввод.\n";
				cin.clear();
				while (cin.get() != '\n');
				system("pause");
				goto Menu2;
			}
			auto time2 = steady_clock::now();
			cout << "Время вставки " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
			system("pause");
			goto Menu2;
		}
		case 2: {
			system("cls");
			int i;
			cout << "1. Удаление по индексу.\n"
				<< "2. Удаление по значению.\n";
			cin >> i;
			if (i == 1) {
				system("cls");
				ShowList(start, N);
				int index;
				cout << "\nВведите индекс: ";
				cin >> index;
				auto time1 = steady_clock::now();
				if (index == 1) {
					DeleteIndex(start, N, index);
					FindStart(end, start);
				}
				else {
					DeleteIndex(end, N, index);
					FindEnd(start, end);
				}
				auto time2 = steady_clock::now();
				cout << "Время удаления " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
				system("pause");
			}
			else if (i == 2) {
				system("cls");
				ShowList(start, N);
				int number;
				cout << "\n*Учтите, что будут удалены все элементы с одинаковым значением*\n"
					<< "Введите значение: ";
				cin >> number;
				auto time1 = steady_clock::now();
				DeleteData(end, start, N, number);
				auto time2 = steady_clock::now();
				cout << "Время удаления " << duration_cast<nanoseconds>(time2 - time1).count() << " наносекунд\n";
				system("pause");
				FindStart(end, start);
				FindEnd(start, end);
			}
			else {
				cout << "\nНеверный ввод.\n";
				cin.clear();
				while (cin.get() != '\n');
				system("pause");
			}

			goto Menu2;
		}
		case 3: {
			system("cls");
			ShowList(start, N);
			int index1, index2;
			cout << "\nВведите индекс 1-ого элемента: ";
			cin >> index1;
			if (((0 < index1) && (index1 <= N)) == 0) {
				cout << "\nНеверный ввод.\n";
				cin.clear();
				while (cin.get() != '\n');
				system("pause");
				goto Menu2;
			}
			cout << "Введите индекс 2-ого элемента: ";
			cin >> index2;
			if (((0 < index2) && (index2 <= N)) == 0) {
				cout << "\nНеверный ввод.\n";
				cin.clear();
				while (cin.get() != '\n');
				system("pause");
				goto Menu2;
			}
			Switch(end, index1, index2);
			FindEnd(start, end);
			goto Menu2;
		}
		case 4: {
			system("cls");
			ShowList(start, N);
			Get(end);

			goto Menu2;
		}
		case 5: {
			cout << "\n*Смэрть*\n";
			return 0;
		}
		default: {
			cout << "\nНеверный ввод.\n";
			cin.clear();
			while (cin.get() != '\n');
			system("pause");
			goto Menu2;
		}
	}
}