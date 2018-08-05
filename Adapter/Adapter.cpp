/**
 * Adapter.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

/**
 * Get the interface you want from the interface you were given.
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include <set>
#include <tuple>

#include <QApplication>
#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QPoint>
#include <QWidget>

/**
 * Assume that we have a class that defines and draws shapes in terms of points, whereas we want circles,
 * lines, and rectangles.
 */
using Point = std::pair<int, int>;
using Points = std::set<Point>;

struct Shape : QWidget {
    Shape(QWidget *parent, const std::set<Point> &points)
        : QWidget{parent}, points{points} {}
    Shape(QWidget *parent, std::set<Point> &&points)
        : QWidget{parent}, points{std::move(points)} {}
    const std::set<Point> points;

    void paintEvent(QPaintEvent *e) override {
        Q_UNUSED(e)
        doPainting();
    }

    virtual Points::iterator begin() {
        return points.begin();
    }
    virtual Points::iterator end() {
        return points.end();
    }
    virtual Points::const_iterator cbegin() {
        return points.cbegin();
    }
    virtual Points::const_iterator cend() {
        return points.cend();
    }


private:
    void doPainting() {
        QPainter painter { this };

        QPen pen{Qt::black};
        pen.setWidth(10);
        for (const auto p: points) {
            const auto [x, y] = p;
            QPoint qp{x, y};
            painter.drawPoint(qp);
        }
    }
};

/**
 * These are our adapters.
 */
struct Line : Shape {
    Line(QWidget *parent, const Point &first, const Point &second)
        : Shape{parent, linePoints(first, second)} {}

private:
    static std::set<Point> linePoints(const Point &first, const Point &second) {
        const auto [x1, y1] = first;
        const auto [x2, y2] = second;

        std::set<Point> points;

        // If the slope is undefined, we need special treatment.
        if (x1 == x2) {
            for (auto y = y1; y <= y2; y += 0.01)
                points.insert({x1, y});
        } else {
            const auto slope = (y2 - y1) / (x2 - x1);
            const auto b     = y1 - slope * x1;

            for (auto x = x1; x <= x2; x += 0.01)
                points.insert({x, slope * x + b});
        }

        return points;
    }
};

// We don't want to use this shape: we want actual geometric objects, so write an adapter.
struct Circle : Shape {
    Circle(QWidget *parent, const Point &centre, const double radius)
        : Shape{parent, circlePoints(centre, radius)} {}

private:
    static std::set<Point> circlePoints(const Point &centre, const double radius) {
        const auto [cx, cy] = centre;

        std::set<Point> points;

        // Iterate over all angles and throw the points into the vector.
        const auto rsq = radius * radius;
        for (auto x = 0.01; x <= radius; x += 0.01) {
            int px = static_cast<int>(std::round(x));
            int y = static_cast<int>(std::round(std::sqrt(rsq - x*x)));
            points.insert({cx + px, cy + y});
            points.insert({cx - px, cy + y});
            points.insert({cx + px, cy - y});
            points.insert({cx - px, cy - y});
        }

        return points;
    }
};

int main(int argc, char *argv[]) {
    QApplication qapp{argc, argv};

    Circle c{nullptr, {200,200}, 100};
    c.resize(400, 400);
    c.setWindowTitle("Circle Adapter!");
    c.setVisible(true);

    return qapp.exec();
}

