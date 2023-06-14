#define R 10
#define G 12
#define B 11
#define PHOTO A0

int lighting;
int autoL;
long nowTime = 0;
int delayTime = 1000;
long previousTime = 0;
int x;
int data;
bool autoMode = 0;
byte userBrightness;
byte minBrightness;
byte maxBrightness;
byte brightness;

void lightOn(byte brightness) {
  analogWrite(R, brightness);
  analogWrite(G, brightness);
  analogWrite(B, brightness);
}

void autoLighting(byte minL, byte maxL, byte currentLighting) {
  if ((currentLighting < minL) && (autoL < 255)) {
    autoL++;
    lightOn(autoL);
  }
  if ((currentLighting > maxL) && (autoL > 0)) {
    autoL--;
    lightOn(autoL);
  }
}

int photoReader() {
  nowTime = millis();
  if (nowTime - previousTime > delayTime) {
    previousTime = millis();
    x = analogRead(PHOTO);
    lighting = map(x, 1020, 100, 0, 100);
  }
  return lighting;
}
void setup() {
  // put your setup code here, to run once:
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
  Serial3.begin(9600);
}

void loop() {
  if (Serial3.available()) {
    data = Serial3.parseInt();
  }

if (data == 505) {
      autoMode = 0;
    } else if (data == 404) {
      autoMode = 1;
    } else if (data == 303) {
      Serial3.print(photoReader());
    } else if (data < 101 && autoMode == 1) {
      userBrightness = data;
      minBrightness = userBrightness - 5;
      maxBrightness = userBrightness + 5;
      autoLighting(minBrightness, maxBrightness, photoReader());
    } else if (data < 101 && autoMode == 0) {
      brightness = map(data, 0, 100, 0, 255);
      lightOn(brightness);
    }
  // put your main code here, to run repeatedly:
  Serial.print("Auto flag: ");
  Serial.print(autoMode);
  Serial.print("\t");

  Serial.print("Fhotoresistor value: ");
  Serial.print(photoReader());
  Serial.print("\t");

Serial.print("Bluetooth value: ");
  Serial.println(data);
   Serial.print("\t");

   Serial.print("User`s brightness of LED: ");
  Serial.print(userBrightness);
  Serial.print("\t");

  Serial.print("Current auto brightness of LED: ");
  Serial.print(autoL);
  Serial.print("\t");

Serial.print("Current brightness of LED: ");
  Serial.print(brightness);
  Serial.print("\t");
  delay(100);
  // autoLighting(50, 60, photoReader());
}
