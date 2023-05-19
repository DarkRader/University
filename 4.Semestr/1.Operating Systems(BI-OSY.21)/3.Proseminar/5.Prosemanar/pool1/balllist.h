#ifndef __balllist_h__23065739576209345612340975__
#define __balllist_h__23065739576209345612340975__


#include "ball.h"
#include <vector>


class CBallList
{
  public:
                             CBallList                     ( void );
                             ~CBallList                    ( void );
    void                     SetPause                      ( bool              paused );
    bool                     GetPause                      ( void );
    void                     CreateBall                    ( void );
    void                     Draw                          ( HWND              hwnd,
                                                             HDC               hdc );
    void                     Quit                          ( void );
  private:
    // Event pozastaveni vlaken kulicek
    HANDLE                   m_Stop;
    // seznam instanci objektu
    std::vector<ABall>       m_Balls;
};

#endif /* __balllist_h__23065739576209345612340975__ */
