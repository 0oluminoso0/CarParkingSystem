//Lib pull
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo myservo;

//Don't use pin3,4 it for lcd

#define IR_Enter  1
#define IR_Out  2
#define IRslot1 5
#define IRslot2 6
#define IRslot3 7
#define IRslot4 8
#define IRslot5 9
#define Floor2slot 10


int slot = 10;
int slot1 = 0;
int slot2 = 0;
int slot3 = 0;
int slot4 = 0;
int slot5 = 0;
int floor1 = 0;
int floor2 = 0;
int servo1 = 0;
int servo2 = 0;



void setup() {
  serial.begin(115200);
  pinMode(IR_Enter,INPUT);
  pinMode(IR_Out,INPUT);
  pinMode(IRslot1,INPUT);
  pinMode(IRslot2,INPUT);
  pinMode(IRslot3,INPUT);
  pinMode(IRslot4,INPUT);
  pinMode(IRslot5,INPUT);
  pinMode(Floor2slot,INPUT);
  myservo.attach(11);
  myservo.write(90);
  lcd.begin(20, 4);
  IR_Read();
  floor1 = slot1 + slot2 + slot3 + slot4 + slot5;
  slot = slot - (floor1+floor2);
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
  floor2 = analogRead(Floor2slot);
  lcd.setCursor(0, 0);
  lcd.print(" 1st Floor slot : ");
  lcd.print(floor1);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print(" 2ns Floor slot : ");
  lcd.print(floor2);
  lcd.print("    ");
  //Servocontrol
  if (digitalRead (IR_Enter) == 0 && servo1 == 0)
  {
    if (slot > 0)
    {
      servo1 = 1;
      if (servo2 == 0)
      {
        myservo.write(180);
        slot = slot - 1;
      }
    }else{
      lcd.setCursor(0, 0);
      lcd.print(" Parking Slot Full ");
      delay(1500);
    }
  }if (servo1 == 1 && servo2 == 1)
  {
    delay(1000);
    myservo.write(90);
    servo1 = 0;
    servo2 = 0;
  }
  delay(1);
}
