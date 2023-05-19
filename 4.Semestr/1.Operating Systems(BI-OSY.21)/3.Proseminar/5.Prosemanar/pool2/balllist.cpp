#include <algorithm>
#include "balllist.h"
using namespace std;

//=================================================================================================
                   CBallList::CBallList                    ( void )
{
  // obe events jsou typu manual, aktualne jsou signalizovane
  m_Stop = CreateEvent ( NULL, TRUE, TRUE, NULL );
  m_Done = CreateEvent ( NULL, TRUE, TRUE, NULL );
  InitializeCriticalSection ( &m_Cs );
}
//-------------------------------------------------------------------------------------------------
                   CBallList::~CBallList                   ( void )
{
  Quit ();
  CloseHandle ( m_Stop );
  CloseHandle ( m_Done );
  DeleteCriticalSection ( &m_Cs );
}
//-------------------------------------------------------------------------------------------------
void               CBallList::SetPause                     ( bool              paused )
{
  if ( paused )
    ResetEvent ( m_Stop );
  else
    SetEvent ( m_Stop );
}
//-------------------------------------------------------------------------------------------------
bool               CBallList::GetPause                     ( void )
{
  // manual event - test, zda je signalizovana s timeoutem 0 msec (okamzite vraci stav)
  return WaitForSingleObject ( m_Stop, 0 ) == WAIT_TIMEOUT;
}
//-------------------------------------------------------------------------------------------------
void               CBallList::CreateBall                   ( void )
{
  ABall n = make_shared<CBall> ( m_Stop, this );
  
  EnterCriticalSection ( &m_Cs );
  m_Balls . push_back ( n );
  ResetEvent ( m_Done );
  LeaveCriticalSection ( &m_Cs );
  n -> Start ();
}
//-------------------------------------------------------------------------------------------------
void               CBallList::Draw                         ( HWND              hwnd,
                                                             HDC               hdc )
{
  RECT rc;
  GetClientRect ( hwnd, &rc );
  
  HDC     hdcBuff = CreateCompatibleDC ( hdc );
  HBITMAP bmpBuff = CreateCompatibleBitmap ( hdc, rc . right - rc . left, rc . bottom - rc . top );
  HBITMAP bmpOld = (HBITMAP) SelectObject ( hdcBuff, bmpBuff );

  FillRect ( hdcBuff, &rc, (HBRUSH) GetStockObject ( WHITE_BRUSH ) );
  
  EnterCriticalSection ( &m_Cs );
  for ( auto & b : m_Balls )
    b -> Draw ( hdcBuff );
  LeaveCriticalSection ( &m_Cs );
  BitBlt ( hdc, rc . left, rc . top, rc . right - rc . left, rc . bottom - rc . top, hdcBuff, 0, 0, SRCCOPY );

  SelectObject ( hdcBuff, bmpOld );
  DeleteObject ( bmpBuff );
  DeleteObject ( hdcBuff );
}
//-------------------------------------------------------------------------------------------------
void               CBallList::Quit                         ( void )
{
  // odblokujeme vlakna (pokud byla pozastavena)
  SetEvent ( m_Stop );
  // vsem vlaknum nastavime priznak "koncime" a cekame
  EnterCriticalSection ( &m_Cs );
  for ( auto & b : m_Balls )
    b -> Terminate ();
  LeaveCriticalSection ( &m_Cs );
  WaitForSingleObject ( m_Done, INFINITE );
  // m_Recycle muze obsahovatodkaz na posledni instanci CBall. Pri volani destruktoru ~CBallList
  // se zavola destruktor -> uvolni se 
}
//-------------------------------------------------------------------------------------------------
void               CBallList::Recycle                      ( ABall             b )
{
  ABall ballToDelete;
  
  EnterCriticalSection ( &m_Cs );
  auto i = find ( m_Balls . begin (), m_Balls . end (), b );
  if ( i != m_Balls . end () )
  {
    ballToDelete = m_Recycler;
    m_Recycler = *i;
    *i = m_Balls . back ();
    m_Balls . pop_back ();
  }
  if ( m_Balls . size () == 0 )
    SetEvent ( m_Done );    
  LeaveCriticalSection ( &m_Cs );
  // promenna ballToDelete zde zanika. Jedna se o posledni odkaz na drive recyklovany CBall ->  
  // zde se zavola jeho destruktor, tedy uklidi se jim alokovane prostredky (mj. ThreadHandle)
}
//=================================================================================================
