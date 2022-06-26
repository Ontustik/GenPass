// Author Nikita Batnikov <designAwl@bk.ru>

#include "Library.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void save(uint32_t N, char* password, string url, string login) {
    system("title AWL-S ������ ������ � ����");

    boost::posix_time::ptime localTIME = boost::posix_time::second_clock::local_time();

    ofstream save(Path, ios::app);
    if (save.is_open()) {
        save << "\n";
        save << localTIME;
        save << "\nWebsite URL: " << url;
        save << "\nLogin: " << login;
        save << "\nPassword: " << password << "\n";
        save << login << ":" << password << "\n";
    }
    save.close();

    if (N <= limit) {
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
        cout << "\n" << password << "\n\n";
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
    }
    else
        cout << "������ ����� �������: ������ ����� ��������� � ����. " << Path << "\n";
};

void data(char* password) {
    int pass_length = strlen(password), point_upper = 0, point_lower = 0, point_digit = 0, point_symbol = 0, point = 0;

    for (int i = 0; i < pass_length; i++) {
        if (password[i] >= 48 && password[i] <= 57)
            point_digit++;
        else if (password[i] >= 97 && password[i] <= 125)
            point_lower++;
        else if (password[i] >= 65 && password[i] <= 90)
            point_upper++;
        else
            point_symbol++;
    }

    if (point_digit > 0)
        point += 50;
    if (point_lower > 0)
        point += 50;
    if (point_upper > 0)
        point += 50;
    if (point_symbol > 0)
        point += 50;

    cout << "���������������  ������ ������: ";
    if (point_digit > 0 && point_lower > 0 && point_upper > 0 &&
        point_symbol > 0)
        point += 100;

    if (point <= 50 || pass_length < 8) {
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
        cout << "~ ������ ������\n";
    }
    else if (point > 50 && point <= 100) {
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
        cout << "~ �� �����\n";
    }
    else if (point >= 150 && point <= 200) {
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
        cout << "~ �������\n";
    }
    else if (point > 200) {
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
        cout << "~ �� � �������������\n";
    }
    SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
}

void telegramSend(char* password, string url, string login, uint16_t N) {
    boost::posix_time::ptime localTIME = boost::posix_time::second_clock::local_time();
    system("title AWL-S �������� � Telegram..");


    ofstream save(PathTemp, ios::out);
    if (save.is_open()) {
        save << "���������� � ������� AWL-S GenPass\n";
        save << localTIME;
        save << "\nWebsite URL: " << url;
        save << "\nLogin: " << login;
        save << "\nPassword: " << password;
    } save.close();

    system("python telegram.py");
    system("cls");
    if (N <= limit) {
        cout << "������ ���������! ��� ������������ ��������� ���.\n";
        cout << "��� ������:\n\n";
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
        cout << password << "\n\n";
    }
    else
    {
        system("color 4");
        cout << "\n������ ���������! ��� ������������ ��������� ���.\n";
        cout << "������ ����� �������: ������ ����� ��������� � ����.\n";
        cout << "������ ����� ����� ����� �� �����������!!!\n\n";
    }
    SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
    remove(PathTemp);
}