#include <iostream>
#include <string>

class Shape {
public:
    virtual Shape* clone() const = 0;
    virtual void draw() const = 0;
};

class Rectangle : public Shape {
private:
    int width;
    int height;
    
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    
    Shape* clone() const override {
        return new Rectangle(*this);
    }
    
    void draw() const override {
        std::cout << "Drawing a rectangle with width " << width
                  << " and height " << height << std::endl;
    }
};

class Circle : public Shape {
private:
    int radius;
    
public:
    Circle(int r) : radius(r) {}
    
    Shape* clone() const override {
        return new Circle(*this);
    }
    
    void draw() const override {
        std::cout << "Drawing a circle with radius " << radius << std::endl;
    }
};

int main() {
    Shape* originalRectangle = new Rectangle(100, 200);
    Shape* originalCircle = new Circle(50);
    
    // Create clones
    Shape* clonedRectangle = originalRectangle->clone();
    Shape* clonedCircle = originalCircle->clone();
    
    // Draw original objects
    originalRectangle->draw();
    originalCircle->draw();
    
    std::cout << std::endl;
    
    // Draw cloned objects
    clonedRectangle->draw();
    clonedCircle->draw();
    
    // Clean up memory
    delete originalRectangle;
    delete originalCircle;
    delete clonedRectangle;
    delete clonedCircle;
    
    return 0;
}
