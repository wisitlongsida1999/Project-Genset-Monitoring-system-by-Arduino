int ib_sensitive = 66; // สำหรับ 30A

 
int ib_offset = 2525; // ค่าเริ่มต้น 2500 ปรับค่าตรงนี้เพื่อให้ค่ายังไม่มีโหลดเป็น 0.00
 
void setup() {
Serial.begin(9600);
}
 
void loop() {
double ib_result = cal_i_avg();
Serial.println(ib_result);
delay(1000);
}
 
// หาค่ากระแสเฉลี่ย
double cal_i_avg() {
int count = 200;
double sum = 0;
for (int i = 0; i < count; i++) {
sum += ib_input();
}
double val = sum / count;
return val;
}
// อ่านค่ากระแส
double ib_input() {
int a = analogRead(A0);
double v = (a / 1024.0) * 5000;
double ib_result = (v - ib_offset) / ib_sensitive;
return ib_result;
}
