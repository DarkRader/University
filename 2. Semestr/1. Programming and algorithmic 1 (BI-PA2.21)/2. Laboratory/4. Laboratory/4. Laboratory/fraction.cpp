#include "fraction.hpp"
#include <numeric>

CFraction::CFraction ( long long int numerator, long long int denominator )
:m_numerator(numerator),
 m_denominator(denominator)
{
    if ( m_denominator < 0 )
    {
        m_numerator *= -1;
        m_denominator *= -1;
    }
    shrink();
}

CFraction operator + ( const CFraction & lhs, const CFraction & rhs )
{
    auto lcm = std::lcm(lhs.m_denominator, rhs.m_denominator);

    return {lhs.m_numerator*(lcm/lhs.m_denominator) + rhs.m_numerator*(lcm/rhs.m_denominator), lcm};
}

CFraction operator - ( const CFraction & lhs, const CFraction & rhs )
{
    return lhs + (-rhs);
}

CFraction operator * ( const CFraction & lhs, const CFraction & rhs )
{
    auto    gcd1 = std::gcd(std::abs(lhs.m_numerator), rhs.m_denominator),
        gcd2 = std::gcd(lhs.m_denominator, std::abs(rhs.m_numerator));

    return {(lhs.m_numerator/gcd1)*(rhs.m_numerator/gcd2), (lhs.m_denominator/gcd2)*(rhs.m_denominator/gcd1)};
}

CFraction operator / ( const CFraction & lhs, const CFraction & rhs )
{
    return lhs * CFraction(rhs.m_denominator, rhs.m_numerator);
}

CFraction & CFraction::operator += ( const CFraction & oth )
{
    return *this = *this + oth;
}

CFraction & CFraction::operator -= ( const CFraction & oth )
{
    return *this += (-oth);
}

CFraction & CFraction::operator *= ( const CFraction & oth )
{
    return *this = *this * oth;
}

CFraction & CFraction::operator /= ( const CFraction & oth )
{
    return *this *= CFraction(oth.m_denominator, oth.m_numerator);
}

CFraction CFraction::operator ++ ( int n )
{
    auto old = *this;
    if ( n == 0 )
        *this += 1;
    else
        *this += n;
    return old;
}

CFraction CFraction::operator -- ( int n )
{
    return operator++(n==0?-1:-n);
}

CFraction & CFraction::operator ++ ( void )
{
    return *this += 1;
}

CFraction & CFraction::operator -- ( void )
{
    return *this -= 1;
}

CFraction CFraction::operator - ( void ) const
{
    return {-m_numerator, m_denominator};
}

bool operator <  ( const CFraction & lhs, const CFraction & rhs )
{
    auto lcm = std::lcm(lhs.m_denominator, rhs.m_denominator);

    return lhs.m_numerator * (lcm/rhs.m_denominator) < rhs.m_numerator * (lcm/lhs.m_denominator);
}

bool operator <= ( const CFraction & lhs, const CFraction & rhs )
{
    return lhs < rhs || lhs == rhs;
}

bool operator == ( const CFraction & lhs, const CFraction & rhs )
{
    auto lcm = std::lcm(lhs.m_denominator, rhs.m_denominator);

    return lhs.m_numerator * (lcm/rhs.m_denominator) == rhs.m_numerator * (lcm/lhs.m_denominator);
}

bool operator != ( const CFraction & lhs, const CFraction & rhs )
{
    return !(lhs == rhs);
}

bool operator >= ( const CFraction & lhs, const CFraction & rhs )
{
    return rhs <= lhs;
}

bool operator >  ( const CFraction & lhs, const CFraction & rhs )
{
    return rhs < lhs;
}

std::ostream & operator << ( std::ostream & os, const CFraction & fraction )
{
    return os << fraction.m_numerator << "/" << fraction.m_denominator;
}

std::istream & operator >> ( std::istream & is, CFraction & fraction )
{
    decltype(CFraction::m_numerator) numerator = 0, denominator = 1;

    is >> numerator;

    if ( is && is.peek() == '/' )
        is.ignore(1) >> denominator;

    if ( is && denominator != 0 )
        fraction = CFraction(numerator, denominator);
    else
        is.setstate(std::ios::failbit);
    return is;
}

void CFraction::shrink ( void )
{
    auto gcd = std::gcd(std::abs(m_numerator), m_denominator);
    if ( gcd == 0 )
    {
        m_denominator = 1;
        return;
    }
    m_numerator   /= gcd;
    m_denominator /= gcd;
}
