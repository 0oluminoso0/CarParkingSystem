#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

//Don't use pin 18,19 it for lcd

#define IRslot1 1
#define IRslot2 2
#define IRslot3 3
#define IRslot4 4
#define IRslot5 5
#define Floor2slot 14

int slot1 = 0;
int slot2 = 0;
int slot3 = 0;
int slot4 = 0;
int slot5 = 0;
int total = 0;

void setup() {
  serial.begin(115200);
  pinMode(IRslot1,INPUT);
  pinMode(IRslot2,INPUT);
  pinMode(IRslot3,INPUT);
  pinMode(IRslot4,INPUT);
  pinMode(IRslot5,INPUT);
  pinMode(Floor2slot,OUTPUT);
  lcd.begin(20, 4);
  IR_Read();
  total = slot1 + slot2 + slot3 + slot4 + slot5; 
}

void IR_Read()  {
  slot1 = 0, slot2 = 0, slot3 = 0, slot4 = 0, slot5 = 0;
  if (digitalRead(IRslot1) == 0)
  {
    slot1 = 1;
  }
  if (digitalRead(IRslot2) == 0)
  {
    slot2 = 1;
  }
  if (digitalRead(IRslot3) == 0)
  {
    slot3 = 1;
  }
  if (digitalRead(IRslot4) == 0)
  {
    slot4 = 1;
  }
  if (digitalRead(IRslot5) == 0)
  {
    slot5 = 1;
  }
}

void loop() {
  IR_Read();
  lcd.setCursor(0, 0);
  lcd.print(" 2st Floor slot : ");
  lcd.print(total);
  lcd.print("    ");
  analogWrite(Floor2slot,total);
  delay(1);
}