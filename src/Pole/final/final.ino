#define DEBUG
#define LASER_DETECT_PIN 11
#define LASER_COMM_PIN 12
#define PR_DETECT_PIN A1
#define PR_COMM_PIN A0
#define THRESHOLD 50
#define ALARM_PIN 13 //currently choose build in
#define RESETPULSES 20 // press reset: FORCE eject D=0.8 pulse for "cancel alarm" message


#define RES 16
#define PR0MAX 0
#define D1 3
#define PR1MAX 5
#define D2 7
#define PR2MAX 9
#define D3 11
#define PR3MAX 12
#define DRESET 14

#define Tpulse 30


int buff=0;
int val_comm_0=0,val_comm_1=0,val_detect_0=0,val_detect_1=0;
unsigned long Dout = 0;
unsigned long D[5]={D1,D2,D3,RES,DRESET};
unsigned long T = Tpulse;
unsigned long t,t0;
unsigned long readcount = 0;
int pulses_detect = 0;
int pulses_comm = 0;
bool laserstate = 0;
bool PRstate_comm = 0;
bool PRstate_detect = 0;
bool alarmstate = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LASER_DETECT_PIN, OUTPUT);
  pinMode(LASER_COMM_PIN, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(PR_DETECT_PIN,INPUT);
  pinMode(PR_COMM_PIN,INPUT);
#ifdef DEBUG
  Serial.begin(500000);
  Serial.setTimeout(1);
  Serial.println("Set D & f(T) of light pulse, PR sample rate is 10%(by default).");
  Serial.println("EX: D(0,10) T(10up ms).");
#endif
  unsigned long t0 = millis();
  Dout=D[4];     //initially eject reset signal
  readcount=0;

  t = millis();
  for(int ireset=0;ireset<RESETPULSES;++ireset){
    t0=millis();
    if((t-t0)*RES >= Dout*T) {if(laserstate==HIGH){digitalWrite(LASER_DETECT_PIN,LOW) ;digitalWrite(LASER_COMM_PIN,LOW) ;laserstate=LOW;}}
    else                     {if(laserstate==LOW) {digitalWrite(LASER_DETECT_PIN,HIGH);digitalWrite(LASER_COMM_PIN,HIGH);laserstate=HIGH;}}
  }
}



void loop() {
 /*                           // serial input for debug con
 if(Serial.available()){
  if(Serial.peek()!='\n'){
  //buff = Serial.parseInt(); //Serial.print(F("BUFF"));Serial.println(buff);
  //D = (buff>RES?RES:buff);
  buff = Serial.parseInt();
  T = buff;
  }
  else
  Serial.read();
 }*/
 t = millis();
 digitalWrite(ALARM_PIN,alarmstate);

     // LASER PULSE
 if((t-t0)*RES >= Dout*T) {if(laserstate==HIGH){digitalWrite(LASER_DETECT_PIN,LOW);digitalWrite(LASER_COMM_PIN,LOW);laserstate=LOW;}}//Serial.print(F("D"));Serial.println(D);}}
 else                {if(laserstate==LOW){digitalWrite(LASER_DETECT_PIN,HIGH);digitalWrite(LASER_COMM_PIN,HIGH);laserstate=HIGH;}}
 
     // READ 10 times in T
 if((t-t0)*RES > readcount*T){
  readcount = readcount+1;
  if(readcount==RES) {
#ifdef DEBUG
    Serial.print("\n");
    Serial.print("D1=");
    Serial.print(pulses_detect);
    Serial.print(" D2=");
    Serial.println(pulses_comm);
    Serial.print("Set level to:");
#endif
    if(pulses_detect == PR0MAX){                                // index 0
      Dout=D[0]; alarmstate=true;
#ifdef DEBUG
      Serial.print(D[0]);
#endif
      }
    else if(pulses_detect <= PR1MAX || pulses_comm <= PR1MAX){   // index 1
      Dout=D[1]; alarmstate=true;
#ifdef DEBUG
      Serial.print(D[1]);
#endif
      }
    else if(pulses_detect <= PR2MAX || pulses_comm <= PR2MAX){   // index 2
      Dout=D[2]; alarmstate=true;
#ifdef DEBUG
      Serial.print(D[2]);
#endif
      }
    else if(pulses_detect <= PR3MAX || pulses_comm <= PR3MAX){   // index 2
      Dout=D[3]; alarmstate=true;
#ifdef DEBUG
      Serial.print(D[3]);
#endif
      }
    else if(pulses_detect == RES && pulses_comm == RES){         // normal
      Dout = D[3];
#ifdef DEBUG
      Serial.print(D[3]);
#endif
      }
    else if(alarmstate == true){                          // RESET ALARM(alarmed device): pass the reset signal
      Dout = D[4]; alarmstate = false;
#ifdef DEBUG
      Serial.print(D[4]);
#endif
      }
    else{                                                 // RESET ALARM(normal device): do nothing
      Dout = D[3];
#ifdef DEBUG
      Serial.print(D[3]);
#endif
      }
    /*Serial.print(" D");
    Serial.print(D);
    Serial.print(" T");
    Serial.println(T);*/
    readcount=0;
    pulses_detect=0;
    pulses_comm=0;
    t0=millis();
    }
  /*Serial.print("n");
  Serial.print(readcount);
  Serial.print(" PR");
  Serial.print(digitalRead(PRPIN));
  Serial.print(" d");
  Serial.println(detected);*/
  val_detect_1 = analogRead(PR_DETECT_PIN);
  if(val_detect_1 - val_detect_0 > THRESHOLD) PRstate_detect = true;
  else if(val_detect_0 - val_detect_1 > THRESHOLD) PRstate_detect = false;
  val_detect_0 = val_detect_1;

  val_comm_1 = analogRead(PR_COMM_PIN);
  if(val_comm_1 - val_comm_0 > THRESHOLD) PRstate_comm = true;
  else if(val_comm_0 - val_comm_1 > THRESHOLD) PRstate_comm = false;
  val_comm_0 = val_comm_1;
  
  pulses_detect = pulses_detect + PRstate_detect;
  pulses_comm = pulses_comm+ PRstate_comm;
 }
}
