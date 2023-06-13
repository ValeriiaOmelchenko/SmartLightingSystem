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
char data;

void lightOn (byte brightness){
  analogWrite(R,brightness);
  analogWrite(G,brightness);
  analogWrite(B,brightness);

}
void lightOff (){
  analogWrite(R,0);
  analogWrite(G,0);
  analogWrite(B,0);
}

void autoLighting (byte minL,byte maxL, byte currentLighting){
  if ( (currentLighting< minL)&&(autoL<255)){
    autoL++;
    lightOn(autoL);
  }
    if ( (currentLighting> maxL)&&(autoL>0)){
    autoL--;
    lightOn(autoL);
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
Serial3.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
/*Serial.print(photoReader());
Serial.print("\t");
Serial.println(autoL);*/

autoLighting(50,60,photoReader());

delay(100);
}
