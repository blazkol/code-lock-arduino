#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(2, 3, A3, A2, A1, A0);

const int ROW_NUM = 4;
const int COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {4, 5, 6, 7};
byte pin_column[COLUMN_NUM] = {8, 9, 10, 11};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

char password[] = {'3', '5', '9', '3'};
char input[] = {'-', '-', '-', '-'};
char key;
int pos = 0;

void setup(){
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter password:");
  lcd.setCursor(0, 1);
  lcd.print("----");
  lcd.setCursor(0, 1);
}

void loop(){
  key = keypad.getKey();

  if (key == '#') {
    if (pos != 0) {
      pos--;
      input[pos] = '-';
      lcd.moveCursorLeft();
      lcd.print('-');
      lcd.moveCursorLeft();
    }    
  }
  else if (key == '*') {
    if (pos == 4) {
      lcd.clear();
      lcd.setCursor(0, 0);

      if (password[0] == input[0] &&
          password[1] == input[1] &&
          password[2] == input[2] &&
          password[3] == input[3]) {
            digitalWrite(A5, HIGH);
            lcd.print("Correct password");
            delay(3000);
            digitalWrite(A5, LOW);
      }
      else {
        digitalWrite(A4, HIGH);
        lcd.print("Wrong password!");
        delay(3000);
        digitalWrite(A4, LOW);
      }

      for (int i = 0; i < 4; i++) {
        input[i] = '-';
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter password:");
      lcd.setCursor(0, 1);
      lcd.print("----");
      lcd.setCursor(0, 1);
      pos = 0;
    }    
  }
  else if (key) {
    if (pos < 4) {
      input[pos] = key;
      pos++;
      lcd.print(key);
    }
  }
}