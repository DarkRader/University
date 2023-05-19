/* V teto verze prubezne ubyvaji instance CBall - po urcitem poctu odrazu se vlakno CBall ukonci. 
 * Na ukonceni vlakna je potreba reagovat: odstranit instanci CBall ze seznamu v CBallList a zlikvidivat vlakno
 * pouzivane v koncici instanci CBall. Nad koncicim vlaknem je potreba provest volani CloseHandle, ale zaroven
 * je potreba zabranit potencialni race-condition (ukoncuje se vlakno CBall a zaroven se ukoncuje cely program, 
 * pri nevhodnem planovani by se mohl program ukoncit drive, nez skonci vlakno).
 *
 * Resenim je, ze se koncici vlakno X podiva do "recyklatoru" - zkontroluje, zda nejake vlakno Y koncilo jiz pred nim.
 * Pokud ano, zavola na vlakne Y WaitForSingleObject (thread), tedy pocka na jeho dobehnuti a zlikviduje
 * prostredky alokovane Y. Nasledne se vlakno X zapise do "recyklatoru".
 *
 * Vyhodou je, vlakna mohou probezne vznikat/koncit a se nikde nehromadi neuvolnene prostredy vlaken (jsou 
 * prubezne likvidovane). Rezie je maximalne jedno vlakno v recyklatoru. Overte si, zkuste si umistit logovani 
 * do destruktoru CBall.
 */
#include <windows.h>
#include <cstdio>
#include "ball.h"
#include "balllist.h"
using namespace std;

static const char mainWndClass [] = "MainWndClass";
//-------------------------------------------------------------------------------------------------
static LRESULT CALLBACK mainWndCallback                    ( HWND              hwnd,
                                                             unsigned          Msg,
                                                             WPARAM            wparam,
                                                             LPARAM            lparam )
{ 
  // tato funkce je callback okna. Udalosti z GUI (stisk klaves, mys, ...) prochazeji touto funkci,
  // ono na ne ma sanci reagovat.
  // V nasem pripade budeme reagovat na stisk tlacitka mysi - leve vytvori novou kulicku, prave pusti/pozastavi
  // siulaci.
  // dale reagujeme na zadost o prekresleni - volame Draw.
  PAINTSTRUCT ps;
  CBallList * bl = (CBallList *) GetWindowLong ( hwnd, GWL_USERDATA );

  switch ( Msg )
  {
    case WM_CREATE:
      SetCursor ( LoadCursor ( NULL, IDC_ARROW ) );
      SetWindowLong ( hwnd, GWL_USERDATA, (LONG) (((CREATESTRUCT *) lparam ) -> lpCreateParams) ); \
      SetTimer ( hwnd, 1, 20, NULL );
      break;
  
    case WM_DESTROY:
      PostQuitMessage ( 0 );
      break;
  
    case WM_LBUTTONDOWN:
      bl -> CreateBall ();
      break;
    
    case WM_RBUTTONDOWN:
      bl -> SetPause ( ! bl -> GetPause () );
      break;
    
    case WM_TIMER:
      if ( wparam == 1 )
      {
        InvalidateRect ( hwnd, NULL, FALSE );
        UpdateWindow ( hwnd );
      }
      break;
  
    case WM_PAINT:
      BeginPaint ( hwnd, &ps );
      bl -> Draw ( hwnd, ps . hdc );
      EndPaint ( hwnd, &ps );
      break;
  }
  return DefWindowProc ( hwnd, Msg, wparam, lparam );
}
//-------------------------------------------------------------------------------------------------
int PASCAL         WinMain                                 ( HINSTANCE         MyInstance,
                                                             HINSTANCE         PrevInstance,
                                                             LPSTR             cmd,
                                                             int               cmdShow )
{
  MSG        msg;
  WNDCLASS   wc;
  HWND       mainWnd;
  CBallList  ballList;
  
  // inicializace okna
  wc . style        = CS_HREDRAW | CS_VREDRAW;
  wc . lpfnWndProc  = mainWndCallback;
  wc . cbClsExtra   = 0;
  wc . cbWndExtra   = sizeof ( DWORD );
  wc . hInstance    = GetModuleHandle ( NULL );
  wc . hIcon        = NULL;
  wc . hCursor      = NULL;
  wc . hbrBackground= (HBRUSH)GetStockObject ( WHITE_BRUSH );
  wc . lpszMenuName = NULL;
  wc . lpszClassName= mainWndClass;

  if ( !RegisterClass ( &wc ) ) 
    return 0;


  mainWnd = CreateWindow ( mainWndClass, "Crazy pool simulator", (WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS) & ~ WS_THICKFRAME,
                          CW_USEDEFAULT, CW_USEDEFAULT, SIZE_X + 2 * GetSystemMetrics ( SM_CXFRAME ),
                          SIZE_Y + 2*GetSystemMetrics ( SM_CYFRAME ) + GetSystemMetrics ( SM_CYCAPTION ),
                          NULL, NULL, GetModuleHandle ( NULL ), (void*) &ballList );

  ShowWindow ( mainWnd, SW_SHOW );
  // smycka udalosti. Hlavni vlakno Win aplikace typicky
  // cte v nekonecne smycce svoji frontu udalosti a na udalosti reaguje.
  while ( GetMessage ( &msg, NULL, 0, 0 ) )
  {
    TranslateMessage ( &msg );
    DispatchMessage ( &msg );
  }
  // smycka udalosti je opustena pri konci programu (zavreni okna)
  return 0;
}
//-------------------------------------------------------------------------------------------------
