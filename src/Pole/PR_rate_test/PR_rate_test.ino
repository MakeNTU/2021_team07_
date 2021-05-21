#define LASERPIN 6
#define LASERPIN2 5
#define PRPIN 10
#define PRPIN2 31

int buff=0;
unsigned long D=0;
unsigned long T=30;
unsigned long t,t0;
unsigned long readcount = 0;
int detected = 0;
bool state = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LASERPIN, OUTPUT);
  pinMode(PRPIN,INPUT);
  Serial.begin(500000);
  Serial.setTimeout(1);
  Serial.println("Set D & f(T) of light pulse, PR sample rate is 10%(by default).");
  Serial.println("EX: D(0,10) T(10up ms).");
  unsigned long t0 = millis();
  D=0;
}



void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available()){
  if(Serial.peek()!='\n'){
  buff = Serial.parseInt(); //Serial.print(F("BUFF"));Serial.println(buff);
  D = (buff>10?10:buff);
  buff = Serial.parseInt();
  T = buff;
  }
  else
  Serial.read();
 }
 t=millis();

     // LASER PULSE
 if((t-t0)*10 >= D*T) {if(state==HIGH){digitalWrite(LASERPIN,LOW);state=LOW;}}//Serial.print(F("D"));Serial.println(D);}}
 else                {if(state==LOW){digitalWrite(LASERPIN,HIGH);state=HIGH;}}
 
     // READ 10 times in T
 if((t-t0)*10 > readcount*T){
  readcount = readcount+1;
  if(readcount==10) {
    Serial.print("\n");
    Serial.print("N");
    Serial.print(detected);
    Serial.print(" D");
    Serial.print(D);
    Serial.print(" T");
    Serial.println(T);
    readcount=0;
    detected=0;
    t0=millis();
    }
  /*Serial.print("n");
  Serial.print(readcount);
  Serial.print(" PR");*/
  Serial.print(digitalRead(PRPIN));
  /*Serial.print(" d");
  Serial.println(detected);*/
  detected = detected+ !digitalRead(PRPIN);
  Serial.flush();
 }
}
