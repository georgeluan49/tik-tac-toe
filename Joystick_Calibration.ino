int VRX = A0;
int VRY = A1;
int SW = 2;

int vrxValue = 500;
int vryValue = 500;
int swValue = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT_PULLUP); 
}

void loop() {
  vrxValue = analogRead(VRX);
  vryValue = analogRead(VRY);
  swValue = digitalRead(SW);

  if (vryValue < 50) 
        Serial.print("UP");
  if (vryValue > 1000) 
        Serial.print("Down");
  if (vrxValue < 50) 
        Serial.print("LEFT");
  if (vrxValue > 1000) 
        Serial.print("Right");
  if (swValue == 0)
      Serial.print("BUTTON PRESSED");
}
