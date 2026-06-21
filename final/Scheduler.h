#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <vector>
#include <string>
#include "Event.h"

// [필수 요건 ①: 책임 분리]
// 일정 데이터를 관리(추가, 삭제, 조회, 정렬, 저장)하는 매니저 클래스입니다.
class Scheduler {
private:
    // [선택 요건: STL 컨테이너] 다형성을 위해 부모 포인터(Event*)의 백터를 사용
    std::vector<Event*> events;

public:
    ~Scheduler();
    void addEvent(Event* e);
    void deleteEvent(int index);
    void sortByDate();
    void sortByPriority();
    void searchByStatus(int s);
    void showAll();
    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);
    int getCount(); // 테스트용
};
#endif