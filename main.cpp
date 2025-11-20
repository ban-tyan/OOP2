/**
 * @file main.cpp
 * @brief Демонстрационная программа для класса Time с интерактивным меню
 */

 #include "time.h"
 #include <iostream>
 #include <limits>
 #include <vector>
 #include <string>
 using namespace std;
 
 struct Event {
     string name;
     Time startTime;
     Time endTime;
     Time plannedDuration;
     Time actualDuration;
 };
 
 vector<Event> schedule; // Все мероприятия
 
 // Вспомогательные функции
 void clearInputBuffer() {
     cin.clear();
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
 }
 
 void waitForEnter() {
     cout << "\nНажмите Enter для продолжения...";
     clearInputBuffer();
     cin.get();
 }
 
 // Выбор мероприятия
 int selectEvent(const string& prompt) {
     if (schedule.empty()) {
         cout << "\nРасписание пусто! Создайте мероприятие в пункте 1.\n";
         return -1;
     }
     
     cout << prompt;
     for (size_t i = 0; i < schedule.size(); i++) {
         cout << i + 1 << ". " << schedule[i].name << " (";
         schedule[i].startTime.print();
         cout << " - ";
         schedule[i].endTime.print();
         cout << ")" << endl;
     }
     
     int choice;
     cout << "Выберите (0 - отмена): ";
     cin >> choice;
     
     if (cin.fail() || choice < 0 || choice > static_cast<int>(schedule.size())) {
         clearInputBuffer();
         cout << "Ошибка ввода!\n";
         return -1;
     }
     
     return choice - 1;
 }
 
 // Обновление фактической длительности с учётом перехода через сутки
 void updateActualDuration(Event& event) {
     int startSec = event.startTime.getTotalSeconds();
     int endSec = event.endTime.getTotalSeconds();
     int actualSec = endSec - startSec;
     
     // Если конец меньше начала (например, 23:00 → 04:00), добавляем сутки
     if (actualSec < 0) {
         actualSec += 24 * 3600; // 86400 секунд
     }
     
     event.actualDuration.setTime(0, 0, actualSec);
 }
 
 // Пункт 1: Создание/изменение мероприятий
 void manageSchedule() {
     int choice;
     do {
         system("clear");
         cout << "=== СОЗДАНИЕ/ИЗМЕНЕНИЕ МЕРОПРИЯТИЙ ===\n\n";
         cout << "Количество мероприятий: " << schedule.size() << endl << endl;
         
         cout << "1. Добавить новое мероприятие\n";
         cout << "2. Редактировать мероприятие\n";
         cout << "3. Удалить мероприятие\n";
         cout << "4. Просмотреть все мероприятия\n";
         cout << "0. Назад\n";
         cout << "Выберите: ";
         cin >> choice;
         
         if (cin.fail()) {
             clearInputBuffer();
             cout << "Ошибка ввода!\n";
             waitForEnter();
             continue;
         }
         
         switch (choice) {
             case 1: {
                 Event newEvent;
                 cout << "\nВведите название мероприятия: ";
                 clearInputBuffer();
                 getline(cin, newEvent.name);
                 
                 int h, m, s;
                 cout << "Введите время начала (часы минуты секунды): ";
                 cin >> h >> m >> s;
                 if (cin.fail() || h < 0 || m < 0 || s < 0 || m >= 60 || s >= 60) {
                     cout << "Ошибка ввода времени!\n";
                     clearInputBuffer();
                 } else {
                     newEvent.startTime.setTime(h, m, s);
                     
                     cout << "Введите время окончания (часы минуты секунды): ";
                     cin >> h >> m >> s;
                     if (cin.fail() || h < 0 || m < 0 || s < 0 || m >= 60 || s >= 60) {
                         cout << "Ошибка ввода времени!\n";
                         clearInputBuffer();
                     } else {
                         newEvent.endTime.setTime(h, m, s);
                         
                         cout << "Введите планируемую длительность (часы минуты секунды): ";
                         cin >> h >> m >> s;
                         if (cin.fail() || h < 0 || m < 0 || s < 0 || m >= 60 || s >= 60) {
                             cout << "Ошибка ввода времени!\n";
                             clearInputBuffer();
                         } else {
                             newEvent.plannedDuration.setTime(h, m, s);
                             updateActualDuration(newEvent);
                             schedule.push_back(newEvent);
                             cout << "\nМероприятие успешно добавлено!\n";
                         }
                     }
                 }
                 waitForEnter();
                 break;
             }
             case 2: {
                 int idx = selectEvent("\nВыберите мероприятие для редактирования:\n");
                 if (idx < 0) continue;
                 
                 Event& event = schedule[idx];
                 cout << "\nТекущее название: " << event.name << endl;
                 cout << "Введите новое название (Enter - оставить): ";
                 clearInputBuffer();
                 string newName;
                 getline(cin, newName);
                 if (!newName.empty()) event.name = newName;
                 
                 int h, m, s;
                 cout << "Введите новое время начала (часы минуты секунды): ";
                 cin >> h >> m >> s;
                 if (!cin.fail()) event.startTime.setTime(h, m, s);
                 
                 cout << "Введите новое время окончания (часы минуты секунды): ";
                 cin >> h >> m >> s;
                 if (!cin.fail()) event.endTime.setTime(h, m, s);
                 
                 cout << "Введите новую план. длительность (часы минуты секунды): ";
                 cin >> h >> m >> s;
                 if (!cin.fail()) event.plannedDuration.setTime(h, m, s);
                 
                 updateActualDuration(event);
                 cout << "\nМероприятие отредактировано!\n";
                 waitForEnter();
                 break;
             }
             case 3: {
                 int idx = selectEvent("\nВыберите мероприятие для удаления:\n");
                 if (idx >= 0) {
                     schedule.erase(schedule.begin() + idx);
                     cout << "\nМероприятие удалено!\n";
                 }
                 waitForEnter();
                 break;
             }
             case 4: {
                 if (schedule.empty()) {
                     cout << "\nРасписание пусто!\n";
                 } else {
                     cout << "\n=== ПОЛНОЕ РАСПИСАНИЕ ===\n\n";
                     for (size_t i = 0; i < schedule.size(); i++) {
                         cout << i + 1 << ". " << schedule[i].name << endl;
                         cout << "   Начало: ";
                         schedule[i].startTime.print();
                         cout << " | Конец: ";
                         schedule[i].endTime.print();
                         cout << endl;
                         cout << "   План: ";
                         schedule[i].plannedDuration.print();
                         cout << " | Факт: ";
                         schedule[i].actualDuration.print();
                         cout << endl << endl;
                     }
                 }
                 waitForEnter();
                 break;
             }
             case 0:
                 return;
             default:
                 cout << "Неверный выбор!\n";
                 waitForEnter();
                 break;
         }
     } while (choice != 0);
 }
 

// Пункт 2: Унарные операторы
void demonstrateUnaryOperators() {
    int idx = selectEvent("\nВыберите мероприятие для демонстрации унарных операторов:\n");
    if (idx < 0) return;
    
    int operatorChoice;
    do {
        system("clear");
        cout << "=== ДЕМОНСТРАЦИЯ УНАРНЫХ ОПЕРАТОРОВ ===\n\n";
        cout << "Мероприятие: " << schedule[idx].name << endl;
        cout << "Время начала: ";
        schedule[idx].startTime.print();
        cout << endl << endl;
        
        cout << "Выберите оператор:\n";
        cout << "1. Префиксный инкремент (++time)\n";
        cout << "2. Постфиксный инкремент (time++)\n";
        cout << "3. Префиксный декремент (--time)\n";
        cout << "4. Постфиксный декремент (time--)\n";
        cout << "0. Назад\n";
        cout << "Выберите: ";
        cin >> operatorChoice;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Ошибка ввода!\n";
            waitForEnter();
            continue;
        }
        
        Time& temp = schedule[idx].startTime; // Работаем непосредственно с временем мероприятия
        
        switch (operatorChoice) {
            case 1:
                cout << "\nПрефиксный инкремент:\n";
                cout << "До: ";
                temp.print();
                cout << "\nПосле ++: ";
                (++temp).print();
                cout << endl;
                waitForEnter();
                break;
            case 2:
                cout << "\nПостфиксный инкремент:\n";
                cout << "Значение до операции: ";
                temp.print();
                cout << "\nВозвращаемое значение: ";
                (temp++).print();
                cout << endl;
                waitForEnter();
                break;
            case 3:
                cout << "\nПрефиксный декремент:\n";
                cout << "До: ";
                temp.print();
                cout << "\nПосле --: ";
                (--temp).print();
                cout << endl;
                waitForEnter();
                break;
            case 4:
                cout << "\nПостфиксный декремент:\n";
                cout << "Значение до операции: ";
                temp.print();
                cout << "\nВозвращаемое значение: ";
                (temp--).print();
                cout << endl;
                waitForEnter();
                break;
            case 0:
                break;
            default:
                cout << "Неверный выбор!\n";
                waitForEnter();
                break;
        }
    } while (operatorChoice != 0);
}
 
 // Пункт 3: Арифметическое присваивание
 void demonstrateArithmeticAssignment() {
     int idx = selectEvent("\nВыберите мероприятие:\n");
     if (idx < 0) return;
     
     int choice;
     do {
         system("clear");
         cout << "=== АРИФМЕТИЧЕСКОЕ ПРИСВАИВАНИЕ ===\n\n";
         cout << "Мероприятие: " << schedule[idx].name << endl;
         cout << "Время начала: ";
         schedule[idx].startTime.print();
         cout << endl << endl;
         
         cout << "Выберите операцию:\n";
         cout << "1. Прибавить время (+=)\n";
         cout << "2. Вычесть время (-=)\n";
         cout << "3. Умножить (*=)\n";
         cout << "4. Разделить (/=)\n";
         cout << "0. Назад\n";
         cout << "Выберите: ";
         cin >> choice;
         
         if (cin.fail()) {
             clearInputBuffer();
             cout << "Ошибка ввода!\n";
             waitForEnter();
             continue;
         }
         
         switch (choice) {
             case 1: {
                 int h, m, s;
                 cout << "Введите время для прибавления (часы минуты секунды): ";
                 cin >> h >> m >> s;
                 if (cin.fail() || h < 0 || m < 0 || s < 0 || m >= 60 || s >= 60) {
                     cout << "Ошибка ввода!\n";
                     clearInputBuffer();
                 } else {
                     Time delta(h, m, s);
                     cout << "\nДо: ";
                     schedule[idx].startTime.print();
                     schedule[idx].startTime += delta;
                     cout << "\nПосле += ";
                     delta.print();
                     cout << ": ";
                     schedule[idx].startTime.print();
                     cout << endl;
                 }
                 waitForEnter();
                 break;
             }
             case 2: {
                 int h, m, s;
                 cout << "Введите время для вычитания (часы минуты секунды): ";
                 cin >> h >> m >> s;
                 if (cin.fail() || h < 0 || m < 0 || s < 0 || m >= 60 || s >= 60) {
                     cout << "Ошибка ввода!\n";
                     clearInputBuffer();
                 } else {
                     Time delta(h, m, s);
                     cout << "\nДо: ";
                     schedule[idx].startTime.print();
                     schedule[idx].startTime -= delta;
                     cout << "\nПосле -= ";
                     delta.print();
                     cout << ": ";
                     schedule[idx].startTime.print();
                     cout << endl;
                 }
                 waitForEnter();
                 break;
             }
             case 3: {
                 double scalar;
                 cout << "Введите скаляр: ";
                 cin >> scalar;
                 if (cin.fail()) {
                     cout << "Ошибка ввода!\n";
                     clearInputBuffer();
                 } else {
                     cout << "\nДо: ";
                     schedule[idx].startTime.print();
                     schedule[idx].startTime *= scalar;
                     cout << "\nПосле *= " << scalar << ": ";
                     schedule[idx].startTime.print();
                     cout << endl;
                 }
                 waitForEnter();
                 break;
             }
             case 4: {
                 double scalar;
                 cout << "Введите скаляр: ";
                 cin >> scalar;
                 if (cin.fail()) {
                     cout << "Ошибка ввода!\n";
                     clearInputBuffer();
                 } else if (scalar == 0) {
                     cout << "Ошибка: деление на ноль!\n";
                 } else {
                     cout << "\nДо: ";
                     schedule[idx].startTime.print();
                     schedule[idx].startTime /= scalar;
                     cout << "\nПосле /= " << scalar << ": ";
                     schedule[idx].startTime.print();
                     cout << endl;
                 }
                 waitForEnter();
                 break;
             }
             case 0:
                 break;
             default:
                 cout << "Неверный выбор!\n";
                 waitForEnter();
                 break;
         }
     } while (choice != 0);
 }
 
 // Пункт 4: Бинарные операторы
 void demonstrateBinaryOperators() {
     int idx1 = selectEvent("\nВыберите первое мероприятие:\n");
     if (idx1 < 0) return;
     
     int idx2 = selectEvent("\nВыберите второе мероприятие:\n");
     if (idx2 < 0) return;
     
     int choice;
     do {
         system("clear");
         cout << "=== БИНАРНЫЕ ОПЕРАТОРЫ ===\n\n";
         cout << schedule[idx1].name << " (начало): ";
         schedule[idx1].startTime.print();
         cout << endl;
         cout << schedule[idx2].name << " (начало): ";
         schedule[idx2].startTime.print();
         cout << endl << endl;
         
         cout << "Выберите операцию:\n";
         cout << "1. Сложение (time1 + time2)\n";
         cout << "2. Вычитание (time1 - time2)\n";
         cout << "3. Умножение на скаляр (time1 * scalar)\n";
         cout << "4. Деление на скаляр (time1 / scalar)\n";
         cout << "0. Назад\n";
         cout << "Выберите: ";
         cin >> choice;
         
         if (cin.fail()) {
             clearInputBuffer();
             cout << "Ошибка ввода!\n";
             waitForEnter();
             continue;
         }
         
         switch (choice) {
             case 1: {
                 Time result = schedule[idx1].startTime + schedule[idx2].startTime;
                 cout << "\nРезультат сложения: ";
                 result.print();
                 cout << endl;
                 waitForEnter();
                 break;
             }
             case 2: {
                 Time result = schedule[idx1].startTime - schedule[idx2].startTime;
                 cout << "\nРезультат вычитания: ";
                 result.print();
                 cout << endl;
                 waitForEnter();
                 break;
             }
             case 3: {
                 double scalar;
                 cout << "Введите скаляр: ";
                 cin >> scalar;
                 if (cin.fail()) {
                     cout << "Ошибка ввода!\n";
                     clearInputBuffer();
                 } else {
                     Time result = schedule[idx1].startTime * scalar;
                     cout << "\nРезультат умножения: ";
                     result.print();
                     cout << endl;
                 }
                 waitForEnter();
                 break;
             }
             case 4: {
                 double scalar;
                 cout << "Введите скаляр: ";
                 cin >> scalar;
                 if (cin.fail()) {
                     cout << "Ошибка ввода!\n";
                     clearInputBuffer();
                 } else if (scalar == 0) {
                     cout << "Ошибка: деление на ноль!\n";
                 } else {
                     Time result = schedule[idx1].startTime / scalar;
                     cout << "\nРезультат деления: ";
                     result.print();
                     cout << endl;
                 }
                 waitForEnter();
                 break;
             }
             case 0:
                 break;
             default:
                 cout << "Неверный выбор!\n";
                 waitForEnter();
                 break;
         }
     } while (choice != 0);
 }
 
 // Пункт 5: Операторы сравнения
 void demonstrateComparisonOperators() {
     int idx1 = selectEvent("\nВыберите первое мероприятие:\n");
     if (idx1 < 0) return;
     
     int idx2 = selectEvent("\nВыберите второе мероприятие:\n");
     if (idx2 < 0) return;
     
     system("clear");
     cout << "=== ОПЕРАТОРЫ СРАВНЕНИЯ ===\n\n";
     
     cout << schedule[idx1].name << " (начало): ";
     schedule[idx1].startTime.print();
     cout << endl;
     cout << schedule[idx2].name << " (начало): ";
     schedule[idx2].startTime.print();
     cout << endl << endl;
     
     cout << "Результаты сравнения:\n";
     cout << "time1 < time2:  " << (schedule[idx1].startTime < schedule[idx2].startTime ? "true" : "false") << endl;
     cout << "time1 > time2:  " << (schedule[idx1].startTime > schedule[idx2].startTime ? "true" : "false") << endl;
     cout << "time1 <= time2: " << (schedule[idx1].startTime <= schedule[idx2].startTime ? "true" : "false") << endl;
     cout << "time1 >= time2: " << (schedule[idx1].startTime >= schedule[idx2].startTime ? "true" : "false") << endl;
     cout << "time1 == time2: " << (schedule[idx1].startTime == schedule[idx2].startTime ? "true" : "false") << endl;
     cout << "time1 != time2: " << (schedule[idx1].startTime != schedule[idx2].startTime ? "true" : "false") << endl;
     
     waitForEnter();
 }
 
 // Пункт 6: Расписание и статистика
 void demonstrateScheduleAndStatic() {
     int choice;
     do {
         system("clear");
         cout << "=== РАСПИСАНИЕ И СТАТИСТИКА ===\n\n";
         cout << "1. Вывести полное расписание\n";
         cout << "2. Статистика программы\n";
         cout << "3. Посчитать интервал между мероприятиями\n";
         cout << "0. Назад\n";
         cout << "Выберите: ";
         cin >> choice;
         
         if (cin.fail()) {
             clearInputBuffer();
             cout << "Ошибка ввода!\n";
             waitForEnter();
             continue;
         }
         
         switch (choice) {
             case 1: {
                 if (schedule.empty()) {
                     cout << "\nРасписание пусто!\n";
                 } else {
                     cout << "\n=== ПОЛНОЕ РАСПИСАНИЕ ===\n\n";
                     for (size_t i = 0; i < schedule.size(); i++) {
                         cout << i + 1 << ". " << schedule[i].name << endl;
                         cout << "   Начало: ";
                         schedule[i].startTime.print();
                         cout << " | Конец: ";
                         schedule[i].endTime.print();
                         cout << endl;
                         cout << "   План: ";
                         schedule[i].plannedDuration.print();
                         cout << " | Факт: ";
                         schedule[i].actualDuration.print();
                         cout << endl;
                         
                         // Анализ разницы
                         Time diff = schedule[i].actualDuration - schedule[i].plannedDuration;
                         cout << "   Разница: ";
                         diff.print();
                         cout << " (";
                         if (schedule[i].actualDuration > schedule[i].plannedDuration) 
                             cout << "опоздание";
                         else if (schedule[i].actualDuration < schedule[i].plannedDuration)
                             cout << "ускорение";
                         else
                             cout << "точно";
                         cout << ")" << endl << endl;
                     }
                 }
                 waitForEnter();
                 break;
             }
             case 2: {
                 system("clear");
                 cout << "=== СТАТИСТИКА ===\n\n";
                 cout << "Всего мероприятий: " << schedule.size() << endl;
                 cout << "Всего операций с Time: " << Time::getOperationCount() << endl;
                 waitForEnter();
                 break;
             }
             case 3: {
                 int idx1 = selectEvent("\nВыберите первое мероприятие:\n");
                 if (idx1 < 0) break;
                 
                 int idx2 = selectEvent("\nВыберите второе мероприятие:\n");
                 if (idx2 < 0) break;
                 
                 cout << "\nИнтервал между мероприятиями:\n";
                 cout << "Конец \"" << schedule[idx1].name << "\": ";
                 schedule[idx1].endTime.print();
                 cout << endl;
                 cout << "Начало \"" << schedule[idx2].name << "\": ";
                 schedule[idx2].startTime.print();
                 cout << endl;
                 
                 Time interval = schedule[idx2].startTime - schedule[idx1].endTime;
                 if (interval.getTotalSeconds() < 0) {
                     interval += Time(24, 0, 0); // Добавляем сутки если нужно
                 }
                 
                 cout << "Интервал: ";
                 interval.print();
                 cout << endl;
                 waitForEnter();
                 break;
             }
             case 0:
                 break;
             default:
                 cout << "Неверный выбор!\n";
                 waitForEnter();
                 break;
         }
     } while (choice != 0);
 }
 
 // ГЛАВНАЯ ФУНКЦИЯ
 int main() {
     int choice;
     
     do {
         system("clear");
         cout << "=== ПРОГРАММА \"РАСПИСАНИЕ НА ДЕНЬ\" ===\n";
         cout << "1. Создать/изменить мероприятия\n";
         cout << "2. Демонстрация унарных операторов\n";
         cout << "3. Демонстрация арифметического присваивания\n";
         cout << "4. Демонстрация бинарных операторов\n";
         cout << "5. Демонстрация операторов сравнения\n";
         cout << "6. Расписание и статистика\n";
         cout << "0. Выход\n";
         cout << "Выберите действие: ";
         cin >> choice;
         
         if (cin.fail()) {
             clearInputBuffer();
             cout << "Ошибка ввода. Введите число.\n";
             waitForEnter();
             continue;
         }
         
         switch (choice) {
             case 1:
                 manageSchedule();
                 break;
             case 2:
                 demonstrateUnaryOperators();
                 break;
             case 3:
                 demonstrateArithmeticAssignment();
                 break;
             case 4:
                 demonstrateBinaryOperators();
                 break;
             case 5:
                 demonstrateComparisonOperators();
                 break;
             case 6:
                 demonstrateScheduleAndStatic();
                 break;
             case 0:
                 cout << "Выход из программы...\n";
                 break;
             default:
                 cout << "Неверный выбор! Попробуйте снова.\n";
                 waitForEnter();
                 break;
         }
     } while (choice != 0);
     
     return 0;
 }