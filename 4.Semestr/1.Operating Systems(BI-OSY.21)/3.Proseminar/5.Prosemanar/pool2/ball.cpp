#include "ball.h"
#include "balllist.h"
using namespace std;
//=================================================================================================
                   CBall::CBall                            ( HANDLE            stopEvent,
                                                             CBallList       * list )
                   : m_X ( SIZE_X / 2 ),
                     m_Y ( SIZE_Y / 2 ),
                     m_vX ( 10 - 20.0 * rand () / RAND_MAX ),
                     m_vY ( 10 - 20.0 * rand () / RAND_MAX ),
                     m_Thread ( NULL ),
                     m_Stop ( stopEvent ),
                     m_Bounces ( 5 + (int)(10.0 * rand () / RAND_MAX ) ),
                     m_List ( list ),
                     m_Terminate ( false )

{
  // nahodna barva (vyber ze saturovanych barev)
  int ang = (int)(1536.0 * rand () / RAND_MAX );
  m_Color = RGB ( clipColor ( 512 - abs ( ang - 512 ) ),
                  clipColor ( abs ( ang - 768 ) - 256 ),
                  clipColor ( 512 - abs ( ang - 1024 ) ) );
  InitializeCriticalSection ( &m_Cs );
}
//-------------------------------------------------------------------------------------------------
               CBall::~CBall           ( void )
{
  // destruktor je volany z jineho vlakna nez vlakno m_Thread.
  WaitForSingleObject ( m_Thread, INFINITE );
  CloseHandle ( m_Thread );
  DeleteCriticalSection ( &m_Cs );
}
//-------------------------------------------------------------------------------------------------
void               CBall::Start                            ( void )
{
  DWORD dummy;
  // start vlakna. Parametrem je funkce vlakna. Zde to bude funkce (tridni metoda)
  // thrWrapper. Nemuze to byt primo metoda (funkce CreateThread neumi predat this).
  // pomocna tridni metoda dostane parametrem (void*) ukazatel na instanci. V ni spusti
  // metody thread - tu, ktera zajistuje vlasni beh vlakna.
  m_Thread = CreateThread ( NULL, 0, (DWORD (__stdcall *) ( void *))thrWrapper, this, 0, &dummy );
}
//-------------------------------------------------------------------------------------------------
void               CBall::Terminate                        ( void )
{
  m_Terminate = true;
}
//-------------------------------------------------------------------------------------------------
void               CBall::threadMethod                     ( void )
{
  while ( ! m_Terminate && m_Bounces )
  {
    // pokud mame zastavit simulaci
    WaitForSingleObject ( m_Stop, INFINITE );

    EnterCriticalSection ( &m_Cs );
    // zmena pozice v zamcenem kontextu - nemenime hodnoty pripadnemu prekresleni 
    changePosition ();
    LeaveCriticalSection ( &m_Cs );
    Sleep ( 30 );
  }  
  m_List -> Recycle ( shared_from_this () );
}
//-------------------------------------------------------------------------------------------------
DWORD WINAPI       CBall::thrWrapper                       ( CBall           * param )
{
  // pomocna funkce, ktera misto funkce vlakna vola metodu vlakna. Instanci dostane jako svuj
  // parametr. Soucasti zabavy je i chvile hrani s pretypovanim.
  param -> threadMethod ();
  return 0;
}
//-------------------------------------------------------------------------------------------------
int                CBall::clipColor                        ( int               x )
{
  if ( x < 0 ) 
    return 0;
  if ( x > 255 ) 
    return 255;
  return x;
}
//-------------------------------------------------------------------------------------------------
void               CBall::Draw                             ( HDC               hdc ) const
{ 
  // nakresleni na aktualni pozici
  // tato metoda je volana z vlakna obsluhy okna (pohyb)
  // aby byl pristup k promennym polohy m_X a m_Y atomicky 
  // (nekolidoval se zmenami pozice ve vlaknu kulicky),
  // zamykame pristup k m_X a m_Y

  HBRUSH br = CreateSolidBrush ( m_Color );
  HBRUSH old = (HBRUSH)SelectObject ( hdc, br );

  RECT rc;
  EnterCriticalSection ( &m_Cs );
  rc . left   = (int)(m_X - BALL_R);
  rc . top    = (int)(m_Y - BALL_R);
  rc . right  = (int)(m_X + BALL_R);
  rc . bottom = (int)(m_Y + BALL_R);
  LeaveCriticalSection ( &m_Cs );
  Ellipse ( hdc, rc . left, rc . top, rc . right, rc . bottom );

  SelectObject ( hdc, old );
  DeleteObject ( br );
}
//-------------------------------------------------------------------------------------------------
void               CBall::changePosition                   ( void )
{ 
  m_X += m_vX;
  m_Y += m_vY;
  if ( m_X < BALL_R )
  {
    m_X = 2 * BALL_R - m_X;
    m_vX = -m_vX;
    m_Bounces --;
  }
  if ( m_X > SIZE_X - BALL_R )
  {
    m_X = 2 * (SIZE_X-BALL_R) - m_X;
    m_vX = -m_vX;
    m_Bounces --;
  }
  if ( m_Y < BALL_R )
  {
    m_Y = 2 * BALL_R - m_Y;
    m_vY = -m_vY;
    m_Bounces --;
  }
  if ( m_Y > SIZE_Y - BALL_R )
  {
    m_Y = 2 * ( SIZE_Y - BALL_R ) - m_Y;
    m_vY = -m_vY;
    m_Bounces --;
  }
}
//=================================================================================================
