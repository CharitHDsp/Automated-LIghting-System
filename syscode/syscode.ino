/*=============================================
    Program : Automated Lights
    Author : LAPTOP-MHHCOEAP\Charitha Dasanayake
    Time : 5:12 PM
    Date : 11/2/2023
    Created with Codino Studio
  =============================================*/

#include <LiquidCrystal.h>

#include <RTClib.h>

#include<Wire.h>

#include<EEPROM.h>

RTC_DS3231 rtc;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int dd, hh, Min;
int btn1Current, btn1Previos = LOW;
int btn2Current, btn2Previos = LOW;
int btn1Current1, btn1Previos1 = LOW;
int btn2Current1, btn2Previos1 = LOW;
int Hourcounter = 0;
int Minutecounter = 1;
int Hourcounter1 = 0;
int Minutecounter1 = 1;

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  lcd.begin(20,4);
  delay(3000);
  rtc.begin();

  displayMode();
  setStartTime();
  displayMode();
  setEndTime();
  lcd.setCursor(0, 3);
  lcd.print("Setup Over");
  delay(3000);
}

void loop() {
  displayDate();
  delay(1000);
  lcd.clear();
  DateTime now = rtc.now();
  if (now.hour() == Hourcounter && now.minute() == Minutecounter) {
    digitalWrite(10, HIGH);
  }
  else if (now.hour() == Hourcounter1 && now.minute() == Minutecounter1) {
    digitalWrite(10, LOW);
  }
}
void displayDate() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print(now.year());
  lcd.setCursor(4, 0);
  lcd.print("/");
  lcd.setCursor(5, 0);
  lcd.print(now.month());
  lcd.setCursor(7, 0);
  lcd.print("/");
  lcd.setCursor(8, 0);
  lcd.print(now.day());
  lcd.setCursor(10, 0);
  lcd.print(" ");
  lcd.setCursor(11, 0);
  lcd.print(now.hour());
  lcd.setCursor(13, 0);
  lcd.print(":");

  lcd.setCursor(14, 0);
  lcd.print(now.minute());
  lcd.setCursor(16, 0);
  lcd.print(":");
  lcd.setCursor(17, 0);
  lcd.print(now.second());
  lcd.println();
  lcd.setCursor(0, 1);
  lcd.print("Start Time:");
  lcd.setCursor(12, 1);
  lcd.print(Hourcounter);
  lcd.setCursor(14, 1);
  lcd.print(":");
  lcd.setCursor(15, 1);
  lcd.print(Minutecounter);
  lcd.setCursor(0, 2);
  lcd.print("End Time:");
  lcd.setCursor(12, 2);
  lcd.print(Hourcounter1);
  lcd.setCursor(14, 2);
  lcd.print(":");
  lcd.setCursor(15, 2);
  lcd.print(Minutecounter1);
}
void displayMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter New Date&Time");
  lcd.setCursor(0, 1);
  lcd.print("Press Button 1");
  lcd.setCursor(0, 2);
  lcd.print("Get Pre Date&Time");
  lcd.setCursor(0, 3);
  lcd.print("Press Button 2");
}
void setStartTime() {
  while (true) {
    btn1Current = digitalRead(7);
    btn2Current = digitalRead(8);
    if (btn1Current == LOW && btn1Previos == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select 1");

      lcd.setCursor(0, 1);
      lcd.print("Enter Hour: ");
      while (true) {
        btn1Current1 = digitalRead(7);
        btn2Current1 = digitalRead(8);
        if (btn1Current1 == LOW && btn1Previos1 == HIGH) {
          Hourcounter++;
          lcd.setCursor(15, 1);
          lcd.print(Hourcounter);
          if (Hourcounter == 24) {
            Hourcounter = 0;
          }
        }
        if (btn2Current1 == LOW && btn2Previos1 == HIGH) {
          break;
        }
        btn1Previos1 = btn1Current1;
        btn2Previos1 = btn2Current1;
      }
      btn1Previos1 = LOW;
      btn2Previos1 = LOW;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Enter minutes: ");
      while (true) {
        btn1Current1 = digitalRead(7);
        btn2Current1 = digitalRead(8);
        if (btn1Current1 == LOW && btn1Previos1 == HIGH) {
          Minutecounter++;
          lcd.setCursor(15, 1);
          lcd.print(Minutecounter);
          if (Minutecounter == 60) {
            Minutecounter = 0;
          }
        }
        if (btn2Current1 == LOW && btn2Previos1 == HIGH) {
          break;
        }
        btn1Previos1 = btn1Current1;

        btn2Previos1 = btn2Current1;
      }
      EEPROM.update(0, Hourcounter);
      EEPROM.update(1, Minutecounter);
      break;
    }
    else if (btn2Current == LOW && btn2Previos == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select 2");
      Hourcounter = EEPROM.read(0);
      Minutecounter = EEPROM.read(1);
      break;
    }
    btn1Previos = btn1Current;
    btn2Previos = btn2Current;
  }
}
void setEndTime() {
  btn1Previos = LOW;
  btn2Previos = LOW;
  while (true) {
    btn1Current = digitalRead(7);
    btn2Current = digitalRead(8);
    if (btn1Current == LOW && btn1Previos == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select 1");
      lcd.setCursor(0, 1);
      lcd.print("Enter Hour: ");
      btn1Previos1 = LOW;
      btn2Previos1 = LOW;
      while (true) {
        btn1Current1 = digitalRead(7);
        btn2Current1 = digitalRead(8);
        if (btn1Current1 == LOW && btn1Previos1 == HIGH) {
          Hourcounter1++;
          lcd.setCursor(15, 1);

          lcd.print(Hourcounter1);
          if (Hourcounter1 == 24) {
            Hourcounter1 = 0;
          }
        }
        if (btn2Current1 == LOW && btn2Previos1 == HIGH) {
          break;
        }
        btn1Previos1 = btn1Current1;
        btn2Previos1 = btn2Current1;
      }
      btn1Previos1 = LOW;
      btn2Previos1 = LOW;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Enter minutes: ");
      while (true) {
        btn1Current1 = digitalRead(7);
        btn2Current1 = digitalRead(8);
        if (btn1Current1 == LOW && btn1Previos1 == HIGH) {
          Minutecounter1++;
          lcd.setCursor(15, 1);
          lcd.print(Minutecounter1);
          if (Minutecounter1 == 60) {
            Minutecounter1 = 0;
          }
        }
        if (btn2Current1 == LOW && btn2Previos1 == HIGH) {
          break;
        }
        btn1Previos1 = btn1Current1;
        btn2Previos1 = btn2Current1;
      }
      EEPROM.update(2, Hourcounter1);
      EEPROM.update(3, Minutecounter1);

      break;
    }
    else if (btn2Current == LOW && btn2Previos == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select 2");
      Serial.println("Select 2");
      Hourcounter1 = EEPROM.read(2);
      Minutecounter1 = EEPROM.read(3);
      break;
    }
    btn1Previos = btn1Current;
    btn2Previos = btn2Current;
  }
}

