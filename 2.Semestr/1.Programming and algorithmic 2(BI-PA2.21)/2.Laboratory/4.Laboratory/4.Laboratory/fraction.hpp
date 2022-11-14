#pragma once

#include <ostream>
#include <istream>

class CFraction
{
    public:
        CFraction ( long long int = 0, long long int = 1 );

        friend CFraction operator + ( const CFraction &, const CFraction & );
        friend CFraction operator - ( const CFraction &, const CFraction & );
        friend CFraction operator * ( const CFraction &, const CFraction & );
        friend CFraction operator / ( const CFraction &, const CFraction & );
        
        CFraction & operator += ( const CFraction & );
        CFraction & operator -= ( const CFraction & );
        CFraction & operator *= ( const CFraction & );
        CFraction & operator /= ( const CFraction & );
        
        CFraction operator ++ ( int n );
        CFraction operator -- ( int n );
        
        CFraction & operator ++ ( void );
        CFraction & operator -- ( void );

        CFraction operator - ( void ) const;

        friend bool operator <  ( const CFraction &, const CFraction & );
        friend bool operator <= ( const CFraction &, const CFraction & );
        friend bool operator == ( const CFraction &, const CFraction & );
        friend bool operator != ( const CFraction &, const CFraction & );
        friend bool operator >= ( const CFraction &, const CFraction & );
        friend bool operator >  ( const CFraction &, const CFraction & );

        friend std::ostream & operator << ( std::ostream &, const CFraction & );
        friend std::istream & operator >> ( std::istream &, CFraction & );
    private:
        void shrink ( void );
        long long int m_numerator;
        long long int m_denominator;
};
