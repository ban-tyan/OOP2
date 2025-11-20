/**
 * @file time.h
 * @brief Заголовочный файл класса Time для работы с временем
 */

 #ifndef TIME_H
 #define TIME_H
 
 #include <cstddef>
 
 /**
  * @class Time
  * @brief Класс для работы с временем в формате часы:минуты:секунды
  */
 class Time {
 private:
     int totalSeconds_; ///< Общее количество секунд
     
     static size_t operationCount_; ///< Статический счетчик операций/объектов
 
 public:
     // Конструкторы 3 штуки
     
     /**
      * @brief Конструктор по умолчанию. Создает время 00:00:00
      */
     Time();
     
     /**
      * @brief Параметризованный конструктор
      * @param hours Часы
      * @param minutes Минуты
      * @param seconds Секунды
      */
     Time(int hours, int minutes, int seconds);
     
     /**
      * @brief Конструктор копирования
      * @param other Объект для копирования
      */
     Time(const Time& other);
     
     /**
      * @brief Деструктор с выводом сообщения
      */
     ~Time();
     
     // Методы доступа
     
     /**
      * @brief Установить время
      * @param hours Часы
      * @param minutes Минуты
      * @param seconds Секунды
      */
     void setTime(int hours, int minutes, int seconds);
     
     /**
      * @brief Получить часы
      * @return Значение часов
      */
     int getHours() const;
     
     /**
      * @brief Получить минуты
      * @return Значение минут
      */
     int getMinutes() const;
     
     /**
      * @brief Получить секунды
      * @return Значение секунд
      */
     int getSeconds() const;
     
     /**
      * @brief Получить общее количество секунд
      * @return Общие секунды
      */
     int getTotalSeconds() const;
     
     /**
      * @brief Вывести время в формате HH:MM:SS
      */
     void print() const;
     
     /**
      * @brief Получить количество операций/объектов
      * @return Статистика работы
      */
     static size_t getOperationCount();
     
     // Унарные операторы (4 варианта)
     Time& operator++();       ///< Префиксный инкремент (+1 секунда)
     Time operator++(int);     ///< Постфиксный инкремент  
     Time& operator--();       ///< Префиксный декремент (-1 секунда)
     Time operator--(int);     ///< Постфиксный декремент
 
     // Операторы арифметического присваивания
     Time& operator+=(const Time& other); ///< Прибавить время
     Time& operator-=(const Time& other); ///< Вычесть время
     Time& operator*=(double scalar);     ///< Умножить на скаляр
     Time& operator/=(double scalar);     ///< Разделить на скаляр
 
     // Бинарные арифметические операторы
     Time operator+(const Time& other) const; ///< Сложение времени
     Time operator-(const Time& other) const; ///< Вычитание времени
     Time operator*(double scalar) const;     ///< Умножение на скаляр
     Time operator/(double scalar) const;     ///< Деление на скаляр
 
     // Бинарные операторы сравнения
     bool operator<(const Time& other) const;  ///< Меньше
     bool operator>(const Time& other) const;  ///< Больше
     bool operator<=(const Time& other) const; ///< Меньше или равно
     bool operator>=(const Time& other) const; ///< Больше или равно
     bool operator==(const Time& other) const; ///< Равно
     bool operator!=(const Time& other) const; ///< Не равно
 };
 
 #endif