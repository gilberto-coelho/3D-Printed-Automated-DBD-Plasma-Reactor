#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t degree[8]  = {140, 146, 146, 140, 128, 128, 128, 128};

byte arrowDown[8] = {
  B00000,
  B00100,
  B00100,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte arrowUp[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B00100,
  B00100,
  B00000
};

bool ajuste1 = 0;
bool ajuste2 = 0;
bool ajuste3 = 0;
bool ajuste4 = 0;
bool ajuste5 = 0;
bool ajuste6 = 0;

byte valorServo = 50;
byte memoriavalorServo = 1;

unsigned long tempo1 = 0;
unsigned long tempo2 = 0;

unsigned long tempo3 = 0;
unsigned long tempo4 = 0;

void aumenta();
void diminui();

int temperatura = 50;


void setup() {

  Serial.begin(9600);

  pinMode(7, INPUT_PULLUP); //Button
  pinMode(5, OUTPUT); // Buzzer
  pinMode(4, OUTPUT); // LED DBD

  digitalWrite(5, HIGH);
  delay(100);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);

  valorServo = EEPROM.read(memoriavalorServo);

  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, degree);
  lcd.createChar(1, arrowDown);
  lcd.createChar(2, arrowUp);

  mlx.begin();

  lcd.setCursor(0, 0); lcd.print("Waiting..        ");
  lcd.setCursor(0, 1); lcd.print("Reactor:  "); lcd.print(mlx.readObjectTempC(), 0); lcd.print(" "); lcd.write((byte)0); lcd.print("C   ");

  myservo.attach(9);
  myservo.write(105); delay(500);
  myservo.detach();

}

void loop() {

  //Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  //Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  //Serial.println();

  lcd.setCursor(0, 1); lcd.print("Reactor:  "); lcd.print(mlx.readObjectTempC(), 0); lcd.print(" "); lcd.write((byte)0); lcd.print("C   ");

  //delay(100);

  temperatura = mlx.readObjectTempC();
  if (temperatura >= 100) {
    ajuste4 = 1;
  }
  if (temperatura <= 40 && ajuste4 == 1) {
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    myservo.write(105); delay(500);
    myservo.detach();
    ajuste4 = 0;
  }


  if (digitalRead(7) == HIGH && ajuste1 == 0 && ajuste2 == 1) {
    myservo.attach(9);
    myservo.write(valorServo);
    ajuste1 = 1;
    ajuste2 = 0;
    ajuste5 = 1;
    ajuste6 = 0;
    tempo3 = millis();
  }



  if (ajuste5 == 1) {
    tempo4 = millis() - tempo3;
    Serial.print(tempo4); Serial.print(","); Serial.println(temperatura);
    tempo4 = tempo4 / 1000;
    lcd.setCursor(0, 0); lcd.print("Time: "); lcd.print(tempo4); lcd.print(" s  ");
    if (ajuste6 == 0) {
      delay(500);
    }
    ajuste6 = 1;
    digitalWrite(4, HIGH);
    if (digitalRead(7) == LOW) {
      while (digitalRead(7) == LOW) {;}
      myservo.write(105); 
      digitalWrite(4, LOW);
      delay(500);
      myservo.detach();
      tempo4 = 140;
    }
  }

  if (tempo4 >= 140) {
    digitalWrite(4, LOW);
    lcd.setCursor(0, 0); lcd.print("Waiting..        ");
    ajuste5 = 0;
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    tempo4 = 0;
  }

  if (digitalRead(7) == HIGH && ajuste1 == 1 && ajuste2 == 1) {
    digitalWrite(4, LOW);
    myservo.write(105); delay(500);
    myservo.detach();
    ajuste1 = 0;
    ajuste2 = 0;
    ajuste5 = 0;
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("Waiting..        ");

  }



  if (Serial.available() > 0) {
    valorServo = Serial.parseInt();
    valorServo = constrain(valorServo, 0, 180);
    myservo.attach(9);
    myservo.write(valorServo);
    Serial.print("Posição do Servo: ");
    Serial.println(valorServo);
  }




  if (digitalRead(7) == LOW) {
    if (ajuste2 == 0) {
      tempo1 = millis();
      ajuste2 = 1;
      ajuste1 = 0;
    }
    tempo2 = millis();
    if ((tempo2 - tempo1) > 1000) {
      ajuste2 = 0;
      while (digitalRead(7) == LOW) {
        lcd.clear();
      }
      while (digitalRead(7) == HIGH) {
        lcd.setCursor(0, 0); lcd.print("MENU      "); lcd.print(mlx.readObjectTempC(), 0); lcd.print(" "); lcd.write((byte)0); lcd.print("C   ");
        lcd.setCursor(0, 1); lcd.print("POSITION: "); lcd.print(valorServo); lcd.write((byte)0); lcd.print("  "); lcd.setCursor(15, 1); lcd.write((byte)1);
        myservo.attach(9);
        myservo.write(valorServo);
      }
      if (digitalRead(7) == LOW) {
        delay(1000);
        while (digitalRead(7) == LOW) {
          diminui();
        }
      }

      lcd.setCursor(0, 1); lcd.print("POSITION: "); lcd.print(valorServo); lcd.write((byte)0); lcd.print("  "); lcd.setCursor(15, 1); lcd.write((byte)2);
      while (digitalRead(7) == HIGH) {lcd.setCursor(0, 0); lcd.print("MENU      "); lcd.print(mlx.readObjectTempC(), 0); lcd.print(" "); lcd.write((byte)0); lcd.print("C   ");}

      if (digitalRead(7) == LOW) {
        delay(1000);
        while (digitalRead(7) == LOW) {
          aumenta();
        }
        EEPROM.put(memoriavalorServo, valorServo);
        lcd.clear();
        lcd.setCursor(0, 0); lcd.print("Wainting..    ");
        myservo.write(105); delay(500);
        myservo.detach();
        
      }
    }
  }
}

void diminui() {
  valorServo -= 1;
  lcd.setCursor(0, 1); lcd.print("POSITION: "); lcd.print(valorServo); lcd.write((byte)0); lcd.print("  "); lcd.setCursor(15, 1); lcd.write((byte)1);
  myservo.attach(9);
  myservo.write(valorServo);
  delay(1000);
}

void aumenta() {
  valorServo += 1;
  lcd.setCursor(0, 0); lcd.print("MENU      "); lcd.print(mlx.readObjectTempC(), 0); lcd.print(" "); lcd.write((byte)0); lcd.print("C   ");
  lcd.setCursor(0, 1); lcd.print("POSITION: "); lcd.print(valorServo); lcd.write((byte)0); lcd.print("  "); lcd.setCursor(15, 1); lcd.write((byte)2);
  myservo.attach(9);
  myservo.write(valorServo);
  delay(1000);
}
