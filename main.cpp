// Author Nikita Batnikov <designAwl@bk.ru>

#include "Library.h"

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("title AWL-S Password manager");

    setlocale(0, "");
    cout << "Менеджер паролей от AWL-S \n";
    Data userData;
    cout << "Адрес сайта: "; cin >> userData.url;
    cout << "Логин: "; cin >> userData.login;
    cout << "Длина пароля: ";  cin >> userData.N;

    srand(time(NULL));
    char* password = new  char[userData.N + 1];

    for (uint32_t i = 0; i < userData.N; ++i) {
        switch (rand() % 3) {
        case 0:
            password[i] = rand() % 32 + '!';
            break;
        case 1:
            password[i] = rand() % 26 + 'A';
            break;
        case 2:
            password[i] = rand() % 26 + 'a';
        }
    }
    password[userData.N] = 0;
    save(userData.N, password, userData.url, userData.login);
    data(password);

    fstream tg("telegram.py", ios::in);

    if (tg.is_open()) {
    cout << "\nОтправить данные в Telegram? \n";
    SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));

    cout << "Отправить [Пробел/Space];\nЗакрыть программу [Левый ALT | Left  ALT];\n";
    SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));

    while (1 != 0)
    {
        if (GetAsyncKeyState(VK_SPACE)) {
            cout << "Идет отправка..\n";
            telegramSend(password, userData.url, userData.login, userData.N);
            break;
        }
        else if (GetAsyncKeyState(VK_LMENU))
        {
            delete[] password;
            exit(0);
        }
    }
}
    delete[] password;
    system("pause");
    return 0;
}