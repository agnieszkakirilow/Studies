#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Settings.h"

class Menu;

class Navigator 
{
public:
  Navigator();
  virtual ~Navigator();
    
  Settings& navigate(int x, int y, int pushed);
  void setMenu(Menu* menu);
private:
  enum EState
  {
    IDLE = 0,
    UP,
    RIGHT,
    DOWN,
    LEFT
  };
    
  int diff(int x, int y);
  EState getHorizontal(int x, int xConst);
  EState getVertical(int y, int yConst);
  EState _state;
    
  Menu* _menu;
    
  const int CENTRAL_POSITION = 493;
  const int THRESHOLD = 100;
};

#endif /* NAVIGATOR_H */

