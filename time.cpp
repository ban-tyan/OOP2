/**
 * @file time.cpp
 * @brief Реализация методов класса Time
 */

 #include "time.h"
 #include <iostream>
 
 using namespace std;
 
 size_t Time::operationCount_ = 0;
 
 Time::Time() : totalSeconds_(0) {
     operationCount_++;
 }
 
 Time::Time(int hours, int minutes, int seconds) {
     totalSeconds_ = hours * 3600 + minutes * 60 + seconds;
     operationCount_++;
 }
 
 Time::Time(const Time& other) : totalSeconds_(other.totalSeconds_) {
     operationCount_++;
 }
 
 Time::~Time() {
     cout << "[DELETED] Time object with value ";
     print();
     cout << endl;
 }
 
 void Time::setTime(int hours, int minutes, int seconds) {
     totalSeconds_ = hours * 3600 + minutes * 60 + seconds;
 }
 
 int Time::getHours() const {
     return totalSeconds_ / 3600;
 }
 
 int Time::getMinutes() const {
     return (totalSeconds_ % 3600) / 60;
 }
 
 int Time::getSeconds() const {
     return totalSeconds_ % 60;
 }
 
 int Time::getTotalSeconds() const {
     return totalSeconds_;
 }
 
 Time& Time::operator++() {
     totalSeconds_++;
     return *this;
 }
 
 Time Time::operator++(int) {
     Time temp(*this);
     totalSeconds_++;
     return temp;
 }
 
 Time& Time::operator--() {
     if (totalSeconds_ > 0) totalSeconds_--;
     return *this;
 }
 
 Time Time::operator--(int) {
     Time temp(*this);
     if (totalSeconds_ > 0) totalSeconds_--;
     return temp;
 }
 
 Time& Time::operator+=(const Time& other) {
     totalSeconds_ += other.totalSeconds_;
     return *this;
 }
 
 Time& Time::operator-=(const Time& other) {
     totalSeconds_ -= other.totalSeconds_;
     if (totalSeconds_ < 0) totalSeconds_ = 0;
     return *this;
 }
 
 Time& Time::operator*=(double scalar) {
     totalSeconds_ = static_cast<int>(totalSeconds_ * scalar);
     return *this;
 }
 
 Time& Time::operator/=(double scalar) {
     if (scalar != 0) {
         totalSeconds_ = static_cast<int>(totalSeconds_ / scalar);
     }
     return *this;
 }
 
 Time Time::operator+(const Time& other) const {
     Time result(*this);
     result += other;
     return result;
 }
 
 Time Time::operator-(const Time& other) const {
     Time result(*this);
     result -= other;
     return result;
 }
 
 Time Time::operator*(double scalar) const {
     Time result(*this);
     result *= scalar;
     return result;
 }
 
 Time Time::operator/(double scalar) const {
     Time result(*this);
     result /= scalar;
     return result;
 }
 
 bool Time::operator<(const Time& other) const {
     return totalSeconds_ < other.totalSeconds_;
 }
 
 bool Time::operator>(const Time& other) const {
     return totalSeconds_ > other.totalSeconds_;
 }
 
 bool Time::operator<=(const Time& other) const {
     return totalSeconds_ <= other.totalSeconds_;
 }
 
 bool Time::operator>=(const Time& other) const {
     return totalSeconds_ >= other.totalSeconds_;
 }
 
 bool Time::operator==(const Time& other) const {
     return totalSeconds_ == other.totalSeconds_;
 }
 
 bool Time::operator!=(const Time& other) const {
     return totalSeconds_ != other.totalSeconds_;
 }
 
 void Time::print() const {
     int hours = getHours();
     int minutes = getMinutes();
     int seconds = getSeconds();
     
     cout << hours << ":";
     if (minutes < 10) cout << "0";
     cout << minutes << ":";
     if (seconds < 10) cout << "0";
     cout << seconds;
 }
 
 size_t Time::getOperationCount() {
     return operationCount_;
 }