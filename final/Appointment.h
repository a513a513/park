#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include "Event.h"
#include <iostream>

// Event를 상속받는 구체 클래스 2: 장소 정보가 추가된 약속
class Appointment : public Event {
private:
    std::string location; // 약속 전용 고유 속성
public:
    Appointment(std::string t, std::string d, int p, std::string loc) : Event(t, d, p), location(loc) {}
    
    // Appointment에 맞는 출력 방식 적용 (장소 포함)
    void display() const override {
        std::cout << "[약속] " << title << " | 날짜: " << date << " | 장소: " << location << " | 상태: " << status << std::endl;
    }
    
    std::string getType() const override { return "Appointment"; }
    
    // 장소(location) 정보까지 포함하여 직렬화
    std::string serialize() const override {
        return "Appoint," + title + "," + date + "," + std::to_string(priority) + "," + std::to_string(status) + "," + location;
    }
};
#endif