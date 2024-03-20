#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;





char** create() {                                                           //Первая игра, создание поля
    char c = '_';
    int const n = 3;
    char** field = new char* [n];
    for (int i = 0; i < n; i++) {
        field[i] = new char[n];
        field[i][0] = c;
        field[i][1] = c;
        field[i][2] = c;
    }
    return field;
}


void createPlayer(string& Name1, string& Name2) {
    srand(time(NULL));                                                   //Задаем разную базу рандомных чисел
    int num = rand() % 2;                                               //Число для случайного выбора хода
    cout << "Введите имя первого игрока: ";
    cin >> Name1;
    cout << "Введите имя второго игрока: ";
    cin >> Name2;
    if (num) {                                                          //Случайный выбор первого хода
        string tmp = Name1;
        Name1 = Name2;
        Name2 = tmp;
    }
    cout << "Первым ходит: " << Name1 << endl;
}


void startGame(char** field, char c = '_') {                            //Заполнение поля 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            field[i][j] = c;
        }
    }
}


void output(char** field) {                                                 //Вывод поля на экран
    cout << "  1 2 3" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

bool chekWin(char** field, string& Name1, string& Name2) {
    bool chekWin = false, gamer = false;
    //Проверка главной диагонали на наличие трех знаков                                     Проверка побочной диагонали на наличие трех знаков
    if (field[0][0] == field[1][1] && field[0][0] == field[2][2] && (field[0][0] == 'X' || field[0][0] == 'O') || field[2][0] == field[1][1] && field[2][0] == field[0][2] && (field[2][0] == 'X' || field[2][0] == 'O')) {
        chekWin = true;
        if (field[1][1] == 'X') {
            gamer = true;
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            //Проверка N-ной горизонтальной строки на наличие трех знаком                                       Проверка N-ной вертикальной строки на наличие трех знаком
            if (field[i][0] == field[i][1] && field[i][0] == field[i][2] && (field[i][0] == 'X' || field[i][0] == 'O') || field[0][i] == field[1][i] && field[0][i] == field[2][i] && (field[0][i] == 'X' || field[0][i] == 'O')) {
                chekWin = true;
                if (field[i][i] == 'X') {
                    gamer = true;
                }
                break;
            }
        }
    }

    if (chekWin) {
        if (gamer) {                                                    //Если gamer=true, то игрок 1
            cout << "победил " << Name1 << endl;
        }
        else {
            cout << "победил  " << Name2 << endl;                       //Игрок 2
        }
        return true;
    }
    else {
        bool draw = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i][j] != 'X' && field[i][j] != 'O') {
                    draw = false;
                }
            }
        }

        if (draw) {
            cout << "ничья" << endl;
            return true;
        }
    }

    return false;
}


void input(char** field, bool& gamer, string& Name1, string& Name2) {

    string answer;
    int num;
    
    while (true) {

        if (gamer) {                                                                  //Если игрок 1
            cout << Name1;
        }
        else {                                                                        //Если не игрок 1, то игрок 2
            cout << Name2;
        }
        cout << ", введите номер строки и столбца: ";


        cin >> answer;
        num = stoi(answer);
        if (num> 10 && num < 34) {                                                   //Вводятся номера строк и столбцов слитно, представляя одно число
            int i = num / 10;                                                        //Строка поля
            int j = num % 10;                                                        //Столбец поля

            if (0 < j && j < 4) {
                if (field[i - 1][j - 1] != 'X' && field[i - 1][j - 1] != 'O') {     //Проверка на незанятость поля
                    if (gamer) {                                                         //Если игрок 1, то Х
                        field[i - 1][j - 1] = 'X';
                    }
                    else {                                                           //Игрок 2, О
                        field[i - 1][j - 1] = 'O';
                    }
                    gamer = !gamer;                                         
                    break;
                }
            }
        }
        cout << "Вы ввели неверную ячейку" << endl;
    }
}





bool restart() {                                                                               //Рестарт
    bool flag = true;
    while (true) {
        string answer;
        cout << "Хотите ли вы продолжить игру?(Да/Нет)" << endl << "Введите ответ: ";
        cin >> answer;
        if (answer == "Да") {
            break;
        }
        else if (answer == "Нет") {
            flag = false;
            break;
        }
        else {
            cout << "Такого ответа не существует!";
        }
    }
    return flag;
}
void deleteF(char** field) {                                            //Удаление поля
    for (int i = 0; i < 3; i++) {
        delete[] field[i];                                              //Удаление элементов
    }
    delete[] field;                                                     //Удаление массива
}






int main() {
    SetConsoleCP(1251);                             //Для ввода латинских букв
    SetConsoleOutputCP(1251);                       //Для вывода латинских букв
    bool gamer = true;
    char** field = create();                        //Создается поле
    string Name1, Name2;
    createPlayer(Name1, Name2);                     //Создание игроков
    while (true) {
        startGame(field);                           //Новая игра. Если игрок напишет Да, то игра без этого поля не начнется
        while (true) {
            system("Cls");                          //очистка консоли от мусора
            output(field);                          //вывод поля
            if (chekWin(field, Name1, Name2))       //проверка победы
                break;
            input(field, gamer, Name1, Name2);      //если не победа, то играем дальше

        }
        if (!restart())                             //новая игра
            break;
    }
    deleteF(field);                                   //Удалить поле 
}

