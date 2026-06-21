#include "Scheduler.h"
#include "Task.h"
#include "Appointment.h"
#include "Exceptions.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

// 소멸자: 동적 할당된(new) 객체들의 메모리 누수 방지를 위해 delete 호출
Scheduler::~Scheduler() {
    for (auto e : events) delete e;
}

void Scheduler::addEvent(Event* e) {
    events.push_back(e);
}

void Scheduler::deleteEvent(int index) {
    if (index < 0 || index >= events.size()) return;
    delete events[index]; // 메모리 해제
    events.erase(events.begin() + index); // 벡터에서 요소 제거
}

// [선택 요건: STL + 알고리즘 + 람다]
// std::sort 알고리즘과 람다 함수를 결합하여 날짜순 오름차순 정렬
void Scheduler::sortByDate() {
    std::sort(events.begin(), events.end(), [](Event* a, Event* b) {
        return a->getDate() < b->getDate();
    });
}

// 우선순위 내림차순 정렬 (높은 숫자가 먼저 오도록)
void Scheduler::sortByPriority() {
    std::sort(events.begin(), events.end(), [](Event* a, Event* b) {
        return a->getPriority() > b->getPriority();
    });
}

// 상태 조건으로 검색하여 일치하는 항목만 출력
void Scheduler::searchByStatus(int s) {
    std::cout << "\n--- 검색 결과 (상태: " << s << ") ---" << std::endl;
    for (auto e : events) {
        if (e->getStatus() == s) e->display(); // 다형성에 의해 알아서 알맞은 display 호출
    }
}

void Scheduler::showAll() {
    for (int i = 0; i < events.size(); ++i) {
        std::cout << i << ". ";
        events[i]->display();
    }
}

// [필수 요건 ③: 파일 I/O - 저장]
void Scheduler::saveToFile(std::string filename) {
    std::ofstream outFile(filename);
    if (!outFile) throw FileOpenException(); // 파일 열기 실패 시 예외 던짐
    
    for (auto e : events) {
        // serialize()를 통해 문자열로 변환 후 파일에 한 줄씩 쓰기
        outFile << e->serialize() << std::endl;
    }
    outFile.close();
}

// [필수 요건 ③: 파일 I/O - 로드]
void Scheduler::loadFromFile(std::string filename) {
    std::ifstream inFile(filename);
    if (!inFile) return; // 파일이 없으면 그냥 통과 (첫 실행 시 등)
    
    std::string line;
    // 텍스트 파일에서 한 줄씩 읽어오기
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string type, title, date, pStr, sStr, loc;
        
        // 쉼표(,)를 구분자로 사용하여 데이터 분리
        std::getline(ss, type, ',');
        std::getline(ss, title, ',');
        std::getline(ss, date, ',');
        std::getline(ss, pStr, ',');
        std::getline(ss, sStr, ',');
        
        // 타입에 따라 알맞은 자식 객체를 동적 생성(new)하여 복원
        if (type == "Task") {
            Task* t = new Task(title, date, std::stoi(pStr));
            t->setStatus(std::stoi(sStr));
            addEvent(t);
        } else if (type == "Appoint") {
            std::getline(ss, loc, ',');
            Appointment* a = new Appointment(title, date, std::stoi(pStr), loc);
            a->setStatus(std::stoi(sStr));
            addEvent(a);
        }
    }
}

int Scheduler::getCount() {
    return events.size();
}