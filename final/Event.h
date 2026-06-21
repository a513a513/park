#ifndef EVENT_H
#define EVENT_H
#include <string>

// [필수 요건 ①, ②: 추상 클래스 설계 및 다형성]
// 모든 일정(Task, Appointment)의 공통 속성과 기능을 정의하는 부모 클래스입니다.
class Event {
protected:
    // 자식 클래스에서 접근 가능하도록 protected로 선언
    std::string title;
    std::string date;
    int status; // 0: 미완료, 1: 진행중, 2: 완료
    int priority; // 중요도

public:
    Event(std::string t, std::string d, int p) : title(t), date(d), status(0), priority(p) {}
    
    // [선택 요건: 동적 할당] 
    // 다형성을 사용할 때 자식 클래스의 소멸자가 정상 호출되도록 가상 소멸자 지정
    virtual ~Event() {}

    // 순수 가상 함수 (= 0): 자식 클래스에서 반드시 구현해야 합니다. (다형성 핵심)
    virtual void display() const = 0;           // 일정 출력
    virtual std::string getType() const = 0;    // 일정 종류 반환
    virtual std::string serialize() const = 0;  // 파일 저장을 위한 문자열 변환

    // 공통 속성에 대한 Getter 및 Setter
    std::string getTitle() const { return title; }
    std::string getDate() const { return date; }
    int getStatus() const { return status; }
    int getPriority() const { return priority; }
    void setStatus(int s) { status = s; }
};
#endif