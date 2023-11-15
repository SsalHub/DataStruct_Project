//옵션화면과 정지화면 담당
//가운데 상단에 PAUSE 글자 출력

#define _SCREEN_WIDTH_ 60
#define _SCREEN_HEIGHT_ 24

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
