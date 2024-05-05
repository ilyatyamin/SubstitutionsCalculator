#include "line.h"

#include <algorithm>
#include <cmath>

#include "segment.h"

namespace geometry {
    Line::Line() {
        start_ = Point(0, 0);
        end_ = Point(0, 0);
    }

    int64_t Line::GetA() const {
        return end_.GetY() - start_.GetY();
    }

    int64_t Line::GetB() const {
        return start_.GetX() - end_.GetX();
    }

    int64_t Line::GetC() const {
        return end_.GetX() * start_.GetY() - start_.GetX() * end_.GetY();
    }

    Line::Line(Point start, Point end) {
        start_ = start;
        end_ = end;
    }

    double Line::Distance(Point point) const {
        return static_cast<double>(std::abs(GetA() * point.GetX() + GetB() * point.GetY() + GetC())) /
               std::sqrt(GetA() * GetA() + GetB() * GetB());
    }

    Line &Line::Move(const Vector &vector) {
        start_.Move(vector);
        end_.Move(vector);
        return *this;
    }

    bool Line::ContainsPoint(const Point &point) const {
        return GetA() * point.GetX() + GetB() * point.GetY() + GetC() == 0;
    }

    bool Line::CrossesSegment(const Segment &segment) const {
        // Точки лежат по разные стороны от прямой <=> отрезок пересекает прямую (смотрим на векторное произведение)
        return static_cast<double>(segment.GetStart().GetX() * GetA() + GetB() * segment.GetStart().GetY() + GetC()) /
               std::sqrt(GetA() * GetA() + GetB() * GetB()) *
               static_cast<double>(segment.GetEnd().GetX() * GetA() + GetB() * segment.GetEnd().GetY() + GetC()) /
               std::sqrt(GetA() * GetA() + GetB() * GetB()) <=
               0;
    }

    Line *Line::Clone() const {
        Line *line = new Line(start_, end_);
        return line;
    }
}  // namespace geometry
