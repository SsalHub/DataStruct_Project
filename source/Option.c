#define _SCREEN_WIDTH_ 60
#define _SCREEN_HEIGHT_ 24
int volume = 50;
int level = 1;

void ShowSettings() {
    system("cls");
    // 설정창 출력
    SetCurrentCursorPos(30, 2);
    fprintf(stdout, "------------------설정------------------");
    
    SetCurrentCursorPos(30, 10);
    fprintf(stdout, "1. 음량 설정");
    SetCurrentCursorPos(30, 20);
    fprintf(stdout, "2. 난이도 설정");
}

void AdjustVolume() {
    // 사용자 입력 받기
    int key = _getch();
    
    // 음량은 10단계
    // 키에 따라 동작 처리
    switch (key) {
        case 72:  // 방향키 위
            volume += 10;
            break;
        case 80:  // 방향키 아래
            volume -= 10;
            break;
        default:
            // 다른 키 입력에 대한 처리 추가
            break;
    }

    // 최소 0
    if (volume < 0) {
        volume = 0;
    }

    // 최대 100
    if (volume > 100) {
        volume = 100;
    }
}

void SelectLevel() {
    // 사용자 입력 받기
    int key = _getch();
    
    // 난이도는 4단계
    // 키에 따라 동작 처리
    switch (key) {
        case 72:  // 방향키 위
            Level += 1;
            break;
        case 80:  // 방향키 아래
            Level -= 1;
            break;
        default:
            // 다른 키 입력에 대한 처리 추가
            break;
    }

    // 최소 1
    if (volume < 1) {
        volume = 1;
    }

    // 최대 100
    if (volume > 4) {
        volume = 4;
    }
}

int main() {
        ShowSettings();

        // 사용자 입력 받기
        char choice = _getch();

        // 사용자의 선택에 따라 동작
        switch (choice) {
            case '1':
                // 음량 설정
                AdjustVolume();
                break;
            case '2':
                // 난이도 설정
                SelectLevel();
                break;
            case '3':
                // 나가기
                // Add your code here
                break;
            default:
                // 예외 처리 또는 다른 동작 추가
                break;
        }
    }
    return 0;
}
