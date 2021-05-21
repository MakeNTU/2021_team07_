#define LASERPIN 11
#define PRPIN 6

void setup() {
  // put your setup code here, to run once:
  pinMode(LASERPIN, OUTPUT);
  pinMode(PRPIN,INPUT);
  Serial.begin(115200);
  Serial.println("PWM test.Enter Duty 0~10.");
  Serial.setTimeout(50);
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
  Serial.print("Photoresister = ");
  Serial.println(digitalRead(PRPIN));
}
