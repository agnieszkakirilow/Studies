#include "Menu.h"
#include "Motor.h"
#include "Settings.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

Settings Menu::_settings;
	
Menu::~Menu() {}

char* Menu::getName()
{
  return _name;
}

SubMenu::SubMenu(char* title) : Menu()
{
  strcpy(_name, title);
}

void SubMenu::addMenu(Menu* menu)
{
  _menus[_count] = menu;
  _count++;
}

void SubMenu::addMenu(BackMenu* menu)
{
  _menus[_count] = menu;
}

void SubMenu::addAction(Action* action)
{
  _action = action;
}
    
Menu* SubMenu::getSubMenuByIndex(uint8_t i)
{
  return _menus[i];
}

void SubMenu::scroll(bool up)
{
  if (up)
  {
    if (_pos > 0)
    {
      _pos--;
    }
  }
  else
  {
    if (_pos < _count - 1)
    {
      _pos++;
    }
  }
}

Menu* SubMenu::visit()
{
  _action->execute(this);
  return this;
}

ActionMenu::ActionMenu(char* title)
{
  strcpy(_name, title);
}

void ActionMenu::addAction(Action* action)
{
  _action = action;
}

Menu* ActionMenu::visit()
{
  _action->execute(this);
  return this;
}

BackMenu::BackMenu(Menu* parent)
{
  _parent = parent;
  strcpy(_name, "back");
}

Menu* BackMenu::visit()
{
  return _parent;
}

void DisplayAction::setOut(LiquidCrystal_I2C* out)
{
  _lcd = out;
}

void DisplayAction::execute(Menu* menu)
{
  displaySubmenus(menu);
  displayCurrentSettings(menu);
}

void DisplayAction::displaySubmenus(Menu* menu)
{
  _lcd->clear();
  for (uint8_t i = 0; i < menu->getCount(); i++)
  {
    _lcd->setCursor(0, i);
    if (i == menu->getPos())
    {
      _lcd->print(">");//print data to lcd in ascii code
    }
    else
    {
      _lcd->print(" ");
    }
    _lcd->print(menu->getSubMenuByIndex(i)->getName());
  }
}
  
void DisplayAction::displayCurrentSettings(Menu* menu)
{
  Settings s = menu->getSettings();
  if (s.mode == MODE_MANUAL)
  {
    _lcd->setCursor(15, 0);
    _lcd->print("M");
  }
  else
  {
    _lcd->setCursor(15, 0);
    _lcd->print("A");
  }
  
  _lcd->setCursor(15, 1);
  _lcd->print("S:");
  _lcd->print((s.sensitivity + 1) * 25, DEC);

  _lcd->setCursor(15, 2);
  _lcd->print("P:");
  _lcd->print((s.periodicity * 15), DEC);
  _lcd->setCursor(15, 3);
  _lcd->print("p:");
  _lcd->print(s.pos, DEC);
}

void DisplayActionManualMenu::execute(Menu* menu)
{
  Settings s = menu->getSettings();
  s.mode = MODE_MANUAL;
  s.periodicityChanged = false;
  menu->setSettings(s);
  
  DisplayAction::execute(menu);
}

void ManualCtrlAction::execute(Menu* menu)
{
  Settings s = menu->getSettings();
  s.mode = MODE_MANUAL;
  s.periodicityChanged = false;
  if (strcmp(menu->getName(), "\01") == 0)
  {
      Serial.print("---------- UP");
    s.pos = POS_MIDDLE;
    s.dir = DIR_UP;
  }
  else if (strcmp(menu->getName(), "\02") == 0)
  {
    Serial.print("---------- DOWN");
    s.pos = POS_MIDDLE;
    s.dir = DIR_DOWN;
   }
  else
  {
    Serial.print("---------- STOP");
    s.dir = DIR_STOP;
  }
  menu->setSettings(s);
}

void AutoCtrlAction::execute(Menu* menu)
{
  Serial.println("AUTO MODE");
  Settings s = menu->getSettings();
  s.mode = MODE_AUTO;
  s.periodicityChanged = true;//reset timer
  menu->setSettings(s);
}

void SensCtrlAction::execute(Menu* menu)
{
  Settings s = menu->getSettings();
  if (strcmp(menu->getName(), "25%") == 0)
  {
    s.sensitivity = SENS_25;
  }
  else if (strcmp(menu->getName(), "50%") == 0)
  {
    s.sensitivity = SENS_50;
  }
  else if (strcmp(menu->getName(), "75%") == 0)
  {    
    s.sensitivity = SENS_75;
  }
  else
  {    
    s.sensitivity = SENS_100 ;
  }
  menu->setSettings(s);
}

void PeriodCtrlAction::execute(Menu* menu)
{
  Settings s = menu->getSettings();
  uint8_t prevPeriodicity = s.periodicity;
  
  if (strcmp(menu->getName(), "15min") == 0)
  {
    s.periodicity = PERIOD_15;
  }
  else if (strcmp(menu->getName(), "30min") == 0)
  {
    s.periodicity = PERIOD_30;
  }
  else
  {    
    s.periodicity = PERIOD_60;
  }

  s.periodicityChanged =  (s.periodicity == prevPeriodicity) ? false : true;

  menu->setSettings(s);
}

