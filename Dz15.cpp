#include <iostream>   
#include <fstream>
//#include <Windows.h> чомусь з ним з'являється помилка
using namespace std;

class Shape {
public:
    virtual void Show() = 0;
    virtual void Save(ofstream& saving) = 0;
    virtual void Load(ifstream& loading) = 0;
    virtual ~Shape() = default;
};

class Square : public Shape {
    double x, y, side;
public:
    Square(double x = 0, double y = 0, double side = 0) : x(x), y(y), side(side) {}

    void Show() override {
        cout << "Square - [" << x << ", " << y << "], side " << side << endl;
    }

    void Save(ofstream& saving) override {
        saving << "Square " << x << " " << y << " " << side << endl;
    }

    void Load(ifstream& loading) override {
        loading >> x >> y >> side;
    }
};

class Rectangle : public Shape {
    double x, y, width, length;
public:
    Rectangle(double x = 0, double y = 0, double width = 0, double length = 0) : x(x), y(y), width(width), length(length) {}

    void Show() override {
        cout << "Rectangle - [" << x << ", " << y << "], width " << width << ", length " << length << endl;
    }

    void Save(ofstream& saving) override {
        saving << "Rectangle " << x << " " << y << " " << width << " " << length << endl;
    }

    void Load(ifstream& loading) override {
        loading >> x >> y >> width >> length;
    }
};

class Circle : public Shape {
    double x, y, radius;
public:
    Circle(double x = 0, double y = 0, double radius = 0) : x(x), y(y), radius(radius) {}

    void Show() override {
        cout << "Circle - [" << x << ", " << y << "], radius " << radius << endl;
    }

    void Save(ofstream& saving) override {
        saving << "Circle " << x << " " << y << " " << radius << endl;
    }

    void Load(ifstream& loading) override {
        loading >> x >> y >> radius;
    }
};

class EquilateralTriangle : public Shape { //Ви казали, що можна замінити еліпс на іншу фігуру, тому я обрала рівносторонній трикутник
    double x, y, side;
public:
    EquilateralTriangle(double x = 0, double y = 0, double side = 0) : x(x), y(y), side(side) {}

    void Show() override {
        cout << "EquilateralTriangle - [" << x << ", " << y << "], side " << side << endl;
    }

    void Save(ofstream& saving) override {
        saving << "EquilateralTriangle " << x << " " << y << " " << side << endl;
    }

    void Load(ifstream& loading) override {
        loading >> x >> y >> side;
    }
};

int main() {
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    Shape* shapes[4];
    shapes[0] = new Square(55.3, 12, 4);
    shapes[1] = new Rectangle(0.3, 1.2, 3, 7);
    shapes[2] = new Circle(45.7, 21.45, 8);
    shapes[3] = new EquilateralTriangle(3.7, 3, 5);

    ofstream saving("shapes.txt");
    if (saving.is_open()) {
        for (int i = 0; i < 4; i++) {
            shapes[i]->Save(saving);
        }
        saving.close();
    }

    Shape* loadedShapes[4];
    ifstream loading("shapes.txt");
    if (loading.is_open()) {
        string shapeType;
        for (int i = 0; i < 4; i++) {
            loading >> shapeType;
            if (shapeType == "Square") {
                loadedShapes[i] = new Square();
            }
            else if (shapeType == "Rectangle") {
                loadedShapes[i] = new Rectangle();
            }
            else if (shapeType == "Circle") {
                loadedShapes[i] = new Circle();
            }
            else if (shapeType == "EquilateralTriangle") {
                loadedShapes[i] = new EquilateralTriangle();
            }
            loadedShapes[i]->Load(loading);
        }
        loading.close();
    }

    for (int i = 0; i < 4; i++) {
        loadedShapes[i]->Show();
    }

    for (int i = 0; i < 4; i++) {
        delete shapes[i];
        delete loadedShapes[i];
    }

    return 0;
}
