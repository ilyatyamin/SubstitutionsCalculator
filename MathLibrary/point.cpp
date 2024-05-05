#include "point.h"

#include <algorithm>

#include "segment.h"

namespace geometry {
    int64_t Point::GetX() const {
        return x_coord_;
    }

    int64_t Point::GetY() const {
        return y_coord_;
    }

    void Point::SetX(int64_t x) {
        x_coord_ = x;
    }

    void Point::SetY(int64_t y) {
        y_coord_ = y;
    }

    Point &Point::Move(const Vector &vector) {
        x_coord_ = x_coord_ + vector.GetX();
        y_coord_ = y_coord_ + vector.GetY();
        return *this;
    }

    bool Point::ContainsPoint(const Point &point) const {
        return (x_coord_ == point.x_coord_) && (y_coord_ == point.y_coord_);
    }

    bool Point::CrossesSegment(const Segment &segment) const {
        return ((x_coord_ - segment.GetStart().x_coord_) * (segment.GetEnd().y_coord_ - segment.GetStart().y_coord_) -
                (segment.GetEnd().x_coord_ - segment.GetStart().x_coord_) * (y_coord_ - segment.GetStart().y_coord_) ==
                0) &&
               (std::min(segment.GetStart().x_coord_, segment.GetEnd().x_coord_) <= x_coord_) &&
               (x_coord_ <= std::max(segment.GetStart().x_coord_, segment.GetEnd().x_coord_)) &&
               (std::min(segment.GetStart().y_coord_, segment.GetEnd().y_coord_) <= y_coord_) &&
               (y_coord_ <= std::max(segment.GetStart().y_coord_, segment.GetEnd().y_coord_));
    }

    Point *Point::Clone() const {
        Point *point = new Point(x_coord_, y_coord_);
        return point;
    }

    Point::Point(int64_t x, int64_t y) {
        x_coord_ = x;
        y_coord_ = y;
    }

    Vector Point::operator-(Point other) const {
        return Vector(x_coord_ - other.x_coord_, y_coord_ - other.y_coord_);
    }
}  // namespace geometry
