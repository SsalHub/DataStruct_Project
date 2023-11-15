//옵션화면과 정지화면 담당
//가운데 상단에 PAUSE 글자 출력

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

void Pause()
{
    system("cls"); // 화면을 지워 새로운 화면 출력

    // 가운데에 "PAUSE" 출력
    int pauseTextLength = strlen("*********PAUSE********");
    int pauseX = (_SCREEN_WIDTH_ - pauseTextLength) / 2;
    int pauseY = _SCREEN_HEIGHT_ / 4;
    SetCurrentCursorPos(pauseX, pauseY);
    fprintf(stdout, "*********PAUSE********");

    // 점수 및 난이도 출력
    SetCurrentCursorPos(20, pauseY + 5);
    fprintf(stdout, "점수 : ");

    SetCurrentCursorPos(40, pauseY + 5);
    fprintf(stdout, "난이도 : ");
  
    // 메뉴 출력
    SetCurrentCursorPos(20, pauseY + 10);
    fprintf(stdout, "1. 게임으로 돌아가기");
  
    SetCurrentCursorPos(40, pauseY + 10);
    fprintf(stdout, "2. 게임 종료");
  
    SetCurrentCursorPos(30, pauseY + 25);
    fprintf(stdout, "3. 설정");

    // 사용자 입력 받기
    char choice = _getch();

    // 사용자의 선택에 따라 동작
    switch (choice) {
        case '1':
            // 게임으로 돌아가기
            break;
        case '2':
            // 게임 종료
            break;
        case '3':
            // 설정창 보여주기
            ShowSettings();
            break;
        default:
            fprintf(stdout, "잘못 입력하였습니다.");
            break;
    }
}

int main() {
    Pause();
    return 0;
}
