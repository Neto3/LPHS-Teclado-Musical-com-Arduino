int PN1 = 1;
int PN2 = 2;
int PN3 = 3;
int PN4 = 4;
int PN5 = 5;
int PN6 = 6;
int PN7 = 7;
int PN8 = 8;
int PN9 = 9;
int PN10 = 10;
int PN11 = 11;
int PN12 = 12;
int PN13 = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(PN7, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (digitalRead(PN7) == HIGH)
      Serial.write("HIGH");
  

  delay(100);

}
