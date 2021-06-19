# Project-Genset-Monitoring-system-by-Arduino

My final year project as A monitoring system for generator set.

Designing, I divided this system into 3 part including 1.Master as ESP32 2.Slave 1 as arduino nano 3.Slave 2 as auduino nano same as slave 1.

Workflow of this system, both slave as arduino nano received all paremeter from others sensors that installed at anypoint of genset >> arduino sended data to Mastaer as ESP32
after that master will backup data in SD card for internet connection lost case , Notify to Line app. throught line api in chat, and master send data for stored in cloud database 
in this project we used real-time database platform of google company also known as FIREBASE for stored data to display in our website that we generated.

This is source code that complied to Arduino(Slave) and ESP32(Master) in our system for measuring , analysing , notify and data storing.

ESP32_WIFI >> ESP32 as Master

Slave 1 Engin >> Arduino as slave 1

Slave 2 gen >> Arduino as slave 2

