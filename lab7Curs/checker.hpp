#pragma once
#include "bmask_set.hpp"
#include "generator.hpp"
#include "sequence.hpp"
#include "HashTable.hpp"
#include <chrono>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

class Checker {
private:
    Generator gen;
    std::ofstream resultsFile;
    std::vector<std::pair<int, double>> measurements;
    
    // Структура для статистики
    struct Stats {
        double mean;
        double variance;
        double stddev;
        size_t count;
    };
    
    // Измерение времени одной цепочки
    double measureSingleRun(int power);
    
    // Измерение с усреднением (repeat раз)
    double measureAveraged(int power, int repeats = 10);
    
    // Сохранение в файл
    void saveMeasurements(const std::string& filename);
    
public:
    Checker();
    ~Checker();
    
    // Запуск полного эксперимента
    void runExperiment(int minPower = 10, int maxPower = 200, int step = 10, int repeats = 10);
    // Регрессионный анализ (упрощённый)
    void performRegressionAnalysis();
    // Вывод результатов на экран
    void printResults();
    
    // Экспорт для RG41
    void exportForRG41(const std::string& filename = "in.txt");
    
    // Дополнительно: проверка корректности операций
    void validateOperations();
};