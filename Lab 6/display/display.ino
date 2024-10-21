#include <LiquidCrystal.h>
#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {48, 46, 44, 42}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {40, 38, 36, 34}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

// LCD pins <--> Arduino pins
// LCD pins <--> Arduino pins
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
int x=0, y=0;
byte customChar[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

byte customChar2[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b01110,
  0b01110,
  0b00000,
  0b00000,
  0b00000
};
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2); // set up number of columns and rows
  lcd.createChar(1, customChar); // create a new custom character, first
  //parameter can be from 0 to 7. Later the same number needs to be used to write
  //on LCD
  lcd.setCursor(0, 0); // move cursor to (0, 0)
  lcd.write((byte)1); // print the custom char at (0, 0)
  lcd.createChar(2, customChar2); // create a new custom character
  lcd.setCursor(5, 1); // move cursor to (5, 1)
  lcd.write((byte)2); // print the custom char at (5, 1)
  lcd.setCursor(9, 1); // move cursor to (9, 1)
  lcd.write((byte)2); // print the custom char at (9, 1)
  lcd.setCursor(6, 0); // move cursor to (6, 0)
  lcd.write((byte)2); // print the custom char at (6, 0)
  lcd.setCursor(15, 1); // move cursor to (15, 1)
  lcd.write((byte)2); // print the custom char at (15, 1)
  lcd.setCursor(0,0); //bring the cursor back to the start
  
}

void loop()
{
  
  char key = keypad.getKey();

  if(key){
    Serial.println(key);
    switch(key){
      case('2'):
        y--;
        break;
      case('4'):
        x--;
        break;
      case('6'):
        x++;
        break;
      case('8'):
        y++;
        break;
    }
    if(x >= 16){
      x = 0;
    }
    if(x < 0){
      x = 15;
    }
    if(y >= 2){
      y = 0;
    }
    if(y < 0){
      y = 1;
    }
    move(x,y);
    }

    if((x == 5 && y == 1) || (x==9 && y == 1) || (x == 6 && y == 0) || (x == 15 && y == 1)){
      Serial.println("You scored!");
    }
}

void move(int x, int y){
  lcd.clear();
  lcd.setCursor(x, y); // move cursor to (0, 0)
  lcd.write((byte)1); // print the custom char at (0, 0)
  lcd.setCursor(5, 1); // move cursor to (5, 1)
  lcd.write((byte)2); // print the custom char at (5, 1)
  lcd.setCursor(9, 1); // move cursor to (9, 1)
  lcd.write((byte)2); // print the custom char at (9, 1)
  lcd.setCursor(6, 0); // move cursor to (6, 0)
  lcd.write((byte)2); // print the custom char at (6, 0)
  lcd.setCursor(15, 1); // move cursor to (15, 1)
  lcd.write((byte)2); // print the custom char at (15, 1)
}



