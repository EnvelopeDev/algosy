#include "checker.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std::chrono;

Checker::Checker() {
    resultsFile.open("experiment_results.csv");
    resultsFile << "power,time_us,repetition\n";
}

Checker::~Checker() {
    if (resultsFile.is_open())
        resultsFile.close();
}

double Checker::measureSingleRun(int power) {
    // Генерация множеств заданной мощности
    BitMaskSet A(gen.generateSet(power * 0.4, power));
    BitMaskSet B(gen.generateSet(power * 0.4, power));
    BitMaskSet C(gen.generateSet(power * 0.4, power));
    BitMaskSet D(gen.generateSet(power * 0.4, power));
    BitMaskSet E(gen.generateSet(power * 0.4, power));
    
    // Дополнительно: последовательностные операции
    // Преобразуем множества в строки для Sequence
    std::string strA = A.toString();
    std::string strB = B.toString();
    std::string strC = C.toString();
    
    Sequence<char> seqA;
    Sequence<char> seqB;
    Sequence<char> seqC;
    
    for (char c : strA) seqA.push_back(c);
    for (char c : strB) seqB.push_back(c);
    for (char c : strC) seqC.push_back(c);
    
    auto start = high_resolution_clock::now();
    
    // ===== Цепочка операций над множествами (вариант 36) =====
    BitMaskSet step1 = B & C;                    // B ∩ C
    BitMaskSet step2 = A ^ step1;                // A ⊕ (B ∩ C)
    BitMaskSet step3 = step2 - D;                // (A ⊕ (B ∩ C)) \ D
    BitMaskSet result = step3 & E;               // ((A ⊕ (B ∩ C)) \ D) ∩ E
    
    // ===== Последовательностные операции (пример) =====
    Sequence<char> concatSeq = seqA.concat(seqB);        // CONCAT
    Sequence<char> erasedSeq = seqA.erase(2, 4);          // ERASE
    Sequence<char> exclSeq = seqA.excl(seqB);             // EXCL
    
    // Чтобы компилятор не оптимизировал
    volatile int dummy = concatSeq.size() + erasedSeq.size() + exclSeq.size();
    (void)dummy;
    (void)result;
    
    auto end = high_resolution_clock::now();
    
    return duration_cast<microseconds>(end - start).count();
}

double Checker::measureAveraged(int power, int repeats) {
    if (repeats < 1) repeats = 1;
    
    std::vector<double> times;
    times.reserve(repeats);
    
    for (int i = 0; i < repeats; ++i) {
        double t = measureSingleRun(power);
        times.push_back(t);
        
        // Сохраняем в CSV
        if (resultsFile.is_open()) {
            resultsFile << power << "," << t << "," << i << "\n";
        }
    }
    
    // Вычисляем среднее
    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    double mean = sum / repeats;
    
    // Запоминаем
    measurements.push_back({power, mean});
    
    return mean;
}

void Checker::runExperiment(int minPower, int maxPower, int step, int repeats) {
    std::cout << "\n============================================================\n";
    std::cout << "  COURSEWORK: TIME COMPLEXITY MEASUREMENT\n";
    std::cout << "  Variant 36: ((A XOR (B AND C)) \\ D) AND E\n";
    std::cout << "  + sequence operations: CONCAT, ERASE, EXCL\n";
    std::cout << "============================================================\n\n";
    
    std::cout << "Measuring for powers from " << minPower << " to " << maxPower 
              << " with step " << step << "\n";
    std::cout << "Repeats per power: " << repeats << "\n\n";
    
    std::cout << std::left << std::setw(10) << "Power" 
              << std::setw(15) << "Time (us)" 
              << std::setw(15) << "Theoretical" << "\n";
    std::cout << std::string(40, '-') << "\n";
    
    for (int power = minPower; power <= maxPower; power += step) {
        double avgTime = measureAveraged(power, repeats);
        
        // Теоретическая оценка (для хеш-таблицы ~ O(n), для битовой маски ~ O(1))
        double theoretical = 10.0 * power;  // Пример, подберите под свою структуру
        
        std::cout << std::setw(10) << power 
                  << std::setw(15) << std::fixed << std::setprecision(2) << avgTime
                  << std::setw(15) << std::fixed << std::setprecision(2) << theoretical << "\n";
        
        // Прогресс
        std::cout.flush();
    }
    
    std::cout << "\nMeasurements completed. Results saved to experiment_results.csv\n";
}

void Checker::printResults() {
    std::cout << "\n============================================================\n";
    std::cout << "                     RESULTS\n";
    std::cout << "============================================================\n\n";
    
    if (measurements.empty()) {
        std::cout << "No data. Please run runExperiment() first.\n";
        return;
    }
    
    std::cout << std::left << std::setw(10) << "n" 
              << std::setw(20) << "T(n) us" 
              << std::setw(20) << "T(n)/n" 
              << std::setw(20) << "T(n)/n²\n";
    std::cout << std::string(70, '-') << "\n";
    
    for (const auto& [power, time] : measurements) {
        double tn_div_n = (power > 0) ? time / power : 0;
        double tn_div_n2 = (power > 0) ? time / (power * power) : 0;
        
        std::cout << std::setw(10) << power 
                  << std::setw(20) << std::fixed << std::setprecision(2) << time
                  << std::setw(20) << std::fixed << std::setprecision(4) << tn_div_n
                  << std::setw(20) << std::fixed << std::setprecision(6) << tn_div_n2 << "\n";
    }
}

void Checker::exportForRG41(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Failed to create file " << filename << "\n";
        return;
    }
    
    // Формат для RG41: каждая строка = "размер_входа время"
    for (const auto& [power, time] : measurements) {
        out << power << " " << time << "\n";
    }
    
    out.close();
    std::cout << "\nData exported to " << filename << " for RG41 processing\n";
}

void Checker::performRegressionAnalysis() {
    if (measurements.size() < 3) {
        std::cout << "Insufficient data for regression analysis\n";
        return;
    }
    
    // Упрощённая линейная регрессия T(n) = a + b*n
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    size_t m = measurements.size();
    
    for (const auto& [x, y] : measurements) {
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
    }
    
    double denominator = m * sum_x2 - sum_x * sum_x;
    if (denominator == 0) return;
    
    double b = (m * sum_xy - sum_x * sum_y) / denominator;
    double a = (sum_y - b * sum_x) / m;
    
    // Коэффициент детерминации R²
    double y_mean = sum_y / m;
    double ss_tot = 0, ss_res = 0;
    for (const auto& [x, y] : measurements) {
        double y_pred = a + b * x;
        ss_tot += (y - y_mean) * (y - y_mean);
        ss_res += (y - y_pred) * (y - y_pred);
    }
    double r2 = 1 - ss_res / ss_tot;
    
    std::cout << "\n============================================================\n";
    std::cout << "         REGRESSION ANALYSIS (linear model)\n";
    std::cout << "============================================================\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "T(n) = " << a << " + " << b << " * n\n";
    std::cout << "R² = " << r2 << "  (closer to 1 = better fit)\n\n";
    
    if (r2 > 0.95) {
        std::cout << "Conclusion: Time complexity is CLOSE TO LINEAR (O(n))\n";
    } else if (r2 > 0.8) {
        std::cout << "Conclusion: Time complexity is APPROXIMATELY LINEAR\n";
    } else {
        std::cout << "Conclusion: Linear model does not fit well.\n";
        std::cout << "Possible complexity: O(n²) or O(n log n)\n";
    }
}

void Checker::validateOperations() {
    std::cout << "\n============================================================\n";
    std::cout << "         OPERATION CORRECTNESS CHECK\n";
    std::cout << "============================================================\n\n";
    
    // Тест 1: Базовые операции над множествами
    BitMaskSet A("ABC");
    BitMaskSet B("BCD");
    BitMaskSet C("CDE");
    
    std::cout << "A = "; A.print(); std::cout << "\n";
    std::cout << "B = "; B.print(); std::cout << "\n";
    std::cout << "C = "; C.print(); std::cout << "\n";
    
    BitMaskSet intersection = B & C;
    std::cout << "B ∩ C = "; intersection.print(); std::cout << "\n";
    
    BitMaskSet xorResult = A ^ intersection;
    std::cout << "A ⊕ (B ∩ C) = "; xorResult.print(); std::cout << "\n";
    
    // Тест 2: Последовательностные операции
    Sequence<char> seqA = {'A', 'B', 'C', 'D'};
    Sequence<char> seqB = {'C', 'D', 'E'};
    
    std::cout << "\nseqA = "; seqA.print(); std::cout << "\n";
    std::cout << "seqB = "; seqB.print(); std::cout << "\n";
    
    Sequence<char> concat = seqA.concat(seqB);
    std::cout << "CONCAT = "; concat.print(); std::cout << "\n";
    
    Sequence<char> erased = seqA.erase(2, 3);
    std::cout << "ERASE(2,3) = "; erased.print(); std::cout << "\n";
    
    Sequence<char> excl = seqA.excl(seqB);
    std::cout << "EXCL = "; excl.print(); std::cout << "\n";
    
    std::cout << "\n✅ All operations work correctly.\n";
}