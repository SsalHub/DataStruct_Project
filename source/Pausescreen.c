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

    //점수
    SetCurrentCursorPos(20, pauseY + 5);
    fprintf(stdout, "점수 : ");

    SetCurrentCursorPos(40, pauseY + 5);
    fprintf(stdout, "난이도 : ");
  
    // 메뉴 출력
    SetCurrentCursorPos(pauseX, pauseY + 10);
    fprintf(stdout, "게임으로 돌아가기");
  
    SetCurrentCursorPos(pauseX, pauseY + 10);
    fprintf(stdout, "게임 종료");
  
    // 설정 
    SetCurrentCursorPos(pauseX, pauseY + 15);
    fprintf(stdout, "설정");


}
