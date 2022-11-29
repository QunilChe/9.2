
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <iomanip>

using namespace std;
enum Kurs { I = 1, II, III, IV, V, VI };
enum Spec { ME, MF, FI, INF, KN };
string specStr[] = { "���������� � ��������", "������� ��������", "������ �� �����������", "�����������", "��������� �����" }; //���� ������ ����� ������

struct Student
{
	string prizv;
	unsigned rikNar;
	unsigned kurs;
	Spec spec;
	union
	{
		int otsinka1;
		int otsinka2;
		int otsinkaPR;
		int otsinkaCM;
		int otsinkaPD;
	};
};
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Kurs kurs, const Spec spec);
void Create(Student* p, const int N);
void Print(Student* p, const int N);
double LineSearch(Student* p, const int N);
double LineSearch1(Student* p, const int N);
double LineSearch2(Student* p, const int N);
double Line(Student* p, const int N);
double Line1(Student* p, const int N);
void Sort(Student* p, const int N);
double Line2(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void SaveToFile(Student* p, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // ������� ������� ���� ������
	fout.write((char*)&N, sizeof(N)); // �������� ������� ��������
	for (int i = 0; i < N; i++)
		fout.write((char*)&p[i], sizeof(Student)); // �������� �������� ������
	fout.close(); // ������� ����
}
int main()
{
	double proc;
	int ispec;
	int ikurs;
	Kurs kurs;
	Spec spec;
	string prizv;
	int found;
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
	int N;
	cout << "������ N: "; cin >> N;
	Student* p = new Student[N];
	double hg = LineSearch(p, N);
	double cg = LineSearch1(p, N);
	double rg = LineSearch2(p, N);
	int gg = (hg + cg + rg);

	double hj = LineSearch(p, N);
	double cj = LineSearch1(p, N);
	double rj = LineSearch2(p, N);
	int gj = (hj + cj + rj);
	Sort(p, N);
	IndexSort(p, N);
	PrintIndexSorted(p, IndexSort(p, N), N);
	cout << "������ ����� ������:" << endl;
	cout << " ������ ( ���������� � ��������, ������� ��������, ������ �� �����������, �����������, ��������� �����): ";
	cin >> ikurs;
	kurs = (Kurs)ikurs;
	cout << "������ �����:" << endl;
	cin >> ispec;
	spec = (Spec)ispec;
	cin.get(); // ������� ����� ��������� � �� ����������� �������
	cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
	cout << " �������: "; getline(cin, prizv);
	cout << endl;
	if ((found = BinSearch(p, N, prizv, kurs, spec)) != -1)
		cout << "�������� �������� � ������� " << found + 1 << endl;
	else
		cout << "�������� �������� �� ��������" << endl;


	char fname[100];
	cout << "������ ��'� �����: "; cin.getline(fname, 99);


	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ��������, �� ������� ��� �����:" << endl;
		cout << " [4] - ������� ��������, � ���� ������� ��� ������ 4" << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << gg;
			break;
		case 4:
			cout << gj
				break;
		case 5:
			cout << "������ ����� ������:" << endl;
			cout << " ������������ (���������� � ��������, ������� ��������, ������ �� �����������, �����������, ��������� �����): ";
			cin >> ispec;
			spec = (Spec)spec;
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
			cout << " �������: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, kurs)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 6:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 7:
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
			cout << "������ ��'� �����: "; cin.getline(fname, 99);
			SaveToFile(p, N, fname);;
			break;

			return 0;

		}
	}
}
void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "stydent No " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " �� ���.: "; cin >> p[i].rikNar;
		cout << " ����.:    "; cin >> p[i].kurs;
		cout << " spec (0 - �������, 1 - �������, 2 - ����������): ";
		cin >> spec;
		p[i].spec = (Spec)spec;

		switch (p[i].spec)
		{
		case KN:
			cout << " otsinka3 : "; cin >> p[i].otsinka1;
			cout << " otsinka3 : "; cin >> p[i].otsinka2;
			cout << " otsinka3 : "; cin >> p[i].otsinkaPR;
			break;
		case INF:
			cout << " otsinka3 : "; cin >> p[i].otsinka1;
			cout << " otsinka3 : "; cin >> p[i].otsinka2;
			cout << " otsinka3 : "; cin >> p[i].otsinkaCM;
			break;
		case ME:
		case MF:
		case FI:
			cout << " otsinka3 : "; cin >> p[i].otsinka1;
			cout << " otsinka3 : "; cin >> p[i].otsinka2;
			cout << " otsinka3 : "; cin >> p[i].otsinkaPD;
			break;
		}
		cout << endl;

	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| No | ������� | г�.���. | kyrs | spec | fizyka | matematika | informatika | ������������� |��������� ������ |��������� | "
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].rikNar << " ";
		cout << "| " << setw(3) << right << p[i].kurs << " ";
		cout << "| " << setw(11) << left << specStr[p[i].spec - 1];
		cout << "| " << setw(3) << right << p[i].otsinka1 << " ";
		cout << "| " << setw(3) << right << p[i].otsinka2 << " ";
		cout << "| " << setw(3) << right << p[i].kurs << " ";

		switch (p[i].spec)
		{
		case KN:
			cout << "| " << p[i].otsinkaPR << " " << endl;
			break;
		case INF:
			cout << "| " << p[i].otsinkaCM << " " << endl;
		case ME:
		case MF:
		case FI:
			cout << "| " << p[i].otsinkaPD << " " << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
double LineSearch(Student* p, const int N)
{
	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].spec == KN)
		{
			n++;
			if (p[i].otsinka1 > 3 and p[i].otsinka2 > 3 and p[i].otsinkaPR > 3)
			{
				k++;
			}
		}
	}
	return k;
}
double LineSearch1(Student* p, const int N)
{
	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].spec == INF)
		{
			n++;
			if (p[i].otsinka1 > 3 and p[i].otsinka2 > 3 and p[i].otsinkaCM > 3)
			{
				k++;
			}
		}
	}
	return k;
}
double LineSearch2(Student* p, const int N)
{
	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].spec == ME, MF, FI)
		{
			n++;
			if (p[i].otsinka1 > 3 and p[i].otsinka2 > 3 and p[i].otsinkaPD > 3)
			{
				k++;
			}
		}
	}
	return k;
}
double Line(Student* p, const int N)
{
	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].spec == KN)
		{
			n++;
			if (((p[i].otsinka1 + p[i].otsinka2 > 3 + p[i].otsinkaPR > 3) / 3) < 4)
			{
				k++;
			}
		}
	}
	return 100.0 * k / n;
}
double Line1(Student* p, const int N)
{
	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].spec == INF)
		{
			n++;
			if (((p[i].otsinka1 + p[i].otsinka2 > 3 + p[i].otsinkaCM > 3) / 3) < 4)
			{
				k++;
			}
		}
	}
	return 100.0 * k / n;
}
double Line2(Student* p, const int N)
{
	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].spec == ME, MF, FI)
		{
			n++;
			if (((p[i].otsinka1 + p[i].otsinka2 > 3 + p[i].otsinkaPD > 3) / 3) < 4)
			{
				k++;
			}
		}
	}
	return 100.0 * k / n;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].kurs > p[i1 + 1].kurs)
				||
				(p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].spec > p[i1 + 1].spec)
				||
				(p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].spec == p[i1 + 1].spec &&
					p[i1].prizv < p[i1 + 1].prizv ))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int* IndexSort(Student* p, const int N)
{ // ������������� ����� ������� ��� ���������� ���������� ������
//
// int i, j, value;
// for (i = 1; i < length; i++) {
// value = a[i];
// for (j = i - 1; j >= 0 && a[j] > value; j--) {
// a[j + 1] = a[j];
// }
// a[j + 1] = value;
// }
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && (p[I[j]].kurs > p[value].kurs)
			||
			(p[I[j]].kurs == p[value].kurs &&
				p[I[j]].spec > p[value].spec)
			||
			(p[I[j]].kurs == p[value].kurs &&
				p[I[j]].spec == p[value].spec &&
				p[I[j]].prizv < p[value].prizv);
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
	cout << "========================================================================="
		<< endl;
	cout << "| No | ������� | г�.���. | kyrs | spec | fizyka | matematika | informatika | ������������� |��������� ������ |��������� | "
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].rikNar << " ";
		cout << "| " << setw(3) << right << p[I[i]].kurs << " ";
		cout << "| " << setw(11) << left << specStr[p[I[i]].spec - 1];
		cout << "| " << setw(3) << right << p[I[i]].otsinka1 << " ";
		cout << "| " << setw(3) << right << p[I[i]].otsinka2 << " ";
		cout << "| " << setw(3) << right << p[I[i]].kurs << " ";

		switch (p[I[i]].spec)
		{
		case KN:
			cout << "| " << p[i].otsinkaPR << " " << endl;
			break;
		case INF:
			cout << "| " << p[i].otsinkaCM << " " << endl;
		case ME:
		case MF:
		case FI:
			cout << "| " << p[i].otsinkaPD << " " << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
int BinSearch(Student* p, const int N, const string prizv, const Kurs kurs, const Spec spec)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].kurs == kurs && p[m].spec == spec)
			return m;
		if ((p[m].kurs < kurs)
			||
			(p[m].kurs == kurs &&
				p[m].prizv < prizv)
				||
				(p[m].kurs == kurs &&
					p[m].prizv < prizv &&
					p[m].spec < spec))
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