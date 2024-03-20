#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;





char** create() {                                                           //������ ����, �������� ����
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
    srand(time(NULL));                                                   //������ ������ ���� ��������� �����
    int num = rand() % 2;                                               //����� ��� ���������� ������ ����
    cout << "������� ��� ������� ������: ";
    cin >> Name1;
    cout << "������� ��� ������� ������: ";
    cin >> Name2;
    if (num) {                                                          //��������� ����� ������� ����
        string tmp = Name1;
        Name1 = Name2;
        Name2 = tmp;
    }
    cout << "������ �����: " << Name1 << endl;
}


void startGame(char** field, char c = '_') {                            //���������� ���� 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            field[i][j] = c;
        }
    }
}


void output(char** field) {                                                 //����� ���� �� �����
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
    //�������� ������� ��������� �� ������� ���� ������                                     �������� �������� ��������� �� ������� ���� ������
    if (field[0][0] == field[1][1] && field[0][0] == field[2][2] && (field[0][0] == 'X' || field[0][0] == 'O') || field[2][0] == field[1][1] && field[2][0] == field[0][2] && (field[2][0] == 'X' || field[2][0] == 'O')) {
        chekWin = true;
        if (field[1][1] == 'X') {
            gamer = true;
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            //�������� N-��� �������������� ������ �� ������� ���� ������                                       �������� N-��� ������������ ������ �� ������� ���� ������
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
        if (gamer) {                                                    //���� gamer=true, �� ����� 1
            cout << "������� " << Name1 << endl;
        }
        else {
            cout << "�������  " << Name2 << endl;                       //����� 2
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
            cout << "�����" << endl;
            return true;
        }
    }

    return false;
}


void input(char** field, bool& gamer, string& Name1, string& Name2) {

    string answer;
    int num;
    
    while (true) {

        if (gamer) {                                                                  //���� ����� 1
            cout << Name1;
        }
        else {                                                                        //���� �� ����� 1, �� ����� 2
            cout << Name2;
        }
        cout << ", ������� ����� ������ � �������: ";


        cin >> answer;
        num = stoi(answer);
        if (num> 10 && num < 34) {                                                   //�������� ������ ����� � �������� ������, ����������� ���� �����
            int i = num / 10;                                                        //������ ����
            int j = num % 10;                                                        //������� ����

            if (0 < j && j < 4) {
                if (field[i - 1][j - 1] != 'X' && field[i - 1][j - 1] != 'O') {     //�������� �� ����������� ����
                    if (gamer) {                                                         //���� ����� 1, �� �
                        field[i - 1][j - 1] = 'X';
                    }
                    else {                                                           //����� 2, �
                        field[i - 1][j - 1] = 'O';
                    }
                    gamer = !gamer;                                         
                    break;
                }
            }
        }
        cout << "�� ����� �������� ������" << endl;
    }
}





bool restart() {                                                                               //�������
    bool flag = true;
    while (true) {
        string answer;
        cout << "������ �� �� ���������� ����?(��/���)" << endl << "������� �����: ";
        cin >> answer;
        if (answer == "��") {
            break;
        }
        else if (answer == "���") {
            flag = false;
            break;
        }
        else {
            cout << "������ ������ �� ����������!";
        }
    }
    return flag;
}
void deleteF(char** field) {                                            //�������� ����
    for (int i = 0; i < 3; i++) {
        delete[] field[i];                                              //�������� ���������
    }
    delete[] field;                                                     //�������� �������
}






int main() {
    SetConsoleCP(1251);                             //��� ����� ��������� ����
    SetConsoleOutputCP(1251);                       //��� ������ ��������� ����
    bool gamer = true;
    char** field = create();                        //��������� ����
    string Name1, Name2;
    createPlayer(Name1, Name2);                     //�������� �������
    while (true) {
        startGame(field);                           //����� ����. ���� ����� ������� ��, �� ���� ��� ����� ���� �� ��������
        while (true) {
            system("Cls");                          //������� ������� �� ������
            output(field);                          //����� ����
            if (chekWin(field, Name1, Name2))       //�������� ������
                break;
            input(field, gamer, Name1, Name2);      //���� �� ������, �� ������ ������

        }
        if (!restart())                             //����� ����
            break;
    }
    deleteF(field);                                   //������� ���� 
}

