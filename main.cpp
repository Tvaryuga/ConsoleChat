// ConsoleChat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// Выделять память под 10 юзеров потом увеличивать?!
// Разделить вход и регистрацию на отдельные функции
#include <iostream>
#include "User.h"
#include <string>

using std::cout;
using std::cin;
using std::endl;

void inputMenu();                                                                                   // меню входа и регистрации
void mainMenu(User&);                                                                               // меню Аккаунта для переданного в параметре пользователя
template <typename T>
void checkInput(T&);                                                                                // Шаблонная функция проверки ввода
void changeAccount(User*&, const int);                                                              // функция изменения меню для изменения данных аккаунта
bool yesOrNot();                                                                                    // функция выбора да/нет
void registration(User*&);                                                                          // функция регистрации пользвователя
int signingIn(User*);                                                                               // функция входа в аккаунт
int main()
{
    User* users = nullptr;                                                                          // Указатель на пользвователей чата
    int choice(-1), i = 0;                                                                          // выбор
    while (choice != 0)
    {
        system("cls");
        inputMenu();                                                                                
        while (choice < 0 || choice > 2)
            checkInput(choice);
        if (choice == 1)
        {
            if (users == nullptr)                                                                   //Если нет ни одного зарегестрированного пользователя
            {
                cout << "\nYou haven't signed up yet! \nDo you want to sign up now? (y or n): ";    // Предложение зарегестрироваться
                if (yesOrNot())
                    choice = 2;
                else
                {
                    choice = -1;
                    continue;
                }
            }
            else
            {
                i = signingIn(users);                                                               // функция signinIn вернёт индекс пользователь если вход успешен или -1 если нет
                if (i >= 0)                                                                         // вход успешно выполнен
                {
                    while (true)
                    {
                        mainMenu(users[i]);                                                         // главное меню пользователя
                        int action(-1);                                                             // переменная отвечающая за действия пользователя
                        while (action < 1 || action > 4)
                            checkInput(action);
                        if (4 == action)                                                            // Если 4, то выходим
                            break;
                        switch (action)
                        {
                        case 1: changeAccount(users, i); break;                                     // Редактируем данные своего аккаунта
                        case 2:                                                                     // Переходим в раздел "Dialogs"
                            while (true)
                            {
                                cin.get();
                                std::string name;
                                system("cls");
                                cout << "Enter the name to choose dialog.\n";
                                cout << "\"all\" to enter the general chat.\n";
                                cout << "\"q\" to quit\n\nChats:\n";
                                users[i].showDialogs();                                             // Показываем наши диалоги 
                                cout << "> ";
                                getline(cin, name);
                                if (name == "all")
                                {
                                    while (true)
                                    {
                                        action = -1;
                                        system("cls");
                                        users[i].showMessages();                                    // Показать историю сообщений в общем чате у текущего пользователя
                                        cout << "\n1. Send\t\t 2. Back ";                           // Отправить сообщение в общем чате или вернуться назад
                                        while (action < 1 || action > 2)
                                            checkInput(action);
                                        if (action == 1)                                            // Отправить сообщение
                                        {
                                            std::cout << "Input > ";
                                            std::string text;
                                            std::cin.get();
                                            getline(std::cin, text);
                                            users[i].sendMessageTo(users, text, 1);                 // Отправляем сообщение всем в общий чат
                                            continue;                                               // продолжаем выполнение цикла
                                        }
                                        else
                                            break;
                                    }
                                }
                                else if (name == "q")                                                 // Выходим
                                    break;
                                else
                                {
                                    int j(0);
                                    for (; j < users->getCountUsers(); j++)
                                    {
                                        if (name == users[j].getName())
                                        {
                                            while (true)
                                            {
                                                int action2(0);
                                                system("cls");
                                                users[i].showMessages(name);                          // Показать историю сообщений в нашем диалоге
                                                cout << "\n1. Send\t\t 2. Back ";                     // Отправить сообщение или вернуться назад
                                                while (action2 < 1 || action2 > 2)
                                                    checkInput(action2);
                                                if (action2 == 1)                                     // Если кнопка Send
                                                {
                                                    std::cout << "Input > ";
                                                    std::string text;
                                                    std::cin.get();
                                                    getline(std::cin, text);
                                                    users[i].sendMessageTo(&users[j], text);          // отправляем сообщение выбранному пользователю
                                                    continue;
                                                }
                                                else if (action2 == 2)                                // Иначе кнопка back 
                                                    break;
                                            }
                                        }
                                    }
                                    if (j == users->getCountUsers())
                                    {
                                        cout << "\nCommand \"" << name << "\" not found! Push any bottom to continue..." << endl;

                                        continue;
                                    }
                                }
                            } break;
                        case 3:                                                                       // отправить новое сообщение(суть в том, что можно отправить сообщение пользователю, с которым пока нет диалога)
                        {
                            system("cls");
                            cout << "Select user.\n\n";
                            action = -1;
                            for (int j(0); j < users[i].getCountUsers(); j++)                         // Выводим всех зарегестрированных юзеров
                            {
                                cout << j << ". ";
                                if (users[j].getName() != users[i].getName())
                                    cout << users[j].getName() << endl;
                                else
                                    cout << " Myself" << endl;
                            }
                            cout << users->getCountUsers() << ". Back\n";                             // последний номер - кнопка назад
                            while (action < 0 || action >(users[i].getCountUsers()))                  // выбираем юзера
                                checkInput(action);
                            if (action == (users[i].getCountUsers()))                                 // если выбор равен кол-ву юзеров, то выбирается кнопка назад
                                break;
                            else
                            {
                                system("cls");
                                std::string text;
                                std::cout << "Recipient: " << users[action].getName() << endl;
                                cout << "\n> ";
                                std::cin.get();
                                getline(std::cin, text);
                                users[i].sendMessageTo(&users[action], text);                         // отправляем сообщение выбранному пользователю
                            }
                            cout << "Success!\n";
                            cin.get();
                            cin.get();
                        } break;
                        }
                    }
                    choice = -1;
                }
                else
                    choice = -1;
            }
        }
        if (choice == 2)                                                                            // Регистрация в чате
        {
            registration(users);                                                                    // Функция регистрирующая пользователя
            choice = -1;                                                                            // обновляем переменную выбора в значение -1
        }
    }
    delete[] users;                                                                                 // Удаляем всех пользователей
    cin.get();
    return 0;
}
void inputMenu()
{
    cout.width(19);
    cout << "1. Sign in\n";
    cout.width(18);
    cout << "or\n";
    cout.width(20);
    cout << "2. Sign up\n\n";
    cout.width(22);
    cout << "Choose 1 or 2\n\n";
}
void mainMenu(User& user)
{
    system("cls");
    cout << "***\t" << user.getName() << "\t***" << endl;
    cout << "\n1. My account\n";
    cout << "2. Dialogs\n";
    cout << "3. Send message to user\n";
    cout << "4. Sign out\n\n ";
}
template <typename T>
void checkInput(T& temp)
{
    cout << "> ";
    while (!(cin >> temp))
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
        cout << "Command not found!\n> ";
    }

}
void changeAccount(User*& user, const int i)
{
    while (true)
    {
        system("cls");
        unsigned int countUsers = user->getCountUsers();
        int yourchoice = -1;
        cout << "***\tMy profile\t***\n\n";
        cout << "Name: " << user[i].getName() << endl;
        cout << "Login: " << user[i].getLogin() << endl;
        cout << "Password: " << user[i].getPassword() << endl;
        cout << "1. Change Name\n";
        cout << "2. Change Login\n";
        cout << "3. Change Password\n";
        cout << "4. Back\n";
        while (yourchoice < 0 || yourchoice > 4)
            checkInput(yourchoice);
        if (yourchoice == 4)
            break;
        system("cls");
        std::string temp;
        int j(0);
        switch (yourchoice)
        {                                                                                                      // Меняем данные юзера если новые данные ещё никем не заняты
        case 1:
            cout << "New name: ";
            cin >> temp;
            for (; j < countUsers; j++)
                if (i == j)
                    continue;
                else if (user[j].getName() == temp)
                {
                    cout << "Name \"" << temp << "\" is already taken";
                    cin.get();
                    break;
                }
            if (j == countUsers)
            {
                user[i].setName(temp);
                cout << "Your name was changed!\n";
                cin.get(); 
                break;
            } 
            break;
        case 2:
            cout << "New login: ";
            cin >> temp;
            for (; j < countUsers; j++)
                if (i == j)
                    continue;
                else if (user[j].getLogin() == temp)
                {
                    cout << "Login \"" << temp << "\" is already taken";
                    cin.get();
                    break;
                }
            if (j == countUsers)
            {
                user[i].setLogin(temp);
                cout << "Your login was changed!\n";
                cin.get(); 
                break;
            }
            break;
        case 3:
            cout << "New password: ";
            cin >> temp;
            for (; j < countUsers; j++)
                if (i == j)
                    continue;
                else if (user[j].getPassword() == temp)
                {
                    cout << "Password \"" << temp << "\" is already taken";
                    cin.get();
                    break;
                }
            if (j == countUsers)
            {
               user[i].setPassword(temp);
               cout << "Your password was changed!\n"; 
               cin.get(); 
               break;
            }
            break;
        }
        cin.get();
    }
}
bool yesOrNot()
{
    char ch = '\0';
    while (tolower(ch) != 'y' && tolower(ch) != 'n')
        checkInput(ch);
    if (ch == 'y')
        return true;
    else
        return false;
}
void registration(User*& user)
{
    bool correctSignUp = true;
    std::string name;
    std::string login;
    std::string password;
    do
    {
        system("cls");
        cout << "Registration\n\n";
        cout << "Your name: ";
        cin >> name;
        cout << "Create your Login(email or phone number): ";
        cin >> login;
        cout << "Create your Password: ";
        cin >> password;
        for (int j(0); j < user->getCountUsers(); j++)                                              // Проверка введённых данных на соответствие уже существующим
        {
            if (name == user[j].getName())                                                          // Если совпало имя, то
            {
                cout << "Name " << name << " is already taken!\n";
                cout << "Try again? (y or n): ";                                                    // предложение попробовать снова
                if (yesOrNot())
                {
                    correctSignUp = false; break;                                                   // если да, то пробуем регистрацию снова
                }
                else
                    return;                                                                         // иначе возвращаемся из функции
            }
            else
                correctSignUp = true;
            if (login == user[j].getLogin())                                                        // Если совпал логин
            {
                cout << "Login " << login << " is already taken!\n";
                cout << "Try again? (y or n): ";                                                    // предложение попробовать снова
                if (yesOrNot())
                {
                    correctSignUp = false; break;                                                   // если да, то пробуем регистрацию снова
                }
                else
                    return;                                                                         // иначе возвращаемся из функции
            }
            else
                correctSignUp = true;
            if (password == user[j].getPassword())                                                  
            {
                cout << "Password " << password << " is already taken!\n";
                cout << "Try again? (y or n): ";
                if (yesOrNot())
                {
                    correctSignUp = false; break;
                }
                else
                    return;
            }
            else
                correctSignUp = true;
        }
    } while (!correctSignUp);                                                                       // Если нет совпадений, то продолжаем регистрацию
    if (user == nullptr)
    {
        user = new User[1];                                                                         // Выделяем память для первого пользователя
        user[0].setName(name);
        user[0].setLogin(login);
        user[0].setPassword(password);
    }
    else
    {
        User* oldUsers = user;
        int countUsers = user->getCountUsers();
        try
        {
            user = new User[countUsers + 1];                                                        // Выделяем память с учётом добавления нового пользователя
        }
        catch (std::bad_alloc& ba)
        {
            cout << "bad_alloc caught!" << endl;
            cout << ba.what() << endl;
        }
        for (int i(0); i < countUsers; i++)
            user[i] = oldUsers[i];                                                                  // перезаписываем старых пользователей в новую, только что выделенную, память 
        delete[] oldUsers;
        user[countUsers].setName(name);
        user[countUsers].setLogin(login);
        user[countUsers].setPassword(password);
    }
    cout << "Registration completed!\n";
    cin.get();
    cin.get();
}
int signingIn(User* user)                                                                           // Функция входа в аккаунт
{
    std::string login;
    std::string password;
    while (true)
    {
        system("cls");
        cout << "Login(email or phone number): ";
        cin >> login;
        cout << "Password: ";
        cin >> password;
        for (int i(0); i < user->getCountUsers(); i++)
            if (user[i].getLogin() == login)
                if (user[i].getPassword() == password)                                              // Если логин и пароль совпадают с уже зарегестрированными, 
                {   
                    return i;                                                                       // то возвращаем индекс пользователя с этим логином и паролем
                }                                                                                   
        cout << "Wrong login or password! Try again?(y/n)\n";                                       // Если не совпадают, то попытаться снова, либо вернуться в меню регистрации/входа
        if (yesOrNot())
            continue;
        else
            return -1;
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
