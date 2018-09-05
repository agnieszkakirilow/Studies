#include <iostream>
#include<array>
#include<time.h>

class Figure{
public:
    int sideA;
    int sideB;
    float _area;
    virtual float area() = 0;
    float getArea();
};

float Figure::getArea()
{
    return _area;
}

class Rectangular: public Figure{
public:
    Rectangular(int a, int b = 1)
    {
        sideA = a;
        sideB = b;
        std::cout << a << "  " << b << std::endl;

    }
    float area();
};

float Rectangular::area()
{
   _area = sideA * sideB;
   return _area;
}

class Circle: public Figure{
public:
    Circle(int radius)
    {
      sideA = radius;
      std::cout << radius << std::endl;
    }
    float area();
};

float Circle::area()
{
    _area =  3.14 * sideA * sideA;
    return _area;
}

class Triangle: public Figure{
public:
    Triangle(int side, int height)
    {
       sideA = side;
       sideB = height;
       std::cout << side << "  " << height << std::endl;
    }
    float area();
};


float Triangle::area()
{
    _area =  0.5 *sideA * sideB;
    return _area;
}

class Storage{
public:
    std::array<Figure*,100> arr;
    void putFigure()
    {
        std::srand(time(NULL));
        for(int i = 0; i < 100; i++)
        {
            int figures = std::rand () % 3;
            switch(figures)
            {
            case 0:
            {
                std::cout << "case 0:    ";
                arr[i] = new Rectangular(std::rand () % 10 +1, std::rand () % 10 +1);
            }
            break;
            case 1:
            {
                std::cout << "case 1:    ";
                arr[i] = new Circle(std::rand () % 10 +1);
            }
            break;
            case 2:
            {
                std::cout << "case 2:    ";
                arr[i] = new Triangle(std::rand () % 10 +1, std::rand () % 10 +1);
            }
            }
        }
    }
    void showArr()
    {
        for(int i = 0; i < 100; i++)
        {
            arr[i]->area();
            std::cout << "area " << arr[i]->getArea() << std::endl;
        }
    }
};

int main()
{
    Storage s;
    s.putFigure();
    s.showArr();
    return 0;
}
