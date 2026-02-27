// Пополнение и использование библиотеки фигур
//#include "pch.h"	//связь с ОС (пример для Visual C++2017)
#include <locale.h>
#include <iostream>
#include "shape.h"

class h_circle : public rectangle, public reflectable {
public:
    point dVector;      // вектор диаметра
    int angle;          // угол поворота: 0, 90, 180, 270
    
    h_circle(point a, int rd) : rectangle(point(a.x-rd, a.y), point(a.x+rd, a.y+rd*0.7+1)) {
        dVector = point(rd, 0);
        angle = 0;
    }
    
    void draw();
    void flip_horisontally();
    void rotate_right();
    void rotate_left();
};

void h_circle::draw() {
    // Оставляем ВСЁ как в оригинале
    int x0 = (sw.x + ne.x) / 2;
    int y0 = vert ? ne.y : sw.y;  // как в оригинале!
    int radius = (ne.x - sw.x) / 2;
    
    int x = 0, y = radius, delta = 2 - 2 * radius, error = 0;
    
    while(y >= 0) {
        // Базовая точка (как в оригинале, но с поправкой на угол)
        int base_x = x;
        int base_y = y * 0.7;
        
        // Координаты после поворота
        int px1_x, px1_y, px2_x, px2_y;
        
        // В зависимости от угла поворота по-разному располагаем точки
        switch(angle) {
            case 0: // 0° - оригинальное поведение (вниз или вверх через vert)
                if(vert) {
                    px1_x = x0 + base_x; px1_y = y0 - base_y;
                    px2_x = x0 - base_x; px2_y = y0 - base_y;
                } else {
                    px1_x = x0 + base_x; px1_y = y0 + base_y;
                    px2_x = x0 - base_x; px2_y = y0 + base_y;
                }
                break;
                
            case 90: // 90° - поворот вправо
                if(vert) {
                    px1_x = x0 + base_y; px1_y = y0 - base_x;
                    px2_x = x0 + base_y; px2_y = y0 + base_x;
                } else {
                    px1_x = x0 - base_y; px1_y = y0 - base_x;
                    px2_x = x0 - base_y; px2_y = y0 + base_x;
                }
                break;
                
            case 180: // 180° - перевёрнуто
                if(vert) {
                    px1_x = x0 + base_x; px1_y = y0 + base_y;
                    px2_x = x0 - base_x; px2_y = y0 + base_y;
                } else {
                    px1_x = x0 + base_x; px1_y = y0 - base_y;
                    px2_x = x0 - base_x; px2_y = y0 - base_y;
                }
                break;
                
            case 270: // 270° - поворот влево
                if(vert) {
                    px1_x = x0 - base_y; px1_y = y0 - base_x;
                    px2_x = x0 - base_y; px2_y = y0 + base_x;
                } else {
                    px1_x = x0 + base_y; px1_y = y0 - base_x;
                    px2_x = x0 + base_y; px2_y = y0 + base_x;
                }
                break;
        }
        
        put_point(px1_x, px1_y);
        put_point(px2_x, px2_y);
        
        // Алгоритм Брезенхема (без изменений)
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

void h_circle::rotate_left() {
    angle = (angle + 90) % 360;
    
    // Поворачиваем вектор диаметра
    int new_dx = -dVector.y;
    int new_dy = dVector.x;
    dVector.x = new_dx;
    dVector.y = new_dy;
    
    // НЕ меняем sw, ne, vert!
}

void h_circle::rotate_right() {
    angle = (angle + 270) % 360;
    
    int new_dx = dVector.y;
    int new_dy = -dVector.x;
    dVector.x = new_dx;
    dVector.y = new_dy;
    
    // НЕ меняем sw, ne, vert!
}

void h_circle::flip_horisontally() {
    dVector.x = -dVector.x;
    hor = !hor;
    
    // При горизонтальном отражении угол меняется зеркально
    if(angle == 90) angle = 270;
    else if(angle == 270) angle = 90;
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
	/*
//== 1. Объявление набора фигур ==
	rectangle hat(point(0, 0), point(14, 5));
	line brim(point(20,9),17);
	myshape face(point(15,10), point(27,18));
	h_circle beard(point(40,10), 5);
	shape_refresh( );
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор
//== 2. Подготовка к сборке ==
	hat.rotate_right( );
	brim.resize(2.0);
	face.resize(1.2);
	beard.flip_vertically( );
	beard.resize(1.2);
        shape_refresh( );
	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений
//== 3. Сборка изображения ==
//	face.move(0, -10); // Лицо – в исходное положение (если нужно!)
	up(brim, face);
	up(hat, brim);
	down(beard, face);
	shape_refresh( );
	std::cout << "=== Ready! ===\n";
	std::cin.get();       //Смотреть результат
	*/
	h_circle hc(point(10, 10), 5);
	hc.rotate_left();
	//hc.rotate_right();
	hc.draw();
	screen_refresh();
	//screen_destroy( );
	return 0; 
}