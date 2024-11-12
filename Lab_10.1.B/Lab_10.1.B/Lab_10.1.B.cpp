#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "�����������", "��������������", "����'����� �����", "����'������ ��������", "��������� ������������" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    union {
        int grade_programming;     // ������ �� ������������� (��� ����'������� ����)
        int grade_numerical;       // ������ �� ��������� ������� (��� �����������)
        int grade_pedagogy;        // ������ �� ��������� (��� ������ ��������������)
    };
};

void Create(Students* S, const int N);
void Print(Students* S, const int N);
string FindBestStudent(Students* S, const int N);
double PercentageExcellents(Students* S, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� ��������: "; cin >> N;

    Students* S = new Students[N];

    Create(S, N);
    Print(S, N);

    // ���������� � ����� �������� � ���������� ������� ������
    string best_student = FindBestStudent(S, N);
    cout << "������� � ��������� ������� �����: " << best_student << endl;

    // ���������� �������� ����������
    cout << "������� ��������, �� ������� �� '������': " << fixed << setprecision(2) << PercentageExcellents(S, N) << "%" << endl;

    delete[] S;
    return 0;
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "����� ��������: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "�������: "; getline(cin, S[i].surname);
        cout << "����: "; cin >> S[i].course;
        cout << "������������ (0 - �����������, 1 - ��������������, 2 - ����'����� �����,";
        cout << "\n3 - ����'������ ��������, 4 - ��������� ������������): ";
        cin >> speciality;
        S[i].speciality = (Speciality)speciality;
        cout << "������ � ������: "; cin >> S[i].grade_physics;
        cout << "������ � ����������: "; cin >> S[i].grade_math;

        if (S[i].speciality == KN) {
            cout << "������ � �������������: "; cin >> S[i].grade_programming;
        }
        else if (S[i].speciality == ITIS) {
            cout << "������ � ��������� ������: "; cin >> S[i].grade_numerical;
        }
        else {
            cout << "������ � ���������: "; cin >> S[i].grade_pedagogy;
        }
        cout << endl;
    }
}

void Print(Students* S, const int N)
{
    cout << "=================================================================================================================================" << endl;
    cout << "|  �  |   �������   |  ����  |     ������������     |  Գ����  |  ����������  | ������������� |  ������� ������ | ��������� |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].course;
        cout << "|" << setw(23) << left << speciality_str[S[i].speciality];
        cout << "|" << setw(10) << left << S[i].grade_physics;
        cout << "|" << setw(14) << left << S[i].grade_math;

        if (S[i].speciality == KN) {
            cout << "|" << setw(15) << left << S[i].grade_programming << "|";
            cout << setw(18) << left << " " << "|" << setw(12) << left << " " << "|" << endl;
        }
        else if (S[i].speciality == ITIS) {
            cout << "|" << setw(15) << left << " " << "|";
            cout << setw(18) << left << S[i].grade_numerical << "|" << setw(12) << left << " " << "|" << endl;
        }
        else {
            cout << "|" << setw(15) << left << " " << "|";
            cout << setw(18) << left << " " << "|" << setw(12) << left << S[i].grade_pedagogy << "|" << endl;
        }
    }
    cout << "=================================================================================================================================" << endl << endl;
}

string FindBestStudent(Students* S, const int N)
{
    int best_index = 0;
    double highest_avg = (S[0].grade_physics + S[0].grade_math +
        ((S[0].speciality == KN) ? S[0].grade_programming :
            (S[0].speciality == ITIS) ? S[0].grade_numerical :
            S[0].grade_pedagogy)) / 3.0;

    for (int i = 1; i < N; i++) {
        double avg = (S[i].grade_physics + S[i].grade_math +
            ((S[i].speciality == KN) ? S[i].grade_programming :
                (S[i].speciality == ITIS) ? S[i].grade_numerical :
                S[i].grade_pedagogy)) / 3.0;
        if (avg > highest_avg) {
            highest_avg = avg;
            best_index = i;
        }
    }
    return S[best_index].surname;
}

double PercentageExcellents(Students* S, const int N)
{
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (S[i].grade_physics == 5 && S[i].grade_math == 5 &&
            ((S[i].speciality == KN && S[i].grade_programming == 5) ||
                (S[i].speciality == ITIS && S[i].grade_numerical == 5) ||
                (S[i].speciality != KN && S[i].speciality != ITIS && S[i].grade_pedagogy == 5))) {
            count++;
        }
    }
    return count * 100.0 / N;
}
