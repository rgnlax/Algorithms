//2_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество вершин, затем последовательно координаты всех вершин в порядке обхода против часовой стрелки.

#include <iostream>
#include <math.h>

//Структура точки
struct Point {
    int x;
    int y;
    Point():x(0), y(0) {}
    Point(int _x, int _y): x(_x), y(_y) {}
};

double square(Point *, int);
void inputPoints(Point **, int);

int main() {
    
    //Ввод числа вершин
    int angleCount;
    std::cin >> angleCount;
    
    //Ввод вершин многоугольника
    Point *points;
    inputPoints(&points, angleCount);
    
    
    //Вывод результата площади
    std::cout << square(points, angleCount);
    delete[] points;
    return 0;
}

double square(Point *points, int pointsCount) {
    double square = 0;
    for (int i = 0; i < pointsCount; ++i) {
        //Алгоритм вычисления площади по координатам вершин
        int currentXvalue = points[i].x;
        int currentY1value = points[(i - 1 >= 0) ? i - 1 : pointsCount - i - 1].y;
        int currentY2value = points[(i + 1) % pointsCount].y;
        
        square += currentXvalue * (currentY2value - currentY1value);
    }
    square /= 2;
    return square < 0 ? -square : square;
}

void inputPoints(Point **points, int angleCount) {
    *points = new Point[angleCount];
    for (int i = 0; i < angleCount; ++i) {
        int x, y;
        std::cin >> x >> y;
        Point p = Point(x, y);
        (*points)[i] = p;
    }
    
}


