#include "checker.hpp"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    
    Checker exp;
    
    // 1. Проверка корректности
    exp.validateOperations();
    
    // 2. Запуск эксперимента
    std::cout << "\nStart experiment? (y/n): ";
    char answer;
    std::cin >> answer;
    
    if (answer == 'y' || answer == 'Y') {
        // Параметры эксперимента
        int minPower = 10;      // минимальная мощность
        int maxPower = 200;     // максимальная мощность
        int step = 10;          // шаг
        int repeats = 15;       // повторений для каждой мощности
        
        exp.runExperiment(minPower, maxPower, step, repeats);
        
        // 3. Вывод результатов
        exp.printResults();
        
        // 4. Регрессионный анализ
        exp.performRegressionAnalysis();
        
        // 5. Экспорт для RG41
        exp.exportForRG41("in.txt");
    }
    
    std::cout << "\nProgram finished. Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();
    
    return 0;
}