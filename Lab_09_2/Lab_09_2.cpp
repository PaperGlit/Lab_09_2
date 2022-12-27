#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Spec { CS, IT, ME, PI, TN };
string specStr[] = { "Комп. науки", "Інформатика", "Матем. та екон.", "Фіз. та інф.", "Трудве навч." };
struct Student
{
	string prizv;
	int course;
	Spec spec;
	int phys;
	int matem;
	union
	{
		int program;
		int chys_met;
		int pedag;
	};
};

void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " Прізвище : "; getline(cin, p[i].prizv);
		cout << " Курс : "; cin >> p[i].course;
		cout << " Спеціальність (0 - Комп. науки, 1 - Інформатика, 2 - Матем. та екон., 3 - Фіз. та інф., 4 - Трудве навч.) : ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		cout << " Оцінка з фізики : "; cin >> p[i].phys;
		cout << " Оцінка з математики : "; cin >> p[i].matem;
		switch (p[i].spec)
		{
		case CS:
			cout << " Оцінка з програмування : "; cin >> p[i].program;
			break;
		case IT:
			cout << " Оцінка з чисельних методів : "; cin >> p[i].chys_met;
			break;
		case ME:
		case PI:
		case TN:
			cout << " Оцінка з педагогіки : "; cin >> p[i].pedag;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "=============================================================================================================="
		<< endl;
	cout << "| № |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Програмування | Чис. методи | Педагогіка |"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].course << " "
			<< "| " << setw(16) << left << specStr[p[i].spec]
			<< "| " << setw(6) << right << p[i].phys << " "
			<< "| " << setw(10) << right << p[i].matem << " ";
		switch (p[i].spec)
		{
		case CS:
			cout << "| " << setw(13) << right << p[i].program << " | " << setw(14) << right << "| " << setw(12) << right << " |" << endl;
			break;
		case IT:
			cout << "| " << setw(16) << right << "| " << setw(11) << right << p[i].chys_met << " | " << setw(12) << right << " |" << endl;
			break;
		case ME:
		case PI:
		case TN:
			cout << "| " << setw(16) << right << "| " << setw(14) << right << "| " << setw(10) << right << p[i].pedag << " |" << endl;
			break;
		}
	}
	cout << "=============================================================================================================="
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].phys > p[i1 + 1].phys)
				||
				(p[i1].phys == p[i1 + 1].phys && p[i1].spec > p[i1 + 1].spec)
				||
				(p[i1].phys == p[i1 + 1].phys && p[i1].spec == p[i1 + 1].spec && p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N];
	for (int i = 0; i < N; i++)
		I[i] = i; 
	int i, j, value;
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].phys > p[value].phys)
				||
				(p[I[j]].phys == p[value].phys && p[I[j]].spec > p[value].spec)
				||
				(p[I[j]].phys == p[value].phys && p[I[j]].spec == p[value].spec && p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "=============================================================================================================="
		<< endl;
	cout << "| № |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Програмування | Чис. методи | Педагогіка |"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].course << " "
			<< "| " << setw(16) << left << specStr[p[I[i]].spec]
			<< "| " << setw(6) << right << p[I[i]].phys << " "
			<< "| " << setw(10) << right << p[I[i]].matem << " ";
		switch (p[I[i]].spec)
		{
		case CS:
			cout << "| " << setw(13) << right << p[I[i]].program << " | " << setw(14) << right << "| " << setw(12) << right << " |" << endl;
			break;
		case IT:
			cout << "| " << setw(16) << right << "| " << setw(11) << right << p[I[i]].chys_met << " | " << setw(12) << right << " |" << endl;
			break;
		case ME:
		case PI:
		case TN:
			cout << "| " << setw(16) << right << "| " << setw(14) << right << "| " << setw(10) << right << p[I[i]].pedag << " |" << endl;
			break;
		}
	}
	cout << "=============================================================================================================="
		<< endl;
	cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const int phys)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].spec == spec && p[m].phys == phys)
			return m;
		if ((p[m].phys < phys)
			||
			(p[m].phys == phys && p[m].spec < spec)
			||
			(p[m].phys == phys && p[m].spec == spec && p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N, phys, ispec, found;
	int* I;
	string prizv;
	Spec spec;
	cout << "Введіть кількість студентів N : "; cin >> N;
	Student* p = new Student[N];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію : " << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід фізично відсортованих даних на екран" << endl;
		cout << " [4] - вивід індексно відсортованих даних на екран"  << endl;
		cout << " [5] - Бінарний пошук студента за прізвищем, спеціальністю та оцінкою з фізики" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення : "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			Print(p, N);
			break;
		case 4:
			I = IndexSort(p, N);
			PrintIndexSorted(p, I, N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " Прізвище : "; getline(cin, prizv);
			cout << " Спеціальність (0 - Комп. науки, 1 - Інформатика, 2 - Матем. та екон., 3 - Фіз. та інф., 4 - Трудве навч.) : ";
			cin >> ispec;
			spec = (Spec)ispec;
			cin.get();
			cin.sync();
			cout << " Оцінка з фізики : "; cin >> phys;
			cout << endl;
			if ((found = BinSearch(p, N, prizv, spec, phys)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}