// Пополнение и использование библиотеки фигур
//#include "pch.h"	//связь с ОС (пример для Visual C++2017)
#include <locale.h>
#include <iostream>
#include <cmath>
#include "shape.h"

class h_circle : public rectangle, public reflectable {
public:
    double angle;          // угол поворота: 0, 90, 180, 270
    point center;
    int radius;
    h_circle(point a, int rd) : rectangle(point(a.x-rd, a.y), point(a.x+rd, a.y+rd*0.7+1)) {
        angle = 0;
        center=a;
        radius=rd;
    }
    
    void draw();
    void flip_horisontally();
    void flip_vertically();
    void rotate_right();
    void rotate_left();
};

void h_circle::draw() {
    double currAngle=angle;
    double endAngle=angle+M_PI;
    double angleStep = M_PI / 64;
    for(;currAngle<endAngle;currAngle+=angleStep){
        put_point(center.x+radius*cos(currAngle), center.y+radius*sin(currAngle));
    }
}

void h_circle::rotate_left() {
    angle = angle+M_PI_2;
}

void h_circle::rotate_right() {
    angle = angle-M_PI_2;
}

void h_circle::flip_horisontally() {
    angle = angle+M_PI;
}

void h_circle::flip_vertically(){
    angle = angle+M_PI;
}

// ПРИМЕР ДОБАВКИ: дополнительная функция присоединения…
void down(shape &p,  const shape &q)
{    point n = q.south( );
     point s = p.north( );
     p.move(n.x - s.x, n.y - s.y - 1); 
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
	myshape face(point(15,10), point(27,18));
	shape_refresh( );
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор
//== 2. Подготовка к сборке ==
	hat.rotate_right( );
	brim.resize(2.0);
	face.resize(1.2);
    shape_refresh( );
	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений
//== 3. Сборка изображения ==
//	face.move(0, -10); // Лицо – в исходное положение (если нужно!)
	up(brim, face);
	up(hat, brim);
	shape_refresh( );
	std::cout << "=== Ready! ===\n";
	std::cin.get();       //Смотреть результат
	//screen_destroy( );
	return 0; 
}