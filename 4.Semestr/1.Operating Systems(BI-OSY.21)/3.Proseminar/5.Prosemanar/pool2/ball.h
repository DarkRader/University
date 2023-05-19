#ifndef __ball_h__56230568326534067345__
#define __ball_h__56230568326534067345__

#include <windows.h>
#include <memory>


const int SIZE_X    = 600;
const int SIZE_Y    = 600;

class CBallList;

class CBall : public std::enable_shared_from_this<CBall>
{
  public:
    // konstruktor - nahodny
                             CBall                         ( HANDLE            stopEvent,
                                                             CBallList       * list );
    // destruktor
                             ~CBall                        ( void );
    // start the thread
    void                     Start                         ( void );
    // stop the thread
    void                     Terminate                     ( void );
    // zamceni + vykresleni na aktualni pozici.
    void                     Draw                          ( HDC               hdc ) const;
  private:
    static const int BALL_R    = 8;
    static const int MAX_BALLS = 100;

    // pomocna funkce na omezeni rozsahu 0-255
    static int               clipColor                     ( int               x );
    // prepocet pozice. Volat ze zamceneho kontextu
    void                     changePosition                ( void );
    // pomocna funkce pro startovani vlakna (CreateThread chce funkci, tato staticka metoda
    // (= funkce) volani prehodi na metodu
    static DWORD WINAPI      thrWrapper                    ( CBall           * param );
    // metoda vlakna
    void                     threadMethod                  ( void );
  
  
    double                   m_X, m_Y;    // pozice
    double                   m_vX, m_vY;  // slozky rychlosti
    COLORREF                 m_Color;     // barva
    HANDLE                   m_Thread;    // HANDLE vlakna
    HANDLE                   m_Stop;      // HANDLE udalosti
    int                      m_Bounces;   // pocet odrazu, dokud kulicka "neumre"
    CBallList              * m_List;      // odkaz na seznam 
    mutable CRITICAL_SECTION m_Cs;        // kriticka sekce
    bool                     m_Terminate; // priznak ukonceni vlakna "zvenku"
};

typedef std::shared_ptr<CBall> ABall;


#endif /* __ball_h__56230568326534067345__ */