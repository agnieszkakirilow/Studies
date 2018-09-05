 #include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Settings.h"
#include "Menu.h"
#include "Motor.h"
#include "Navigator.h"
#include "Driver.h"

#define PIN_JOYSTICK_SENSOR_X A0
#define PIN_JOYSTICK_SENSOR_Y A1
#define PIN_JOYSTICK_BUTTON 7

#define PIN_MOTOR_PWM 5
#define PIN_MOTOR_IN_A1 4
#define PIN_MOTOR_IN_A2 6

int valX = 0;
int valY = 0;
uint8_t btn = 0;

Settings settings;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
Motor motor(PIN_MOTOR_PWM, PIN_MOTOR_IN_A1, PIN_MOTOR_IN_A2);

DisplayAction display;
DisplayActionManualMenu displayManual;
ManualCtrlAction manualCtrl;
AutoCtrlAction autoCtrl;
SensCtrlAction sensCtrl;
PeriodCtrlAction periodCtrl;

SubMenu root("root");
SubMenu control("control");

SubMenu automat("auto");
SubMenu manual("manual");
SubMenu set("settings");
BackMenu backToRoot(&root);

SubMenu periodicity("periodicity");
SubMenu sensitivity("sensitivity");
BackMenu backToCtrl(&control);

ActionMenu pos25("25%");
ActionMenu pos50("50%");
ActionMenu pos75("75%");
ActionMenu pos100("100%");
BackMenu backToSettings(&set);

ActionMenu min15("15min");
ActionMenu min30("30min");
ActionMenu min60("60min");

ActionMenu idle("\03");
ActionMenu up("\01");
ActionMenu down("\02");

Navigator navi;
Driver driver(&motor);

void setupMenu();

void setupLCD();

void setup() 
{
  setupMenu();
  
  pinMode(PIN_JOYSTICK_BUTTON, INPUT);//set joystick
  digitalWrite(PIN_JOYSTICK_BUTTON, HIGH) ;
  Serial.begin(9600);
  
  lcd.begin(20,4);//set lcd
  setupLCD();
  lcd.backlight();
  lcd.setCursor(0,0);
    
  root.visit();  
  navi.setMenu(&root);

  attachInterrupt(digitalPinToInterrupt(2), limitSensorDownISR, RISING);//pin number, ISR function(void,no params), mode(rising - goes from low to high)
  attachInterrupt(digitalPinToInterrupt(3), limitSensorUpISR, RISING);
}

void loop() 
{
  valX = analogRead(PIN_JOYSTICK_SENSOR_X);
  valY = analogRead(PIN_JOYSTICK_SENSOR_Y);
  btn = digitalRead(PIN_JOYSTICK_BUTTON);
  
  Settings& s = navi.navigate(valX, valY, btn);

  driver.control(s);
  
  delay(100);
}

void setupMenu()
{
  display.setOut(&lcd);
  displayManual.setOut(&lcd);
 
  root.addMenu(&control);
  root.addMenu(&backToRoot);
  root.addAction(&display);

  //control - SubMenu
  control.addMenu(&automat);
  control.addMenu(&set);
  control.addMenu(&manual);
  control.addMenu(&backToRoot);
  //display - DisplayAction
  control.addAction(&display);

  automat.addAction(&autoCtrl);

  //ActionMenu
  set.addMenu(&periodicity);
  set.addMenu(&sensitivity);
  set.addMenu(&backToCtrl);
  set.addAction(&display);

  periodicity.addMenu(&min15);
  periodicity.addMenu(&min30);
  periodicity.addMenu(&min60);
  periodicity.addMenu(&backToSettings);
  periodicity.addAction(&display);
  
  sensitivity.addMenu(&pos25);
  sensitivity.addMenu(&pos50);
  sensitivity.addMenu(&pos75);
  sensitivity.addMenu(&pos100);
  sensitivity.addMenu(&backToSettings);
  sensitivity.addAction(&display);
  
  manual.addMenu(&idle);
  manual.addMenu(&up);
  manual.addMenu(&down);
  manual.addMenu(&backToCtrl);
  manual.addAction(&displayManual);
  
  idle.addAction(&manualCtrl);
  up.addAction(&manualCtrl);
  down.addAction(&manualCtrl);

  min15.addAction(&periodCtrl);
  min30.addAction(&periodCtrl);
  min60.addAction(&periodCtrl);

  pos25.addAction(&sensCtrl);
  pos50.addAction(&sensCtrl);
  pos75.addAction(&sensCtrl);
  pos100.addAction(&sensCtrl);
}
/// 2

void setupLCD()
{
  byte upArrowIcon[] = {
    B00000,
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100
  };

  byte downArrowIcon[] = {
    B00100,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100,
    B00000,
  };

  byte stopIcon[] = {
    B00000,
    B01110,
    B11111,
    B10001,
    B10001,
    B11111,
    B01110,
    B00000
  };

  lcd.createChar(1, upArrowIcon);
  lcd.createChar(2, downArrowIcon);
  lcd.createChar(3, stopIcon);
}

void limitSensorDownISR()
{
  Serial.println("DOWN reached");
  Settings s = root.getSettings();
  if (s.dir == DIR_DOWN)
  {
    s.pos = POS_DOWN;
    s.dir = DIR_STOP;
    root.setSettings(s);
    
    driver.control(s);
  }
  else
  {
    Serial.println("  DIRECTION IS NOT DOWN - IGNORE EVENT !!!");
  }
}

void limitSensorUpISR()
{
  Serial.println("UP reached");
  Settings s = root.getSettings();
  if (s.dir == DIR_UP)
  {
    s.pos = POS_UP;
    s.dir = DIR_STOP;
    root.setSettings(s);
  
    driver.control(s);
  }
  else
  {
    Serial.println("  DIRECTION IS NOT UP - IGNORE EVENT !!!");
  }
}

