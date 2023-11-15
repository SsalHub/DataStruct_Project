#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include <Windows.h>

//�ɼ�ȭ��� ����ȭ�� ���
//��� ��ܿ� PAUSE ���� ���

#define _SCREEN_WIDTH_ 60
#define _SCREEN_HEIGHT_ 24

int volume = 50;
int Level = 1;

void ShowSettings() {
    system("cls");


    // ����â ���
    gotoxy(30, 2);
    fprintf(stdout, "------------------����------------------");
    gotoxy(30, 10);
    fprintf(stdout, "1. ���� ����");
    gotoxy(30, 20);
    fprintf(stdout, "2. ���̵� ����");

    // ����� �Է� �ޱ�
    char choice = _getch();

    // ������� ���ÿ� ���� ����
    switch (choice) {
    case '1':
        AdjustVolume();
        break;
    case '2':
        SelectLevel();
        break;
    case '3':
        // ����â �����ֱ�
        ShowSettings();
        break;
    default:
        fprintf(stdout, "�߸� �Է��Ͽ����ϴ�.");
        break;
    }
}



void AdjustVolume(){
    // ����� �Է� �ޱ�
    int key = _getch();

    // ������ 10�ܰ�
    // Ű�� ���� ���� ó��
    switch (key) {
    case 72:  // ����Ű ��
        volume += 10;
        break;
    case 80:  // ����Ű �Ʒ�
        volume -= 10;
        break;
    default:
        // �ٸ� Ű �Է¿� ���� ó�� �߰�
        break;
    }

    // �ּ� 0
    if (volume < 0) {
        volume = 0;
    }

    // �ִ� 100
    if (volume > 100) {
        volume = 100;
    }
}

// ���̵� ����
void SelectLevel() {
    // ����� �Է� �ޱ�
    int key = _getch();

    // ���̵��� 4�ܰ�
    // Ű�� ���� ���� ó��
    switch (key) {
    case 72:  // ����Ű ��
        Level += 1;
        break;
    case 80:  // ����Ű �Ʒ�
        Level -= 1;
        break;
    default:
        // �ٸ� Ű �Է¿� ���� ó�� �߰�
        break;
    }

    // �ּ� 1
    if (volume < 1) {
        volume = 1;
    }

    // �ִ� 100
    if (volume > 4) {
        volume = 4;
    }
}


void Pause()
{
    system("cls"); // ȭ���� ���� ���ο� ȭ�� ���

    // ����� "PAUSE" ���
    int pauseTextLength = strlen("*********PAUSE********");
    int pauseX = (_SCREEN_WIDTH_ - pauseTextLength) / 2;
    int pauseY = _SCREEN_HEIGHT_ / 4;
    gotoxy(pauseX, pauseY);
    fprintf(stdout, "*********PAUSE********");

    // ���� �� ���̵� ���
    gotoxy(20, pauseY + 5);
    fprintf(stdout, "���� : ");

    gotoxy(40, pauseY + 5);
    fprintf(stdout, "���̵� : ");

    // �޴� ���
    gotoxy(20, pauseY + 10);
    fprintf(stdout, "1. �������� ���ư���");

    gotoxy(40, pauseY + 10);
    fprintf(stdout, "2. ���� ����");

    gotoxy(30, pauseY + 25);
    fprintf(stdout, "3. ����");

    // ����� �Է� �ޱ�
    char choice = _getch();

    // ������� ���ÿ� ���� ����
    switch (choice) {
    case '1':
        // �������� ���ư���
        break;
    case '2':
        // ���� ����
        break;
    case '3':
        // ����â �����ֱ�
        ShowSettings();
        break;
    default:
        fprintf(stdout, "�߸� �Է��Ͽ����ϴ�.");
        break;
    }
}

int main() {
    Pause();
    return 0;
}