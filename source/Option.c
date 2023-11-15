#define _SCREEN_WIDTH_ 60
#define _SCREEN_HEIGHT_ 24
int volume = 50;

void ShowSettings() {
    system("cls");
    // 설정창 출력
    PrintTextInBox("*********설정*********", 0, 0, _SCREEN_WIDTH_, _SCREEN_HEIGHT_);
    PrintTextInBox("1. 음량", 10, 4, 40, 3);
    PrintTextInBox("2. 난이도 설정", 10, 8, 40, 3);
    PrintTextInBox("3. 나가기", 10, 12, 40, 3);
}

void AdjustVolume() {
    system("cls");

    PrintTextInBox("*********음량 설정*********", 0, 0, _SCREEN_WIDTH_, _SCREEN_HEIGHT_);
    PrintTextInBox("현재 음량: %d", 10, 4, 40, 3, volume);

    // 사용자 입력 받기
    int key = _getch();

    // 키에 따라 동작 처리
    switch (key) {
        case 72:  // 방향키 위
            volume += 5;
            break;
        case 80:  // 방향키 아래
            volume -= 5;
            break;
        default:
            // 다른 키 입력에 대한 처리 추가
            break;
    }

    // 음량이 음수가 되지 않도록 보정
    if (volume < 0) {
        volume = 0;
    }

    // 음량이 100을 초과하지 않도록 보정
    if (volume > 100) {
        volume = 100;
    }
}
