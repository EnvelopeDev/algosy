#include <locale.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>
#include <vector>
#include <limits>
#include "shape.h"

class h_circle : public rotatable, public reflectable {
public:
    double angle;
    point center;
    int radius;

    h_circle(point a, int rd) : center(a), radius(rd), angle(0) {
        if (rd <= 0) throw InvalidParameter("Radius must be positive");
        check_bounds(*this);
    }

    point north() const override {
        double maxY = -std::numeric_limits<double>::infinity();
        // Check all points on the semicircle arc
        for (double theta = angle; theta <= angle + M_PI + 1e-10; theta += 0.01) {
            double y = center.y + radius * sin(theta);
            if (y > maxY) maxY = y;
        }
        // Also check the center point if it's part of the semicircle
        if (sin(angle) >= -1e-10 || sin(angle + M_PI) <= 1e-10) {
            maxY = std::max(maxY, (double)center.y);
        }
        return point(center.x, static_cast<int>(round(maxY)));
    }

    point south() const override {
        double minY = std::numeric_limits<double>::infinity();
        for (double theta = angle; theta <= angle + M_PI + 1e-10; theta += 0.01) {
            double y = center.y + radius * sin(theta);
            if (y < minY) minY = y;
        }
        if (sin(angle) >= -1e-10 || sin(angle + M_PI) <= 1e-10) {
            minY = std::min(minY, (double)center.y);
        }
        return point(center.x, static_cast<int>(round(minY)));
    }

    point east() const override {
        double maxX = -std::numeric_limits<double>::infinity();
        for (double theta = angle; theta <= angle + M_PI + 1e-10; theta += 0.01) {
            double x = center.x + radius * cos(theta);
            if (x > maxX) maxX = x;
        }
        if (cos(angle) >= -1e-10 || cos(angle + M_PI) >= -1e-10) {
            maxX = std::max(maxX, (double)center.x + radius);
        }
        if (cos(angle) <= 1e-10 || cos(angle + M_PI) <= 1e-10) {
            maxX = std::max(maxX, (double)center.x - radius);
        }
        return point(static_cast<int>(round(maxX)), center.y);
    }

    point west() const override {
        double minX = std::numeric_limits<double>::infinity();
        for (double theta = angle; theta <= angle + M_PI + 1e-10; theta += 0.01) {
            double x = center.x + radius * cos(theta);
            if (x < minX) minX = x;
        }
        if (cos(angle) >= -1e-10 || cos(angle + M_PI) >= -1e-10) {
            minX = std::min(minX, (double)center.x + radius);
        }
        if (cos(angle) <= 1e-10 || cos(angle + M_PI) <= 1e-10) {
            minX = std::min(minX, (double)center.x - radius);
        }
        return point(static_cast<int>(round(minX)), center.y);
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
        if (factor <= 0)
            throw InvalidParameter("Resize factor must be positive");
        radius = static_cast<int>(radius * factor);
        if (radius <= 0)
            throw InvalidParameter("Radius became non-positive after resize");
        check_bounds(*this);
    }

    void flip_horisontally() {
        if (angle < M_PI) {
            angle = M_PI - angle;
        } else {
            angle = 3*M_PI - angle;
        }
        while (angle < 0) angle += 2*M_PI;
        while (angle >= 2*M_PI) angle -= 2*M_PI;
        check_bounds(*this);
    }

    void flip_vertically() {
        angle = 2*M_PI - angle;
        while (angle < 0) angle += 2*M_PI;
        while (angle >= 2*M_PI) angle -= 2*M_PI;
        check_bounds(*this);
    }

    void rotate_right() {
        angle -= M_PI_2;
        while (angle < 0) angle += 2*M_PI;
        check_bounds(*this);
    }

    void rotate_left() {
        angle += M_PI_2;
        while (angle >= 2*M_PI) angle -= 2*M_PI;
        check_bounds(*this);
    }
};

void h_circle::draw() {
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error;

    while (y >= 0) {
        for (int dx : {x, -x}) {
            for (int dy : {y, -y}) {
                double pointAngle = atan2(dy, dx);
                if (pointAngle < 0) pointAngle += 2 * M_PI;

                double normalizedAngle = pointAngle - angle;
                while (normalizedAngle < 0) normalizedAngle += 2 * M_PI;
                while (normalizedAngle >= 2 * M_PI) normalizedAngle -= 2 * M_PI;

                if (normalizedAngle >= -1e-10 && normalizedAngle <= M_PI + 1e-10) {
                    put_point(center.x + dx, center.y + dy);
                }
            }
        }

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

void up(shape& p, const shape& q)
{
    point n = q.north( );
    point s = p.south( );
    p.move(n.x - s.x, n.y - s.y + 1);
}

void up_center(h_circle& p, const shape& q) {
    point n = q.north();
    point p_center = p.center;
    p.move(n.x - p_center.x, n.y - p_center.y + 1);
}

void down_center(h_circle& p, const shape& q) {
    point s = q.south();
    point p_center = p.center;
    p.move(s.x - p_center.x, s.y - p_center.y - 1);
}

void right_center(h_circle& p, const shape& q) {
    point e = q.east();
    point p_center = p.center;
    p.move(e.x - p_center.x + 1, e.y - p_center.y);
}

void left_center(h_circle& p, const shape& q) {
    point w = q.west();
    point p_center = p.center;
    p.move(w.x - p_center.x - 1, w.y - p_center.y);
}

class myshape : public rectangle {
    int w, h;
    line l_eye;
    line r_eye;
    line mouth;
public:
    myshape(point, point);
    void draw( );
    void move(int, int);
    void resize(double r) {
        if (r <= 0) throw InvalidParameter("Resize factor must be positive");
        rectangle::resize(r);
        rectangle::move(w*(1-r)*0.5, h*(1-r)*0.5);
    }
    void rotate_left() {}
    void rotate_right() {}
};

myshape :: myshape(point a, point b)
    : rectangle(a, b),
    w(neast( ).x - swest( ).x + 1),
    h(neast( ).y - swest( ).y + 1),
    l_eye(point(swest( ).x + 2, swest( ).y + h * 3 / 4), 2),
    r_eye(point(swest( ).x + w - 4, swest( ).y + h * 3 / 4), 2),
    mouth(point(swest( ).x + 2, swest( ).y + h / 4), w - 4)
{ }

void myshape :: draw( )
{
    rectangle :: draw( );
    int a = (swest( ).x + neast( ).x) / 2;
    int b = (swest( ).y + neast( ).y) / 2;
    put_point(point(a, b));
}

void myshape :: move(int a, int b)
{
    rectangle :: move(a, b);
    l_eye.move(a, b);  r_eye.move(a, b);
    mouth.move(a, b);
}

template<typename Func, typename... Args>
bool safe_execute(const char* operation_name, Func&& func, Args&&... args) {
    try {
        func(std::forward<Args>(args)...);
        std::cout << "  ✓ Success\n";
        return true;
    } catch (const InvalidParameter& e) {
        std::cout << " x Exception: InvalidParameter in " << operation_name
                  << " - " << e.what() << std::endl;
    } catch (const OutOfScreen& e) {
        std::cout << " x Exception: OutOfScreen in " << operation_name
                  << " - " << e.what() << std::endl;
    } catch (const ShapeException& e) {
        std::cout << " x Exception: ShapeException in " << operation_name
                  << " - " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << " x Exception: std::exception in " << operation_name
                  << " - " << e.what() << std::endl;
    }
    return false;
}

template<typename T, typename... Args>
std::unique_ptr<T> safe_create(const char* shape_name, Args&&... args) {
    try {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        std::cout << "  ✓ " << shape_name << " created successfully\n";
        return ptr;
    } catch (const InvalidParameter& e) {
        std::cout << " x Exception: InvalidParameter creating " << shape_name
                  << " - " << e.what() << std::endl;
    } catch (const OutOfScreen& e) {
        std::cout << " x Exception: OutOfScreen creating " << shape_name
                  << " - " << e.what() << std::endl;
    } catch (const ShapeException& e) {
        std::cout << " x Exception: ShapeException creating " << shape_name
                  << " - " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << " x Exception: std::exception creating " << shape_name
                  << " - " << e.what() << std::endl;
    }
    return nullptr;
}

int main( )
{
    screen_init( );

    std::cout << "[Test 1: Creation with invalid parameters]\n" << std::endl;

    safe_create<h_circle>("h_circle with negative radius", point(30, 5), -2);
    safe_create<h_circle>("h_circle with zero radius", point(30, 5), 0);
    safe_create<line>("line with zero length", point(20, 9), point(20, 9));
    safe_create<rectangle>("rectangle with width <= 0", point(10, 10), point(5, 15));
    safe_create<rectangle>("rectangle with height <= 0", point(10, 10), point(15, 5));
    safe_create<h_circle>("h_circle out of screen bounds", point(200, 200), 10);

    std::cout << "[Test 2: Normal creation of basic shapes]\n" << std::endl;

    auto hat = safe_create<rectangle>("hat", point(0, 0), point(14, 5));
    auto brim = safe_create<line>("brim", point(20, 9), 17);
    auto earL = safe_create<h_circle>("earL", point(30, 5), 2);
    auto earR = safe_create<h_circle>("earR", point(40, 5), 2);
    auto tie = safe_create<h_circle>("tie", point(50, 5), 2);
    auto shishak = safe_create<h_circle>("shishak", point(60, 5), 2);
    auto face = safe_create<myshape>("face", point(15, 10), point(27, 18));

    std::cout << "[First screen]\n";
    shape_refresh();
    std::cout << "\nPress Enter to continue...\n";
    std::cin.get();

    std::cout << "[Test 3: Exceptions during transformations]\n" << std::endl;

    if (earL) {
        std::cout << "Rotating earL left: ";
        safe_execute("rotate_left earL", [&](){ earL->rotate_left(); });
        std::cout << "Rotating earL left again: ";
        safe_execute("rotate_left earL", [&](){ earL->rotate_left(); });
    }

    if (tie) {
        std::cout << "Flipping tie horizontally: ";
        safe_execute("flip_horisontally tie", [&](){ tie->flip_horisontally(); });
        std::cout << "Flipping tie horizontally again: ";
        safe_execute("flip_horisontally tie", [&](){ tie->flip_horisontally(); });
    }

    if (earR) {
        std::cout << "Attempting to resize earR with factor 0: ";
        safe_execute("resize earR factor 0", [&](){ earR->resize(0); });
    }

    if (earR) {
        std::cout << "Attempting to enlarge earR 50x: ";
        safe_execute("resize earR factor 50", [&](){ earR->resize(50); });
    }

    if (shishak) {
        std::cout << "Attempting to move shishak out of screen bounds: ";
        safe_execute("move shishak (x+100)", [&](){ shishak->move(100, 0); });
    }

    if (hat) {
        std::cout << "Attempting to rotate hat right: ";
        safe_execute("rotate_right hat", [&](){ hat->rotate_right(); });
    }

    std::cout << "[Second screen]\n";
    std::cout << "Shapes that caused exceptions preserved their previous state\n";
    shape_refresh();
    std::cout << "\nPress Enter to continue...\n";
    std::cin.get();

    std::cout << "[Test 4: Exceptions during shape assembly]\n" << std::endl;

    if (brim && face) {
        std::cout << "Placing brim above face: ";
        safe_execute("up(brim, face)", [&](){ up(*brim, *face); });
    }

    if (hat && brim) {
        std::cout << "Placing hat above brim: ";
        safe_execute("up(hat, brim)", [&](){ up(*hat, *brim); });
    }

    if (shishak && hat) {
        std::cout << "Placing shishak above hat: ";
        safe_execute("up_center(shishak, hat)", [&](){ up_center(*shishak, *hat); });
    }

    std::cout << "Attempting to place large circle left of face: ";
    auto test_circle = safe_create<h_circle>("test_circle for left_center", point(10, 10), 30);
    if (test_circle && face) {
        safe_execute("left_center(test_circle, face)", [&](){ left_center(*test_circle, *face); });
    }

    std::cout << "[Final screen]\n";
    shape_refresh();
    std::cout << "\nPress Enter to exit...\n";
    std::cin.get();

    screen_destroy();
}
