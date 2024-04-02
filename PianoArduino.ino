#include <Wire.h>
#include <VL53L0X.h>
#include <LiquidCrystal.h>

VL53L0X sensor;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Define os pinos do LCD

#define buzzerPin 13 // Definir o pino do buzzer

// Notas musicais (frequências em Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  pinMode(buzzerPin, OUTPUT);

  sensor.startContinuous();

  // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);
}

void loop()
{
  // Limpa o conteúdo do LCD
  lcd.clear();

  int distance = sensor.readRangeContinuousMillimeters();

  Serial.print(distance);

  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  if(distance > 45 && distance < 70)
  {
    lcd.setCursor(0, 0);
    lcd.print("DO");
    tone(buzzerPin, NOTE_C4, 200);
  }
  else if (distance > 72 && distance < 86)
  {
    lcd.setCursor(0, 0);
    lcd.print("SOL");
    tone(buzzerPin, NOTE_G4, 200);
  }
  else if (distance > 88 && distance < 100)
  {
    lcd.setCursor(0, 0);
    lcd.print("LA");
    tone(buzzerPin, NOTE_A4, 200);
  }
  else
  {
    Serial.print("\n");
  }

  delay(500);
}


