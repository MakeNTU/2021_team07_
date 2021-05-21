#define LASER_DETECT_PIN 11
#define LASER_COMM_PIN 12
void setup() {
  // put your setup code here, to run once:
pinMode(LASER_DETECT_PIN,OUTPUT);
pinMode(LASER_COMM_PIN,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(LASER_DETECT_PIN,HIGH);
digitalWrite(LASER_COMM_PIN,HIGH);
}
