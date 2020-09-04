#ifndef _RECTANGLE_HEADER_
#define _RECTANGLE_HEADER_

class Rectangle {
public:
    Rectangle(int width, int height);

    int GetArea() const;

    int GetPerimeter() const;

    int GetWidth() const;
    int GetHeight() const;

private:
    int width_, height_;
};

#endif // !_RECTANGLE_HEADER_