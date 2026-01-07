/*
ESP8266 WebServer using HTML CSS & JS
NodeMCU 1.0 ESP 12E COM3
*/
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "webpageCode.h";

Servo myservo,myservo2;
ESP8266WebServer server(80);
const char* ssid = "Electronics";
const char* password = "dynamess";
int t1,t2;
int pos = 0;
int pos2 = 0;
//=================================================================================
void setup() {
   myservo.attach(15);
   myservo2.attach(13);
   Serial.begin(115200);
   WiFi.begin(ssid,password);
   while(WiFi.status()!= WL_CONNECTED)
   {
     delay(500);
     Serial.print(".");
   }
   Serial.println();
   Serial.print("IP Address: ");
   Serial.println(WiFi.localIP());
   
   server.on("/",webpage);
   server.begin();
  myservo.write(90);
  myservo2.write(0);
}
//=================================================================================
void loop() {

  server.handleClient();
  
  // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15); // delay to allow the servo to reach the desired position
  //   if (pos==90){
  //     delay(1000); //wait 5 seconds once positioned at 90 degrees
  //   }
  // }
  // delay(1000); // wait 5 seconds after reaching 180 degrees
 
  // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);
  //   if (pos==90){
  //     delay(1000); // wait 5 seconds once positioned at 90 degrees
  //   }
  // }
  // delay(1000); // wait 5 seconds after arriving back at 0 degrees
  // Serial.print("End of loop");
  
}

void webpage(){
   server.send(200,"text/html", webpageCode);
   if(server.arg("theta1") == NULL){
     Serial.print("No Theta");
   }else{
     Serial.print("Theta 1 & 2");
    
     
     t1 = server.arg("theta1").toInt();
     t2 = server.arg("thetha2").toInt();
     
      Serial.println(t1);
     Serial.println(t2);
     int cpos= myservo.read();
     int cpos2= myservo2.read();
     Serial.println(cpos);
     int diff = t1-cpos;
     int diff2 = t2-cpos2;
     Serial.println(diff);
     if(diff>0){
       Serial.println("new angle is higher");
       for(pos = cpos;pos <= t1; pos +=1 ){
         myservo.write(pos);
         delay(30);
       }
     }else{
       Serial.println("New Angle is lower");
       for(pos = cpos;pos >= t1; pos -=1 ){
         myservo.write(pos);
         delay(30);
       }
     }
     
       if(diff2>0){
       Serial.println("new angle is higher");
       for(pos2 = cpos2;pos2 <= t2; pos2 +=1 ){
         myservo2.write(pos2);
         delay(30);
       }
     }else{
       Serial.println("New Angle is lower");
       for(pos2 = cpos2;pos2 >= t2; pos2 -=1 ){
         myservo2.write(pos2);
         delay(30);
       }
     
      
      
   }
}}
