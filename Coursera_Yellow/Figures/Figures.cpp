#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <memory>

using namespace std;

const double pi = 3.14;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
};

class Triangle : public Figure {
public:
	Triangle(double a, double b, double c) :
		a_(a), b_(b), c_(c)
	{}

	string Name() const override {
		return "TRIANGLE";
	}

	double Perimeter() const override {
		return a_ + b_ + c_;
	}

	double Area() const override {
		double p = Perimeter() / 2;
		return pow(p * (p - a_) * (p - b_) * (p - c_), 0.5);
	}

private:
	const double a_, b_, c_;
};

class Circle : public Figure {
public:
	Circle(double r) :
		r_(r)
	{}

	string Name() const override {
		return "CIRCLE";
	}

	double Perimeter() const override {
		return 2 * pi * r_;
	}

	double Area() const override {
		return pi * r_ * r_;
	}

private:
	const double r_;
};

class Rect : public Figure {
public:
	Rect(double l, double w) :
		l_(l), w_(w)
	{}

	string Name() const override {
		return "RECT";
	}

	double Perimeter() const override {
		return 2 * (l_ + w_);
	}

	double Area() const override {
		return l_ * w_;
	}

private:
	const double l_, w_;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
	string id;
	is >> id;
	if (id == "RECT") {
		double l, w;
		is >> l >> w;
		return make_shared<Rect>(l, w);
	}
	else if (id == "CIRCLE") {
		double r;
		is >> r;
		return make_shared<Circle>(r);
	}
	else {
		double a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	}
}

/*
ADD RECT 2 3
ADD TRIANGLE 3 4 5
ADD RECT 10 20
ADD CIRCLE 5
PRINT
*/

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			// Пропускаем "лишние" ведущие пробелы.
			// Подробнее об std::ws можно узнать здесь:
			// https://en.cppreference.com/w/cpp/io/manip/ws
			is >> ws;
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}
