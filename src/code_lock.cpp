#include <Arduino.h>
#include <Keypad.h>

char cipher[] = {'3', '5', '9', '3'}; //predefined cipher
char input_num[] = {'-', '-', '-', '-'};  //entered cipher
int i = 0;

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  Serial.begin(9600);
}

void turnOnLEDs() {
  if(i == 1){
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
  }
  else if (i == 2){
    digitalWrite(A3, HIGH);
  }
  else if (i == 3){
    digitalWrite(A4, HIGH);
  }
  else if (i == 4){
    digitalWrite(A5, HIGH);
    if(cipher[0] == input_num[0] &&
       cipher[1] == input_num[1] &&
       cipher[2] == input_num[2] &&
       cipher[3] == input_num[3]){
         digitalWrite(A0, HIGH);
       }
    else{
      digitalWrite(A1, HIGH);
    }
    i = 0;
  }
}

void loop(){
  input_num[i] = keypad.getKey();
  if (input_num[i]){
    Serial.println(input_num[i]);
    i++;
  }
  turnOnLEDs();
}