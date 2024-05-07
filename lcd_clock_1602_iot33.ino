#include <DFRobot_RGBLCD1602.h>

#include <ezTime.h>
#include <Wire.h>
#include <WiFiNINA.h>

#include "DFRobot_RGBLCD1602.h"
DFRobot_RGBLCD1602 lcd(/*RGBAddr*/0x2D ,
                       /*lcdCols*/16,
                       /*lcdRows*/2
);  //16 characters and 2 lines of show

#include "credentials.h"
#include "charconvert.h"

//--Wifi credentials from Credentials.h
const char *ssid = SID;
const char *password = PW;

// make some custom characters:
// the 8 arrays that form each segment of the custom numbers
byte bar1[8] = {
  B11100,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11100
};
byte bar2[8] = {
  B00111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B00111
};
byte bar3[8] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte bar4[8] = {
  B11110,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B11100
};
byte bar5[8] = {
  B01111,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B00111
};
byte bar6[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte bar7[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00111,
  B01111
};
byte bar8[8] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

int status = WL_IDLE_STATUS;           // the Wi-Fi radio's status
const int intervalInfo = 5000;         // interval at which to update the board information

Timezone myTZ;
#define MYTIMEZONE "Australia/Brisbane"


void setup() {
  Serial.begin(9600);
  while (!Serial);

  lcd.init();

  // set the cursor to the top left
  lcd.setCursor(0, 0);
  lcd.write("Network Connect: ");
  lcd.setCursor(2, 1);
  lcd.write(ssid);
  
  // attempt to connect to Wi-Fi network:
  while (status != WL_CONNECTED) {
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, password);
  }
  // wait 10 seconds for connection:
  delay(10000);

  lcd.clear();
  lcd.write(" Connected! ");
  //lcd.setCursor(2, 1);
  //lcd.write(WiFi.localIP());  
  delay(5000);
  lcd.clear();


  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  Serial.println("---------------------------------------");

  //--Setup EZ Time
  setDebug(INFO);
  waitForSync();

  Serial.println();
  Serial.println("UTC:             " + UTC.dateTime());

  myTZ.setLocation(F(MYTIMEZONE));
  Serial.print(F("Time in your set timezone:         "));
  Serial.println(myTZ.dateTime());

  //Send custom characters to display
  //These are recorded to SerLCD and are remembered even after power is lost
  //There is a maximum of 8 custom characters that can be recorded
  lcd.customSymbol(1, bar1);
  lcd.customSymbol(2, bar2);
  lcd.customSymbol(3, bar3);
  lcd.customSymbol(4, bar4);
  lcd.customSymbol(5, bar5);
  lcd.customSymbol(6, bar6);
  lcd.customSymbol(7, bar7);
  lcd.customSymbol(8, bar8);
}

void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}

void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }      
}

int h1, h0, m1, m0;
bool iPM;

void updateTime() {
  String timeString = "";
  String AmPmString = "";
  timeString = myTZ.dateTime("hisv");
  time_t time = myTZ.now();
  iPM = isPM(time);
  Serial.print(iPM);

  m0 = charToInt(timeString[3]);
  m1 = charToInt(timeString[2]);
  h0 = charToInt(timeString[1]);
  h1 = charToInt(timeString[0]);
}

void loop() {
  int delayTime = 500;

  updateTime();

  if (h1 > 0) { printNumber(h1, 0); }
  else {
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(1, 0);
    lcd.print(" ");
    lcd.setCursor(1, 1);
    lcd.print(" ");
    lcd.setCursor(2, 0);
    lcd.print(" ");
    lcd.setCursor(2, 1);
    lcd.print(" ");
  }
  printNumber(h0, 3);
  printNumber(m1, 7);
  printNumber(m0, 10);

    lcd.setCursor(14, 0);
  if(iPM) {
    lcd.print("PM");
  } else {
    lcd.print("AM");
  }

  lcd.setCursor(6, 0);
  lcd.print(" ");
  lcd.setCursor(6, 1);
  lcd.print(" ");
  delay(delayTime);
  lcd.setCursor(6, 0);
  lcd.print(".");
  lcd.setCursor(6, 1);
  lcd.print(".");
  delay(delayTime);
}