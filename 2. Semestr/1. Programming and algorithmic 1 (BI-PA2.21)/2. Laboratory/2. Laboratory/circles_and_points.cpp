#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

struct CPoint
{
    long m_x;
    long m_y;
    // ====================================================================
    CPoint subtract( const CPoint & other ) const
    {
        return { m_x - other.m_x, m_y - other.m_y };
    }
    long square( ) const
    {
        return m_x * m_x + m_y * m_y;
    }
    bool is_multiple_of( const CPoint & other ) const
    {
        return m_x * other.m_y - m_y * other.m_x == 0;
    }
};

class CCircle
{
    public:
        CCircle & init( const CPoint & center, long radius )
        {
            m_center = center;
            m_sq_radius = radius * radius;
            return *this;
        }
        // ====================================================================
        CCircle & change_center ( const CPoint & new_center )
        {
            m_center = new_center;
            return *this;
        }
        // ====================================================================
        bool contains_point ( const CPoint & point ) const
        {
            long sq_distance = point.subtract(m_center).square();
            return sq_distance <= m_sq_radius;
        }
        // ====================================================================
    private:
        CPoint m_center;
        long m_sq_radius;
};

struct CTriangle
{
    // když už ale využívám statické metody, které nepracují s nějakou instancí,
    // nemusel bych u nich volit redundantní název
    static bool is_valid ( const CPoint & a, const CPoint & b, const CPoint & c )
    {
        return !a.subtract(c).is_multiple_of(b.subtract(c));
    }
    // ====================================================================
};

int main ( void )
{
    std::vector<CPoint> points = {{5,5}, {3,3}, {1,1}, {-6,-3}, {-2,2},
                                     {3,1}, {-3,3}, {3,-4}, {-6,-5}, {1,2}};
    CCircle circle;
    assert ( circle.init({15,15}, 5).change_center({-2,-2}).contains_point({-2,-2}) );

    assert ( ! circle.contains_point({15,15}) );

    size_t counter = 0;
    for ( CPoint & point : points )
        counter += circle.contains_point(point);
    
    assert ( counter == 5 );

    const CCircle & const_circle = circle;
    size_t const_counter = 0;
    for ( const CPoint & point : points )
        const_counter += const_circle.contains_point(point);

    assert ( const_counter == 5 );

    assert ( ! CTriangle::is_valid(points[0], points[1], points[2]) );
    assert ( ! CTriangle::is_valid(points[4], points[9], {-8,2})    );
    assert ( ! CTriangle::is_valid(points[1], points[5], {3,-5})    );
    assert ( ! CTriangle::is_valid(points[0], points[1], points[2]) );
    assert ( ! CTriangle::is_valid(points[0], points[0], points[0]) );
    assert ( ! CTriangle::is_valid(points[0], points[0], points[1]) );
    
    assert (   CTriangle::is_valid(points[0], points[2], points[4]) );
    assert (   CTriangle::is_valid(points[0], points[1], points[4]) );
    assert (   CTriangle::is_valid(points[0], points[1], points[3]) );
    assert (   CTriangle::is_valid(points[0], points[1], points[5]) );
    assert (   CTriangle::is_valid(points[0], points[1], points[6]) );
    assert (   CTriangle::is_valid(points[0], points[1], points[7]) );
    assert (   CTriangle::is_valid(points[0], points[1], points[8]) );
    assert (   CTriangle::is_valid(points[0], points[1], points[9]) );

    return 0;
}
