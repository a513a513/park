#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

// [필수 요건 ④: 예외 처리]
// std::exception을 상속받아 사용자 정의 예외 클래스를 생성합니다.
class InvalidDateException : public std::exception {
public:
    // 날짜 길이가 10자(YYYY-MM-DD)가 아닐 때 던질 예외 메시지
    const char* what() const noexcept override { return "Error: 잘못된 날짜 형식입니다. (YYYY-MM-DD)"; }
};

class FileOpenException : public std::exception {
public:
    // 파일 저장 시 오류가 발생할 때 던질 예외 메시지
    const char* what() const noexcept override { return "Error: 파일을 열 수 없습니다."; }
};
#endif