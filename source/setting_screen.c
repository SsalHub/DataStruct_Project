#define _CRT_SECURE_NO_WARNINGS
#include "setting_screen.h"

int volume;

void ShowSettings() {
    int Level = 1;

    clearScreen();

    char Option[100] = "------------------����------------------";
    printString(Option, 20, 9);
    char s1[100] = "1. ���� ����";
    char s2[100] = "2. ���̵� ����";
    printString(s1, 23, 13);
    printString(s2, 23, 16);

    // ����� �Է� �ޱ�
    char choice = _getch();
}

    /* ������� ���ÿ� ���� ����
    switch (choice) {
    case '1':
        AdjustVolume();
        break;
    case '2':
        SelectLevel(Level);
        break;
    case '3':
        // ����â �����ֱ�
        ShowSettings();
        break;
    default:
        fprintf(stdout, "�߸� �Է��Ͽ����ϴ�.");
        break;
    }
}*/



void AdjustVolume() {
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
void SelectLevel(int Level) {
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