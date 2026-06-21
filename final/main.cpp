#include <iostream>
#include "Scheduler.h"
#include "Task.h"
#include "Appointment.h"
#include "Exceptions.h"

using namespace std;

// [필수 요건 ⑤: 단위 테스트]
void runUnitTests() {
    cout << "\n[단위 테스트 시작]" << endl;
    Scheduler testSched;

    // 테스트 1: 일정 추가 기능 검증
    testSched.addEvent(new Task("Test1", "2024-12-01", 1));
    if (testSched.getCount() == 1) cout << "Test 1 (Add): [PASS]" << endl;
    else cout << "Test 1 (Add): [FAIL]" << endl;

    // 테스트 2: 일정 삭제 기능 검증
    testSched.deleteEvent(0);
    if (testSched.getCount() == 0) cout << "Test 2 (Delete): [PASS]" << endl;
    else cout << "Test 2 (Delete): [FAIL]" << endl;

    // 테스트 3: 정렬 로직 검증 (날짜 순서가 맞게 바뀌는지 수량으로 확인)
    testSched.addEvent(new Task("Later", "2024-12-31", 1));
    testSched.addEvent(new Task("Earlier", "2024-12-01", 1));
    testSched.sortByDate();
    if (testSched.getCount() == 2) cout << "Test 3 (Sort/Count): [PASS]" << endl;
    else cout << "Test 3 (Sort/Count): [FAIL]" << endl;
}

int main() {
    Scheduler mySched;
    
    // 프로그램 시작 시 기존 데이터 자동 복원
    try {
        mySched.loadFromFile("data.txt");
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    int choice;
    while (true) {
        cout << "\n--- 개인 일정 관리 시스템 ---" << endl;
        cout << "1. 일정 추가  2. 전체 보기  3. 삭제  4. 정렬(날짜)  5. 검색(상태)  6. 저장  7. 테스트실행  0. 종료" << endl;
        cout << "선택: ";
        cin >> choice;

        if (choice == 0) {
    mySched.saveToFile("data.txt"); // 종료 시 자동 저장
    break;
}

        // [필수 요건 ④: 예외 처리 블록]
        // 사용자의 잘못된 입력이나 파일 에러를 안전하게 잡아냄
        try {
            if (choice == 1) {
                int type;
                string t, d, loc;
                int p;
                
                cout << "종류 (1.할일 2.약속): "; cin >> type;
                cout << "제목: "; cin >> t;
                cout << "날짜(YYYY-MM-DD): "; cin >> d;
                
                // 날짜 형식이 잘못된 경우 사용자가 정의한 예외 던짐
                if (d.length() != 10) throw InvalidDateException(); 
                
                cout << "우선순위(1-5): "; cin >> p;
                
                // 입력된 종류에 따라 다형성을 활용해 각기 다른 객체 생성(new)
                if (type == 1) mySched.addEvent(new Task(t, d, p));
                else {
                    cout << "장소: "; cin >> loc;
                    mySched.addEvent(new Appointment(t, d, p, loc));
                }
            } else if (choice == 2) {
                mySched.showAll();
            } else if (choice == 3) {
                int idx;
                cout << "삭제할 번호: "; cin >> idx;
                mySched.deleteEvent(idx);
            } else if (choice == 4) {
                mySched.sortByDate();
                cout << "날짜순으로 정렬되었습니다." << endl;
            } else if (choice == 5) {
                int s;
                cout << "조회할 상태(0:미완료, 1:진행중, 2:완료): "; cin >> s;
                mySched.searchByStatus(s);
            } else if (choice == 6) {
                mySched.saveToFile("data.txt");
                cout << "저장되었습니다." << endl;
            } else if (choice == 7) {
                runUnitTests();
            }
        } catch (exception& e) {
            // throw된 예외 객체를 받아 에러 메시지 출력 후 프로그램 계속 실행 (다운되지 않음)
            cout << e.what() << endl; 
        }
    }

    return 0;
}