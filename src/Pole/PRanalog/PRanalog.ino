#define pr_comm A0
#define pr_detect A1

void setup() {
  // put your setup code here, to run once:
Serial.begin(500000);
pinMode(pr_comm, INPUT);
pinMode(pr_detect,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(F("COMM "));
  Serial.print(analogRead(pr_comm));
  Serial.print(F(" DETECT "));
  Serial.println(analogRead(pr_detect));
}
