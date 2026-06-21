#ifndef TASK_H
#define TASK_H
#include "Event.h"
#include <iostream>

// Event를 상속받는 구체 클래스 1: 단순 할일
class Task : public Event {
public:
    // 부모 클래스의 생성자를 호출하여 공통 데이터 초기화
    Task(std::string t, std::string d, int p) : Event(t, d, p) {}
    
    // 부모의 가상 함수 오버라이딩 (Task에 맞는 출력 방식 적용)
    void display() const override {
        std::cout << "[할일] " << title << " | 날짜: " << date << " | 우선순위: " << priority << " | 상태: " << status << std::endl;
    }
    
    std::string getType() const override { return "Task"; }
    
    // 파일에 저장하기 위해 속성들을 쉼표(,)로 구분한 문자열로 만듦
    std::string serialize() const override {
        return "Task," + title + "," + date + "," + std::to_string(priority) + "," + std::to_string(status);
    }
};
#endif