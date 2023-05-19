#include "balllist.h"
using namespace std;

//=================================================================================================
                   CBallList::CBallList                    ( void )
{
  // event je typu manual, signalizovana
  m_Stop = CreateEvent ( NULL, TRUE, TRUE, NULL );
}
//-------------------------------------------------------------------------------------------------
                   CBallList::~CBallList                   ( void )
{
  Quit ();
  CloseHandle ( m_Stop );
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
  ABall n = make_shared<CBall> ( m_Stop );
  
  m_Balls . push_back ( n );
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
  for ( auto & b : m_Balls )
    b -> Draw ( hdcBuff );
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
  for ( auto & b : m_Balls )
    b -> Terminate ();
  m_Balls . resize ( 0 );
}
//=================================================================================================
