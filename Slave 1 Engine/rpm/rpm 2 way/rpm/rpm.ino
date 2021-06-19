int chk11;
int chk12;
int sp1_PIN = 9;
int sp2_PIN = 10;
int count_sp1 = 0;
int count_sp2 = 0;
unsigned long lastmillis = 0;
void setup() {
pinMode(sp1_PIN, INPUT);
pinMode(sp2_PIN, INPUT);
Serial.begin(9600);
}
void loop() {

while(millis() - lastmillis <= 1000){     // Limit at 1 sec

while(digitalRead(sp1_PIN) == 1) {        // Check sensor 1
chk11++;
// Serial.println(chk11);
  }

while(chk11 > 0) {                        // Count
count_sp1++;
Serial.print("Round1 = "); Serial.println(count_sp1);
chk11 = 0;
}

while(digitalRead(sp2_PIN) == 1) {        // Check sensor 2
chk12++;
// Serial.println(chk12);
  }

while(chk12 > 0) {                       // Count
count_sp2++;
Serial.print("Round2 = "); Serial.println(count_sp2);
chk12 = 0;
}
}

Serial.print("rpm1 = "); Serial.println(count_sp1*60);
count_sp1=0;

Serial.print("rpm2 = "); Serial.println(count_sp2*60);
count_sp2=0;

lastmillis = millis();                      // Set every 1 sec
}
