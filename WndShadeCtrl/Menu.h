#ifndef MENU_H
#define MENU_H

#include <inttypes.h>
#include "Settings.h"

class Menu;
class LiquidCrystal_I2C;
class Motor;

class Action
{
public:
  virtual ~Action() {};
  virtual void execute(Menu* menu) = 0;
};

class DisplayAction: public Action
{
public:
  virtual ~DisplayAction() {};
  void setOut(LiquidCrystal_I2C* out); 
  virtual void execute(Menu* menu);
private:
  void displaySubmenus(Menu* menu);
  void displayCurrentSettings(Menu* menu);
  LiquidCrystal_I2C* _lcd; 
};

class DisplayActionManualMenu : public DisplayAction
{
  void execute(Menu* menu);
};

class ManualCtrlAction: public Action
{
public:
  void execute(Menu* menu);
};

class AutoCtrlAction: public Action
{
public:
  void execute(Menu* menu);
};

class SensCtrlAction: public Action
{
public:
  void execute(Menu* menu);
};

class PeriodCtrlAction: public Action
{
public:
  void execute(Menu* menu);
};

class Menu 
{
public:
  virtual ~Menu();
  char* getName();
  virtual Menu* visit() = 0;
  virtual Menu* getSubMenuByIndex(uint8_t i) {return 0;}
  virtual uint8_t getCount() {return _count;}
  virtual uint8_t getPos() {return _pos;}
  virtual void scroll(bool up) {}
  virtual Settings& getSettings() {return _settings;};
  virtual void setSettings(Settings& s) {_settings = s;};
  static Settings _settings;
protected:
  char _name[12];
  uint8_t _pos:4;
  uint8_t _count:4;
};

class BackMenu: public Menu
{
public:
  BackMenu(Menu* parent);
  Menu* visit();
private:
  Menu* _parent;
};

class SubMenu: public Menu
{
public:
  SubMenu(char* title);
  void addMenu(Menu* menu);
  void addMenu(BackMenu* menu);
  void addAction(Action* action);
  Menu* visit();
  Menu* getSubMenuByIndex(uint8_t i);
  uint8_t getCount() {return _count;}
  uint8_t getPos() {return _pos;}
  virtual void scroll(bool up);
private:  
  Action* _action;
  Menu* _menus[5];
};

class ActionMenu: public Menu
{
public:
  ActionMenu(char* title);
  void addAction(Action* action);
  Menu* visit();
private:
  Action* _action;
};

#endif /* MENU_H */

