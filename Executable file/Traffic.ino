#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#define splash splash1

int g[2] = {49, 43 };   
int y[2] = {51, 45 };
int r[2] = {53, 47 };

#define s1ir1 A0
#define s1ir2 A1
#define s2ir1 A2
#define s2ir2 A3

int states[2] = { HIGH, HIGH};
int totalDevices = 2;
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
long t = 20, prevt;
long tt1 = 1000;
int tset, a;
int red1Status, yellow1Status, yellow2Status, red2Status, aStat ;

int s1ir1_r, s1ir2_r, s2ir1_r, s2ir2_r;

int dens1, dens2;

void setup() {

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);


  Serial.begin(9600);
  LcDSet();
  splash(0, "Signal");
  splash(1, "Initializing");

  setupPinsMode();
  delay(2000);
  lcd.clear();
}


void LcDSet()
{
  lcd.begin(16, 2);
  splash(0, "Smart Traffic");
  splash(1, "Control");
  delay(2000);
  lcd.clear();

}
void setupPinsMode() {

  pinMode(s1ir1, INPUT);
  pinMode(s1ir2, INPUT);

  pinMode(s2ir1, INPUT);
  pinMode(s2ir2, INPUT);

  // setup Pin mode as output.
  for (int i; i < totalDevices; i++) {

    Serial.println();
    pinMode(g[i], OUTPUT);
    digitalWrite(g[i], HIGH);

    delay(100);

    Serial.println();
    pinMode(y[i], OUTPUT);
    digitalWrite(y[i], HIGH);

    delay(100);
    Serial.println();
    pinMode(r[i], OUTPUT);
    digitalWrite(r[i], HIGH);

    delay(100);
  }
  delay(1000);
  for (int i; i < totalDevices; i++) {

    Serial.println();
    pinMode(g[i], OUTPUT);
    digitalWrite(g[i], LOW);

    delay(100);

    Serial.println();
    pinMode(y[i], OUTPUT);
    digitalWrite(y[i], LOW);

    delay(100);
    Serial.println();
    pinMode(r[i], OUTPUT);
    digitalWrite(r[i], LOW);

    delay(100);
  }
}



void loop()
{
  timer();

  s1ir1_r = digitalRead(s1ir1);
  s1ir2_r = digitalRead(s1ir2);
  s2ir1_r = digitalRead(s2ir1);
  s2ir2_r = digitalRead(s2ir2);

  if (s1ir1_r ) {
    dens1 = 1;
    if (s1ir2_r ) {
      dens1 = 2;
    }
  }
  else {
    dens1 = 0;
  }


  if (!s2ir1_r ) {
    dens2 = 1;
    if (!s2ir2_r ) {
      dens2 = 2;
    }
  }
  else {
    dens2 = 0;
  }




  lcd.setCursor(0, 0);
  lcd.print("Traffic Density");
  lcd.setCursor(0, 1);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print(dens1);
  lcd.setCursor(5, 1);
  lcd.print("    ");
  lcd.setCursor(5, 1);
  lcd.print(dens2);
  lcd.setCursor(14, 1);
  lcd.print("  ");
  lcd.setCursor(14, 1);
  lcd.print(a);
  delay(300);

}


void red1()
{
  digitalWrite(r[0], HIGH);
  digitalWrite(r[1], LOW);
  digitalWrite(y[0], LOW);
  digitalWrite(y[1], LOW);
  digitalWrite(g[0], LOW);
  digitalWrite(g[1], HIGH);

}
void red2()
{

  digitalWrite(r[0], LOW);
  digitalWrite(r[1], HIGH);
  digitalWrite(y[0], LOW);
  digitalWrite(y[1], LOW);
  digitalWrite(g[0], HIGH);
  digitalWrite(g[1], LOW);
}
void yellow()
{
  digitalWrite(r[0], LOW);
  digitalWrite(r[1], LOW);
  digitalWrite(y[0], HIGH);
  digitalWrite(y[1], HIGH);
  digitalWrite(g[0], LOW);
  digitalWrite(g[1], LOW);

}
void green1()
{

}
void green2()
{

}

void timer()
{
  unsigned long currentMillis = millis();
  unsigned long currentMillis1 = millis();
  if (tset == 0)
  {
    tset = 1;
    a = t;
    prevt = t;


  }
  if (currentMillis - previousMillis >= t) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

  }
  if (currentMillis1 - previousMillis1 >= tt1) {
    // save the last time you blinked the LED
    previousMillis1 = currentMillis1;
    if (aStat == 0)
    { aStat = 1;
      red1();
      red1Status = 1;
      t = 5;

    }
    if (a <=  0)
    {

      a = t;

      if (a >= (t - 2) && red1Status == 0)
      {
        red1();
        red1Status = 1;
        red2Status = 0;
        yellow1Status = 0;
        t = 5;
      }
      else if (a >= (t - 2) && yellow1Status == 0)
      {
        yellow();
        yellow1Status = 1;
        red2Status = 0;
        t = prevt;
        if (dens2 == 2  ) {
          t = 60;
        }
        else   if (dens2 == 1 ) {
          t = 40;
        }
        else {
          t = 20;
        }

      }
      else if (a >= (t - 2) && red2Status == 0)
      {
        red2();
        yellow2Status = 0;
        red2Status = 1;
        red1Status = 1;
        t = 5;
      }
      else if (a >= (t - 2) && yellow2Status == 0)
      {
        yellow();
        yellow2Status = 1;
        red1Status = 0;
        t = prevt;
        if (dens1 == 2) {
          t = 60;
        }
        else   if (dens1 == 1 ) {
          t = 40;
        }
        else {
          t = 20;
        }
      }
    }
    else
    {
      a--;
    }

  }
}
