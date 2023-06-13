#define R 10
#define G 12
#define B 11
#define PHOTO A0

int lighting;
int autoR;
int autoG;
int autoB;
long nowTime = 0;
int delayTime = 1000;
long previousTime = 0;
int x;

void lightOn (byte r, byte g, byte b){
  analogWrite(R,r);
  analogWrite(G,g);
  analogWrite(B,b);

}
void lightOff (){
  analogWrite(R,0);
  analogWrite(G,0);
  analogWrite(B,0);
}

void autoLighting (byte minL,byte maxL, byte currentLighting){
  if ( (currentLighting< minL)&&(autoR<255)&&(autoG<255)&&(autoB<255)){
    autoR++;
    autoG++;
    autoB++;
    lightOn(autoR,autoG,autoB);
  }
    if ( (currentLighting> maxL)&&(autoR>0)&&(autoG>0)&&(autoB>0)){
    autoR--;
    autoG--;
    autoB--;
    lightOn(autoR,autoG,autoB);
  }
  
}

int photoReader(){
   nowTime = millis();
  if (nowTime - previousTime > delayTime) {
    previousTime = millis();
    x = analogRead(PHOTO);
    lighting = map(x,1020,100, 0, 100);
  }
  return lighting;  
}
void setup() {
  // put your setup code here, to run once:
pinMode(R,OUTPUT);
pinMode(G,OUTPUT);
pinMode(B,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(lighting);
Serial.print("\t");
Serial.print(autoR);
Serial.print("\t");
Serial.print(autoG);
Serial.print("\t");
Serial.println(autoB);
autoLighting(50,60,lighting);

delay(100);
}
