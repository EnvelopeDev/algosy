// Пополнение и использование библиотеки фигур
//#include "pch.h"	//связь с ОС (пример для Visual C++2017)
#include <locale.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "shape.h"

class h_circle : public rotatable, public reflectable {
public:
    double angle;          // угол поворота: 0, 90, 180, 270
    point center;
    int radius;
    
    h_circle(point a, int rd) : center(a), radius(rd), angle(0) {}
    
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
    }
    
    void resize(double factor) override {
        radius = static_cast<int>(radius * factor);
    }
    
    void flip_horisontally() {
        if (angle < M_PI) {
            angle = M_PI - angle;
        } else {
            angle = 3*M_PI - angle;
        }
    }
    
    void flip_vertically() {
        angle = 2*M_PI - angle;
    }
    
    void rotate_right() {
        angle -= M_PI_2;
        if (angle < 0) angle += 2*M_PI;
    }
    
    void rotate_left() {
        angle += M_PI_2;
        if (angle >= 2*M_PI) angle -= 2*M_PI;
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
int main( ) 
{   setlocale(LC_ALL, "Rus");
	screen_init( );
//== 1. Объявление набора фигур ==
	rectangle hat(point(0, 0), point(14, 5));
	line brim(point(20,9),17);
	h_circle earL(point(30, 5), 2);
	h_circle earR(point(40, 5), 2);
	h_circle tie(point(50, 5), 2);
	h_circle shishak(point(60, 5), 2);
	myshape face(point(15,10), point(27,18));
	shape_refresh( );
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор
//== 2. Подготовка к сборке ==
	earL.rotate_left();
	earR.rotate_right();
	tie.flip_horisontally();
	hat.rotate_right( );
	earL.resize(1.4);
	earR.resize(1.4);
	shishak.resize(1.5);
	tie.resize(1.3);
	brim.resize(2.0);
	face.resize(1.2);
    shape_refresh( );
	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений
//== 3. Сборка изображения ==
//	face.move(0, -10); // Лицо – в исходное положение (если нужно!)
	up(brim, face);
	up(hat, brim);
	up_center(shishak, hat);
	down_center(tie, face);
	right_center(earR, face);
	left_center(earL, face);
	shape_refresh( );
	std::cout << "=== Ready! ===\n";
	std::cin.get();       //Смотреть результат
	screen_destroy( );
}