# 1 "F:\\project\\last_sim_code\\syscode\\syscode.ino"
# 1 "F:\\project\\last_sim_code\\syscode\\syscode.ino"
# 2 "F:\\project\\last_sim_code\\syscode\\syscode.ino" 2

# 4 "F:\\project\\last_sim_code\\syscode\\syscode.ino" 2

# 6 "F:\\project\\last_sim_code\\syscode\\syscode.ino" 2

# 8 "F:\\project\\last_sim_code\\syscode\\syscode.ino" 2
# 9 "F:\\project\\last_sim_code\\syscode\\syscode.ino" 2

RTC_DS3231 rtc;
//LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int dd, hh, Min;
int btn1Current, btn1Previos = 0x0;
int btn2Current, btn2Previos = 0x0;
int btn1Current1, btn1Previos1 = 0x0;
int btn2Current1, btn2Previos1 = 0x0;
int Hourcounter = 0; //was 1
int Minutecounter = 1;
int Hourcounter1 = 0; //was 1
int Minutecounter1 = 1;

void setup() {
  pinMode(7, 0x2);
  pinMode(8, 0x2);
  pinMode(10, 0x1);
 // lcd.init();
//  lcd.backlight();
  Serial.begin(9600);
  lcd.begin(20,4);
  delay(3000);
  rtc.begin();

  displayMode();
  serialmon(); //clean
 // delay(2000);
  setStartTime();
  displayMode();
  serialmon(); //clean
 // delay(2000);
  setEndTime();
  lcd.setCursor(0, 3);
  lcd.print("Setup Over");
  delay(3000);
}

void loop() {
  displayDate();
  displaydate(); //clean
  delay(1000);
  lcd.clear();
  DateTime now = rtc.now();
  if (now.hour() == Hourcounter && now.minute() == Minutecounter) {
    digitalWrite(10, 0x1);
  }
  else if (now.hour() == Hourcounter1 && now.minute() == Minutecounter1) {
    digitalWrite(10, 0x0);
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
    if (btn1Current == 0x0 && btn1Previos == 0x1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select 1");
      Serial.println("Select 1"); //clean

      lcd.setCursor(0, 1);
      lcd.print("Enter Hour: ");
      Serial.println("Enter Hour: "); //clean
      while (true) {
        btn1Current1 = digitalRead(7);
        btn2Current1 = digitalRead(8);
        if (btn1Current1 == 0x0 && btn1Previos1 == 0x1) {
          Hourcounter++;
          lcd.setCursor(15, 1);
          lcd.print(Hourcounter);
          Serial.println(Hourcounter); //clean
          if (Hourcounter == 24) {
            Hourcounter = 0;
          }
        }
        if (btn2Current1 == 0x0 && btn2Previos1 == 0x1) {
          break;
        }
        btn1Previos1 = btn1Current1;
        btn2Previos1 = btn2Current1;
      }
      btn1Previos1 = 0x0;
      btn2Previos1 = 0x0;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Enter minutes: ");
      Serial.println("Enter minutes: "); //clean
      while (true) {
        btn1Current1 = digitalRead(7);
        btn2Current1 = digitalRead(8);
        if (btn1Current1 == 0x0 && btn1Previos1 == 0x1) {
          Minutecounter++;
          lcd.setCursor(15, 1);
          lcd.print(Minutecounter);
          Serial.println(Minutecounter); //clean
          if (Minutecounter == 60) {
            Minutecounter = 0;
          }
        }
        if (btn2Current1 == 0x0 && btn2Previos1 == 0x1) {
          break;
        }
        btn1Previos1 = btn1Current1;

        btn2Previos1 = btn2Current1;
      }
      EEPROM.update(0, Hourcounter);
      EEPROM.update(1, Minutecounter);
      break;
    }
    else if (btn2Current == 0x0 && btn2Previos == 0x1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select 2");
      Serial.println("Select 2"); //clean
      Hourcounter = EEPROM.read(0);
      Minutecounter = EEPROM.read(1);
      break;
    }
    btn1Previos = btn1Current;
    btn2Previos = btn2Current;
  }
}
void setEndTime() {
  btn1Previos = 0x0;
  btn2Previos = 0x0;
  while (true) {
    btn1Current = digitalRead(7);
    btn2Current = digitalRead(8);
    if (btn1Current == 0x0 && btn1Previos == 0x1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select 1");
      Serial.println("Select 1"); //clean
      lcd.setCursor(0, 1);
      lcd.print("Enter Hour: ");
      Serial.println("Enter Hour: "); //clean
      btn1Previos1 = 0x0;
      btn2Previos1 = 0x0;
      while (true) {
        btn1Current1 = digitalRead(7);
        btn2Current1 = digitalRead(8);
        if (btn1Current1 == 0x0 && btn1Previos1 == 0x1) {
          Hourcounter1++;
          lcd.setCursor(15, 1);

          lcd.print(Hourcounter1);
          Serial.println(Hourcounter1); //clean
          if (Hourcounter1 == 24) {
            Hourcounter1 = 0;
          }
        }
        if (btn2Current1 == 0x0 && btn2Previos1 == 0x1) {
          break;
        }
        btn1Previos1 = btn1Current1;
        btn2Previos1 = btn2Current1;
      }
      btn1Previos1 = 0x0;
      btn2Previos1 = 0x0;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Enter minutes: ");
      Serial.println("Enter minutes: "); //clean
      while (true) {
        btn1Current1 = digitalRead(7);
        btn2Current1 = digitalRead(8);
        if (btn1Current1 == 0x0 && btn1Previos1 == 0x1) {
          Minutecounter1++;
          lcd.setCursor(15, 1);
          lcd.print(Minutecounter1);
          Serial.println(Minutecounter1); //clean
          if (Minutecounter1 == 60) {
            Minutecounter1 = 0;
          }
        }
        if (btn2Current1 == 0x0 && btn2Previos1 == 0x1) {
          break;
        }
        btn1Previos1 = btn1Current1;
        btn2Previos1 = btn2Current1;
      }
      EEPROM.update(2, Hourcounter1);
      EEPROM.update(3, Minutecounter1);

      break;
    }
    else if (btn2Current == 0x0 && btn2Previos == 0x1) {
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

void serialmon() {
  Serial.println("Enter New Date & Time");
  Serial.println("Press Button 1");
  Serial.println("Get Pre Date & Time");
  Serial.println("Press Button 2");
}

void displaydate() { //clean
  DateTime now = rtc.now();
  Serial.println(now.year());
  Serial.println("/");
  Serial.println(now.month());
  Serial.println("/");
  Serial.println(now.day());
  Serial.println(" ");
  Serial.println(now.hour());
  Serial.println(":");

  Serial.println(now.minute());
  Serial.println(":");
  Serial.println(now.second());
  Serial.println("Start Time:");
  Serial.println(Hourcounter);
  Serial.println(":");
  Serial.println(Minutecounter);
  Serial.println("End Time:");
  Serial.println(Hourcounter1);
  Serial.println(":");
  Serial.println(Minutecounter1);
}
