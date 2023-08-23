// ENGR 111 Cornerstone Project Skeleton Code

#include <LiquidCrystal_I2C.h>

/**********************************************************/
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/**********************************************************/

// pin assignments (2 & 3 are the only iterrupt pins)
const int tachPin = 2;
const int buttonPin = 3;
const int motorPin = A0;

// LCD settings
int displaySetting = 1;
const int maxDisplays = 5;
unsigned long lastDisplaySwitch = millis();
const int displayDelay = 250;
int flag = 0;

// YOUR GLOBAL VARIABLES SHOULD BE DECLARED HERE
float startTime = 0;
float breakCount = 0;
float RPM_calc;
float endTime;
float changeTime;
const float FanSpeed = 21;
const float powerWind = (0.50 * 1.225 * (FanSpeed * FanSpeed * FanSpeed) * 21);
float pWindmillShaft;
float volts;
float pElec;
float bladeE;
float motorE;
float sysE;

void setup() {
  // initialize LCD & its backlight
  lcd.init();
  lcd.backlight();

  // initialize pushbutton for LCD toggle
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeDisplaySettingFlag, FALLING);

  // initialize proximity sensor
  pinMode(tachPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(tachPin), broken, FALLING);

  // initialize motor input
  pinMode(motorPin, INPUT);

  // start timer for RPM calculation
  startTime = millis();
}

void loop() {
  //YOUR CODE GOES HERE!!!
  //BE SURE TO CREATE ANY VARIABLES YOU NEED IN THE 'Global Variables' ABOVE
  //REMEMBER TO COMMENT EACH SECTION OF CODE YOU WRITE INSIDE OF THE VOID LOOP!

  endTime = millis();                             
  changeTime = ((endTime - startTime) / 60000.0);          
  RPM_calc = ((breakCount / 6.0) / changeTime);
  pWindmillShaft = ((RPM_calc * 21) / 9549) * 1000;
  volts = (5.0 * analogRead(motorPin)) / 1023;
  pElec = (volts * volts) / 21;
  bladeE = (pWindmillShaft/powerWind) * 100;
  motorE = (pElec/pWindmillShaft) * 100;
  sysE = (pElec/powerWind) * 100;
  startTime = millis();
  breakCount = 0; 

  
  if(flag == 1) 
  {
    flag = 0;
    changeDisplaySetting();
    
  }

  delay(1000);
  displayLCD();
  
}

//Call this function when you want to update the LCD Display
void displayLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch(displaySetting)
  {
    case 1:
    lcd.print("Windmill RPM: ");
    lcd.setCursor(0, 1);
    lcd.print(RPM_calc);
    break;
    case 2:
    lcd.print("System pow. out: ");
    lcd.setCursor(0, 1);
    lcd.print(pElec);
    break;
    case 3:
    lcd.print("Blade Eff.: ");
    lcd.setCursor(0, 1);
    lcd.print(bladeE);
    break;
    case 4:
    lcd.print("Motor Eff.: ");
    lcd.setCursor(0, 1);
    lcd.print(motorE);
    break;
    case 5:
    lcd.print("System Eff.: ");
    lcd.setCursor(0, 1);
    lcd.print(sysE);
    break;
    default:
    lcd.print("Unknown Setting!");
  }
}

void changeDisplaySettingFlag() {
    flag = 1;
}

void changeDisplaySetting() {
    if(lastDisplaySwitch + displayDelay < millis()) { // this limits how quickly the LCD Display can switch
    lastDisplaySwitch = millis();
    displaySetting++;
    if(displaySetting > maxDisplays) {
      displaySetting = 1;
    }
    displayLCD();
  }
}

void broken() {
  breakCount++;
}
