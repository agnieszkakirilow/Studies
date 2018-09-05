#include "Navigator.h"
#include "Menu.h"

#include <HardwareSerial.h>

Navigator::Navigator() : _state(IDLE)
{
}

Navigator::~Navigator() 
{
}

void Navigator::setMenu(Menu* menu)//root
{
  _menu = menu;
}

Settings& Navigator::navigate(int x, int y, int pushed)
{
  switch(_state)
  {
    case IDLE:
    {
      if ((diff(x, CENTRAL_POSITION) < THRESHOLD) && (diff(y, CENTRAL_POSITION) > THRESHOLD))
      {
        _state = getVertical(y, CENTRAL_POSITION);
      }
      else if ((diff(x, CENTRAL_POSITION) > THRESHOLD) && (diff(y, CENTRAL_POSITION) < THRESHOLD))
      {
        _state = getHorizontal(x, CENTRAL_POSITION);
      }
      else
      {
        if (pushed == 0)
        {
          int pos = _menu->getPos();
          Menu* tmp = _menu->getSubMenuByIndex(pos);
          tmp->visit();
          // refresh lcd
          _menu->visit();
        }
      }
      break;
    }
    case UP:
    case DOWN:
    {
      if((diff(y, CENTRAL_POSITION) < THRESHOLD) && (diff(x, CENTRAL_POSITION) < THRESHOLD))
      {
        _menu->scroll((_state == UP) ? true : false);
        _menu->visit();
        _state = IDLE;
      }
      break;
    }
    case LEFT:
    {
      if((diff(y, CENTRAL_POSITION) < THRESHOLD) && (diff(x, CENTRAL_POSITION) < THRESHOLD))
      {
        _menu = _menu->getSubMenuByIndex(_menu->getCount());
        _menu = _menu->visit();
        _menu = _menu->visit();
        _state = IDLE;
      }
      break;
    }
    case RIGHT:
    {
      if((diff(y, CENTRAL_POSITION) < THRESHOLD) && (diff(x, CENTRAL_POSITION) < THRESHOLD))
      {
        Menu* m_tmp = _menu->getSubMenuByIndex(_menu->getPos());
        if(m_tmp->getCount() > 0)
        {
          _menu = m_tmp;
          _menu->visit();
        }
        else
        {
          m_tmp->visit();
          // refresh lcd
          _menu->visit();
        }
        _state = IDLE;
      }
      break;
    }
  }
  return _menu->getSettings();
}

int Navigator::diff(int x, int y)
{
  if (x > y)
  {
    return x - y;
  }
  else
  {
    return y - x;
  }
}

Navigator::EState Navigator::getHorizontal(int x, int xConst)
{
  if (x > xConst)
  {
    return RIGHT;
  }
  else
  {
    return LEFT;
  }
}

Navigator::EState Navigator::getVertical(int y, int yConst)
{
  if (y < yConst)
  {
    return UP;
  }
  else
  {
    return DOWN;
  }
}

