#define LASERPIN 11

void setup() {
  // put your setup code here, to run once:
  pinMode(LASERPIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("PWM test.Enter Duty 0~100.");
}
int buff=0;
int D=0;

void loop() {
  // put your main code here, to run repeatedly:
 buff = Serial.parseInt();
 if(buff>0){
  D=buff;
  Serial.println("PWM test.Enter Duty 0~255.");
  Serial.println(D);
  analogWrite(LASERPIN,D);
  }
}
