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
    void                     Recycle                       ( ABall             b );
  private:
    // Event pozastaveni vlaken kulicek
    HANDLE                   m_Stop;
    // Event pro signalizaci "vlakna vsech micku dobehla", tedy m_Balls je prazdne
    HANDLE                   m_Done;
    // seznam instanci objektu
    std::vector<ABall>       m_Balls;
    // zamek pro manipulaci s polem m_Balls
    CRITICAL_SECTION         m_Cs;
    // micek, ktery skoncil (a ktery ceka na destrukci)
    ABall                    m_Recycler;
};

#endif /* __balllist_h__23065739576209345612340975__ */
