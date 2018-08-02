struct Point
{
    int x{ 0 }, y{ 0 };

    Point(){}
    Point(const Point &p) : x{p.x}, y{p.y} {}
    Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line
{
    Point *start, *end;

    Line(Point* const start, Point* const end)
            : start(start), end(end)
    {
    }

    ~Line()
    {
        delete start;
        delete end;
    }

    Line deep_copy() const
    {
        return { new Point{*start}, new Point{*end} };
    }
};

int main() {
    Line l1{new Point{0,0}, new Point{1,1}};
    auto l2 = l1.deep_copy();
    l2.start->x = 1;
}