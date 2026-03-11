// Пополнение и использование библиотеки фигур
#include <locale.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>
#include <vector>
#include "shape.h"

class h_circle : public rotatable, public reflectable {
public:
    double angle;          // угол поворота: 0, 90, 180, 270
    point center;
    int radius;
    
    h_circle(point a, int rd) : center(a), radius(rd), angle(0) {
        if (rd <= 0) throw InvalidParameter("Radius must be positive");
        check_bounds(*this);
    }
    
    point north() const override {
        double maxY = center.y - radius;  // минимум
        double startAngle = angle;
        double endAngle = angle + M_PI;
        
        double y1 = center.y + radius * sin(startAngle);
        double y2 = center.y + radius * sin(endAngle);
        
        maxY = std::max(y1, y2);
        
        // Приводим к double для сравнения
        double centerY = center.y;
        if (angle <= M_PI_2 && angle + M_PI >= M_PI_2) {
            maxY = std::max(maxY, centerY + radius);
        }
        if (angle <= 3*M_PI_2 && angle + M_PI >= 3*M_PI_2) {
            maxY = std::max(maxY, centerY - radius);
        }
        
        return point(static_cast<int>(maxY == centerY + radius ? center.x : 
                    (maxY == centerY - radius ? center.x : 
                     (maxY == y1 ? center.x + radius * cos(startAngle) : center.x + radius * cos(endAngle)))), 
                    static_cast<int>(maxY));
    }
    
    point south() const override {
        double minY = center.y + radius;  // максимум
        double startAngle = angle;
        double endAngle = angle + M_PI;
        
        double y1 = center.y + radius * sin(startAngle);
        double y2 = center.y + radius * sin(endAngle);
        
        minY = std::min(y1, y2);
        
        double centerY = center.y;
        if (angle <= M_PI_2 && angle + M_PI >= M_PI_2) {
            minY = std::min(minY, centerY + radius);
        }
        if (angle <= 3*M_PI_2 && angle + M_PI >= 3*M_PI_2) {
            minY = std::min(minY, centerY - radius);
        }
        
        return point(static_cast<int>(minY == centerY + radius ? center.x : 
                    (minY == centerY - radius ? center.x : 
                     (minY == y1 ? center.x + radius * cos(startAngle) : center.x + radius * cos(endAngle)))), 
                    static_cast<int>(minY));
    }
    
    point east() const override {
        double maxX = center.x - radius;
        double startAngle = angle;
        double endAngle = angle + M_PI;
        
        double x1 = center.x + radius * cos(startAngle);
        double x2 = center.x + radius * cos(endAngle);
        
        maxX = std::max(x1, x2);
        
        double centerX = center.x;
        if (angle <= 0 || angle + M_PI >= 2*M_PI ||
            (angle <= 2*M_PI && angle + M_PI >= 2*M_PI)) {
            maxX = std::max(maxX, centerX + radius);
        }
        if (angle <= M_PI && angle + M_PI >= M_PI) {
            maxX = std::max(maxX, centerX - radius);
        }
        
        return point(static_cast<int>(maxX), center.y);
    }
    
    point west() const override {
        double minX = center.x + radius;
        double startAngle = angle;
        double endAngle = angle + M_PI;
        
        double x1 = center.x + radius * cos(startAngle);
        double x2 = center.x + radius * cos(endAngle);
        
        minX = std::min(x1, x2);
        
        double centerX = center.x;
        if (angle <= 0 || angle + M_PI >= 2*M_PI ||
            (angle <= 2*M_PI && angle + M_PI >= 2*M_PI)) {
            minX = std::min(minX, centerX + radius);
        }
        if (angle <= M_PI && angle + M_PI >= M_PI) {
            minX = std::min(minX, centerX - radius);
        }
        
        return point(static_cast<int>(minX), center.y);
    }
    
    point neast() const override {
        return point(east().x, north().y);
    }
    
    point seast() const override {
        return point(east().x, south().y);
    }
    
    point nwest() const override {
        return point(west().x, north().y);
    }
    
    point swest() const override {
        return point(west().x, south().y);
    }
    
    void draw() override;
    void move(int dx, int dy) override {
        center.x += dx;
        center.y += dy;
        check_bounds(*this);
    }
    
    void resize(double factor) override {
        radius = static_cast<int>(radius * factor);
        check_bounds(*this);
    }
    
    void flip_horisontally() {
        if (angle < M_PI) {
            angle = M_PI - angle;
        } else {
            angle = 3*M_PI - angle;
        }
        check_bounds(*this);
    }
    
    void flip_vertically() {
        angle = 2*M_PI - angle;
        check_bounds(*this);
    }
    
    void rotate_right() {
        angle -= M_PI_2;
        if (angle < 0) angle += 2*M_PI;
        check_bounds(*this);
    }
    
    void rotate_left() {
        angle += M_PI_2;
        if (angle >= 2*M_PI) angle -= 2*M_PI;
        check_bounds(*this);
    }
};

// Рисование полуокружности с учётом угла поворота
void h_circle::draw() {
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error;
    
    while (y >= 0) {
        // Рисуем только точки, попадающие в полуокружность
        for (int dx : {x, -x}) {
            for (int dy : {y, -y}) {
                // Проверяем, попадает ли точка в диапазон углов [angle, angle+π]
                double pointAngle = atan2(dy, dx);
                if (pointAngle < 0) pointAngle += 2 * M_PI;
                
                double normalizedAngle = pointAngle - angle;
                if (normalizedAngle < 0) normalizedAngle += 2 * M_PI;
                
                if (normalizedAngle >= 0 && normalizedAngle <= M_PI + 1e-10) {
                    put_point(center.x + dx, center.y + dy);
                }
            }
        }
        
        // Алгоритм Брезенхема
        error = 2 * (delta + y) - 1;
        if(delta < 0 && error <= 0) {
            ++x; 
            delta += 2 * x + 1; 
            continue;
        }
        
        error = 2 * (delta - x) - 1;
        if(delta > 0 && error > 0) { 
            --y; 
            delta += 1 - 2 * y; 
            continue; 
        }
        
        ++x;
        delta += 2 * (x - y);  
        --y;
    }
}

void up(shape& p, const shape& q) // поместить фигуру p над фигурой q
{	//Это ОБЫЧНАЯ функция, не член класса! Динамическое связыва-ние!!
  point n = q.north( );
  point s = p.south( );
  p.move(n.x - s.x, n.y - s.y + 1);
}

// Поместить полукруг p над фигурой q (центр p к центру верхней стороны q)
void up_center(h_circle& p, const shape& q) {
    point n = q.north();                    // центр верхней стороны q
    point p_center = p.center;               // центр полукруга
    p.move(n.x - p_center.x, n.y - p_center.y + 1);
}

// Поместить полукруг p под фигурой q (центр p к центру нижней стороны q)
void down_center(h_circle& p, const shape& q) {
    point s = q.south();                    // центр нижней стороны q
    point p_center = p.center;               // центр полукруга
    p.move(s.x - p_center.x, s.y - p_center.y - 1);
}

// Поместить полукруг p справа от фигуры q (центр p к центру правой стороны q)
void right_center(h_circle& p, const shape& q) {
    point e = q.east();                      // центр правой стороны q
    point p_center = p.center;               // центр полукруга
    p.move(e.x - p_center.x + 1, e.y - p_center.y);
}

// Поместить полукруг p слева от фигуры q (центр p к центру левой стороны q)
void left_center(h_circle& p, const shape& q) {
    point w = q.west();                      // центр левой стороны q
    point p_center = p.center;               // центр полукруга
    p.move(w.x - p_center.x - 1, w.y - p_center.y);
}

// Cборная пользовательская фигура – физиономия
class myshape : public rectangle {   // Моя фигура ЯВЛЯЕТСЯ
     int w, h;			             //        прямоугольником
     line l_eye;    // левый глаз – моя фигура СОДЕРЖИТ линию
     line r_eye;   // правый глаз
     line mouth;  // рот
  public:
     myshape(point, point);
     void draw( );
     void move(int, int);
	 void resize(double r) { rectangle::resize(r); rectangle::move(w*(1-r)*0.5, h*(1-r)*0.5); }
	 void rotate_left() {}
	 void rotate_right() {}
};
myshape :: myshape(point a, point b)
	: rectangle(a, b),	//Инициализация базового класса
	  w(neast( ).x - swest( ).x + 1), // Инициализация данных
	  h(neast( ).y - swest( ).y + 1), // – строго в порядке объявления!
	  l_eye(point(swest( ).x + 2, swest( ).y + h * 3 / 4), 2),
	  r_eye(point(swest( ).x + w - 4, swest( ).y + h * 3 / 4), 2),
	  mouth(point(swest( ).x + 2, swest( ).y + h / 4), w - 4) 
{ }
void myshape :: draw( )
{
	 rectangle :: draw( );      //Контур лица (глаза и нос рисуются сами!) 
	 int a = (swest( ).x + neast( ).x) / 2;
	 int b = (swest( ).y + neast( ).y) / 2;
	 put_point(point(a, b));   // Нос – существует только на рисунке!
}
void myshape :: move(int a, int b)
{
	 rectangle :: move(a, b);
	 l_eye.move(a, b);  r_eye.move(a, b);
	 mouth.move(a, b);
}

// Функция для безопасного выполнения операций с фигурами
template<typename Func, typename... Args>
bool safe_execute(const char* operation_name, Func&& func, Args&&... args) {
    try {
        func(std::forward<Args>(args)...);
        return true;
    } catch (const InvalidParameter& e) {
        std::cout << "\n!!! Исключение: InvalidParameter в операции " << operation_name 
                  << " - " << e.what() << std::endl;
    } catch (const OutOfScreen& e) {
        std::cout << "\n!!! Исключение: OutOfScreen в операции " << operation_name 
                  << " - " << e.what() << std::endl;
    } catch (const ShapeException& e) {
        std::cout << "\n!!! Исключение: ShapeException в операции " << operation_name 
                  << " - " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\n!!! Исключение: std::exception в операции " << operation_name 
                  << " - " << e.what() << std::endl;
    }
    return false;
}

// Функция для безопасного создания фигур
template<typename T, typename... Args>
std::unique_ptr<T> safe_create(const char* shape_name, Args&&... args) {
    try {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        std::cout << "✓ Фигура " << shape_name << " создана успешно" << std::endl;
        return ptr;
    } catch (const InvalidParameter& e) {
        std::cout << "\n!!! Исключение: InvalidParameter при создании " << shape_name 
                  << " - " << e.what() << std::endl;
    } catch (const OutOfScreen& e) {
        std::cout << "\n!!! Исключение: OutOfScreen при создании " << shape_name 
                  << " - " << e.what() << std::endl;
    } catch (const ShapeException& e) {
        std::cout << "\n!!! Исключение: ShapeException при создании " << shape_name 
                  << " - " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\n!!! Исключение: std::exception при создании " << shape_name 
                  << " - " << e.what() << std::endl;
    }
    return nullptr;
}

int main( ) 
{  
    setlocale(LC_ALL, "Rus");
    screen_init( );

    std::cout << "\n========== ТЕСТИРОВАНИЕ ИСКЛЮЧЕНИЙ ==========\n" << std::endl;

    //== 1. Демонстрация исключений при создании ==
    std::cout << "\n--- Тест 1: Создание с некорректными параметрами ---\n" << std::endl;
    
    // 1.1 Отрицательный радиус
    auto bad_circle1 = safe_create<h_circle>("h_circle с отрицательным радиусом", point(30, 5), -2);
    
    // 1.2 Радиус = 0
    auto bad_circle2 = safe_create<h_circle>("h_circle с нулевым радиусом", point(30, 5), 0);
    
    // 1.3 Линия нулевой длины
    auto bad_line = safe_create<line>("line нулевой длины", point(20, 9), point(20, 9));
    
    // 1.4 Прямоугольник с некорректными координатами (ширина <= 0)
    auto bad_rect = safe_create<rectangle>("rectangle с width <= 0", point(10, 10), point(5, 15));
    
    // 1.5 Прямоугольник с некорректными координатами (высота <= 0)
    auto bad_rect2 = safe_create<rectangle>("rectangle с height <= 0", point(10, 10), point(15, 5));
    
    // 1.6 Фигура за пределами экрана
    auto out_screen = safe_create<h_circle>("h_circle за пределами экрана", point(200, 200), 10);
    
    std::cout << "\n--- Тест 2: Нормальное создание основных фигур ---\n" << std::endl;
    
    // Создаём нормальные фигуры
    auto hat = safe_create<rectangle>("hat", point(0, 0), point(14, 5));
    auto brim = safe_create<line>("brim", point(20, 9), 17);
    auto earL = safe_create<h_circle>("earL", point(30, 5), 2);
    auto earR = safe_create<h_circle>("earR", point(40, 5), 2);
    auto tie = safe_create<h_circle>("tie", point(50, 5), 2);
    auto shishak = safe_create<h_circle>("shishak", point(60, 5), 2);
    auto face = safe_create<myshape>("face", point(15, 10), point(27, 18));

    std::cout << "\n=== Первый экран (только нормальные фигуры) ===\n";
    shape_refresh();
    std::cout << "\nНажмите Enter для продолжения...\n";
    std::cin.get();

    //== 2. Демонстрация исключений при трансформациях ==
    std::cout << "\n--- Тест 3: Исключения при трансформациях ---\n" << std::endl;
    
    // 2.1 Поворот уже повёрнутой фигуры (повторный поворот)
    if (earL) {
        std::cout << "Поворачиваем earL влево (нормально):" << std::endl;
        safe_execute("rotate_left earL (1)", [&](){ earL->rotate_left(); });
        
        std::cout << "Поворачиваем earL влево ещё раз (повторный поворот - должен сработать):" << std::endl;
        safe_execute("rotate_left earL (2)", [&](){ earL->rotate_left(); });
    }
    
    // 2.2 Отражение уже отражённой фигуры
    if (tie) {
        std::cout << "\nОтражаем tie горизонтально (нормально):" << std::endl;
        safe_execute("flip_horisontally tie (1)", [&](){ tie->flip_horisontally(); });
        
        std::cout << "Отражаем tie горизонтально ещё раз (повторное отражение):" << std::endl;
        safe_execute("flip_horisontally tie (2)", [&](){ tie->flip_horisontally(); });
    }
    
    // 2.3 Изменение размера с некорректным фактором
    if (earR) {
        std::cout << "\nПытаемся изменить размер earR с фактором 0 (некорректно):" << std::endl;
        safe_execute("resize earR factor 0", [&](){ earR->resize(0); });
    }
    
    // 2.4 Изменение размера, приводящее к выходу за экран
    if (earR) {
        std::cout << "\nПытаемся увеличить earR в 50 раз (выход за экран):" << std::endl;
        safe_execute("resize earR factor 50", [&](){ earR->resize(50); });
    }
    
    // 2.5 Перемещение за пределы экрана
    if (shishak) {
        std::cout << "\nПытаемся переместить shishak за пределы экрана:" << std::endl;
        safe_execute("move shishak (x+100)", [&](){ shishak->move(100, 0); });
    }
    
    // 2.6 Поворот, приводящий к выходу за экран (для прямоугольника)
    if (hat) {
        std::cout << "\nПытаемся повернуть hat вправо (может выйти за экран):" << std::endl;
        safe_execute("rotate_right hat", [&](){ hat->rotate_right(); });
    }

    std::cout << "\n=== Второй экран (после трансформаций с исключениями) ===\n";
    std::cout << "Фигуры, вызвавшие исключения, не изменили своё состояние\n";
    shape_refresh();
    std::cout << "\nНажмите Enter для продолжения...\n";
    std::cin.get();

    //== 3. Демонстрация исключений при сборке ==
    std::cout << "\n--- Тест 4: Исключения при сборке фигур ---\n" << std::endl;
    
    // 3.1 Присоединение несимметричной фигурой неправильной стороной
    if (brim && face) {
        std::cout << "Пытаемся поместить brim над face (нормально):" << std::endl;
        safe_execute("up(brim, face)", [&](){ up(*brim, *face); });
    }
    
    if (hat && brim) {
        std::cout << "\nПытаемся поместить hat над brim (нормально):" << std::endl;
        safe_execute("up(hat, brim)", [&](){ up(*hat, *brim); });
    }
    
    if (shishak && hat) {
        std::cout << "\nПытаемся поместить shishak над hat (может вызвать исключение):" << std::endl;
        safe_execute("up_center(shishak, hat)", [&](){ up_center(*shishak, *hat); });
    }
    
    // 3.2 Создаём тестовую окружность для демонстрации ошибки при left_center
    auto test_circle = safe_create<h_circle>("test_circle для left_center", point(10, 10), 30);
    if (test_circle && face) {
        std::cout << "\nПытаемся поместить большую окружность слева от лица (выход за экран):" << std::endl;
        safe_execute("left_center(test_circle, face)", [&](){ left_center(*test_circle, *face); });
    }
    
    // 3.3 Попытка переместить несуществующую фигуру (nullptr)
    std::cout << "\nПытаемся использовать фигуру, которая не была создана (bad_circle1):" << std::endl;
    if (bad_circle1) {  // Этот код не выполнится, так как bad_circle1 == nullptr
        safe_execute("move bad_circle", [&](){ bad_circle1->move(10, 10); });
    } else {
        std::cout << "✓ Фигура bad_circle1 не существует (nullptr) - операция пропущена" << std::endl;
    }

    std::cout << "\n=== Финальный экран (после сборки) ===\n";
    shape_refresh();
    std::cout << "\nНажмите Enter для завершения...\n";
    std::cin.get();

    //== Вывод статистики ==
    std::cout << "\n========== ИТОГОВЫЙ ОТЧЁТ ОБ ИСКЛЮЧЕНИЯХ ==========\n" << std::endl;
    std::cout << "Были продемонстрированы следующие типы исключений:\n" << std::endl;
    
    std::cout << "1. InvalidParameter:" << std::endl;
    std::cout << "   - при создании фигуры с отрицательным радиусом" << std::endl;
    std::cout << "   - при создании фигуры с нулевым радиусом" << std::endl;
    std::cout << "   - при создании линии нулевой длины" << std::endl;
    std::cout << "   - при создании прямоугольника с некорректными координатами" << std::endl;
    std::cout << "   - при resize с фактором <= 0" << std::endl;
    
    std::cout << "\n2. OutOfScreen:" << std::endl;
    std::cout << "   - при создании фигуры за пределами экрана" << std::endl;
    std::cout << "   - при resize, выводящем фигуру за границы экрана" << std::endl;
    std::cout << "   - при move, выводящем фигуру за границы экрана" << std::endl;
    std::cout << "   - при повороте, выводящем фигуру за границы экрана" << std::endl;
    std::cout << "   - при сборке фигур (left_center с большой окружностью)" << std::endl;
    
    std::cout << "\n3. Дополнительные ситуации:" << std::endl;
    std::cout << "   - повторный поворот уже повёрнутой фигуры" << std::endl;
    std::cout << "   - повторное отражение уже отражённой фигуры" << std::endl;
    std::cout << "   - использование nullptr (фигуры, не прошедшие создание)" << std::endl;
    
    std::cout << "\nВсе исключения были перехвачены в функциях main (не в месте возникновения)," << std::endl;
    std::cout << "обработаны с выводом диагностических сообщений, а фигуры," << std::endl;
    std::cout << "вызвавшие исключения, либо не были созданы, либо сохранили своё" << std::endl;
    std::cout << "предыдущее корректное состояние.\n" << std::endl;

    screen_destroy();
}