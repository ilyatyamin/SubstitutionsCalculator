#include "segment.h"

#include <algorithm>
#include <cmath>

#include "line.h"

namespace geometry {
    Segment::Segment() {
        start_ = Point(0, 0);
        end_ = Point(0, 0);
    }

    Segment::Segment(Point start, Point end) {
        start_ = start;
        end_ = end;
    }

    Point Segment::GetStart() const {
        return start_;
    }

    Point Segment::GetEnd() const {
        return end_;
    }

    double Segment::Distance(Point point) const {
        // представим отрезок как прямую (сможем получить доступ к коэффициентам a,b,c)
        Line line = geometry::Line(start_, end_);

        return static_cast<double>(std::abs(line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC())) /
               std::sqrt(line.GetA() * line.GetA() + line.GetB() * line.GetB());
    }

    bool Segment::Degenerate() const {
        return (start_.GetX() == end_.GetX()) && (start_.GetY() == end_.GetY());
    }

    Segment &Segment::Move(const Vector &vector) {
        start_.Move(vector);
        end_.Move(vector);
        return *this;
    }

    bool Segment::ContainsPoint(const Point &point) const {
        // решим через скалярное произведение
        Line line = Line(start_, end_);
        bool on_line = (line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC() == 0);
        bool on_segment = (std::min(GetStart().GetX(), GetEnd().GetX()) <= point.GetX()) &&
                          (std::min(GetStart().GetY(), GetEnd().GetY()) <= point.GetY()) &&
                          (std::max(GetStart().GetX(), GetEnd().GetX()) >= point.GetX()) &&
                          (std::max(GetStart().GetY(), GetEnd().GetY()) >= point.GetY());
        return on_line && on_segment;
    }

    int64_t OrientedArea(const Point point1, const Point point2, const Point point3) {
        int64_t first_side = (point2.GetX() - point1.GetX()) * (point3.GetY() - point1.GetY());
        int64_t second_side = (point2.GetY() - point1.GetY()) * (point3.GetX() - point1.GetX());
        int64_t area = first_side - second_side;
        return area;
    }

    bool Segment::CrossesSegment(const Segment &segment) const {
        // случай, когда оба отрезка лежат на одной прямой
        auto is_on_line = [](const Point p1, const Point p2, const Point p3, const Point p4, bool comparator) {
            if (comparator) {
                return std::max(std::min(p1.GetX(), p2.GetX()), std::min(p3.GetX(), p4.GetX())) <=
                       std::min(std::max(p1.GetX(), p2.GetX()), std::max(p3.GetX(), p4.GetX()));
            }
            return std::max(std::min(p1.GetY(), p2.GetY()), std::min(p3.GetY(), p4.GetY())) <=
                   std::min(std::max(p1.GetY(), p2.GetY()), std::max(p3.GetY(), p4.GetY()));
        };

        bool on_line_1 = is_on_line(start_, end_, segment.start_, segment.end_, true);
        bool on_line_2 = is_on_line(start_, end_, segment.start_, segment.end_, false);
        bool is_area_1 = OrientedArea(start_, end_, segment.start_) * OrientedArea(start_, end_, segment.end_) <= 0;
        bool is_area_2 =
                OrientedArea(segment.start_, segment.end_, start_) * OrientedArea(segment.start_, segment.end_, end_) <=
                0;
        return on_line_1 && on_line_2 && is_area_1 && is_area_2;
    }

    Segment *Segment::Clone() const {
        Segment *segment = new Segment(start_, end_);
        return segment;
    }
}  // namespace geometry
