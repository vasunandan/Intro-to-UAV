#include <WiFiScan.h>
#include <WiFiType.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <ETH.h>
#include <WiFiGeneric.h>

#define m1 16
#define m2 17
#define m3 18
#define m4 19
#define R_enable HIGH
#define L_enable HIGH

const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";
void forward(){
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);  
}
void backward(){
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);      
}
void left(){
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);   
}
void right(){
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);      
}
void stopp(){
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,LOW);    
}
WiFiServer server(80);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,LOW);
  
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available(); 
  if(client){
    Serial.println("New Client.");          // print a message out in the serial port
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();
        if(request.indexOf("/forward")>0){
          forward();
        }
        else{
          if(request.indexOf("/back")>0){
            backward();
          }
          else{
            if(request.indexOf("/left")>0){
              left();
            }
            else{
               if(request.indexOf("/right")>0){
                right();
              }
              else{
                stopp();                                
              }
            }
          }
        }
//        else if(request.indexOf("/back")>0){
//          backward();
//        }
//        else if(request.indexOf("/left")>0){
//          left();
//        }
//        else if(request.indexOf("/right")>0){
//          right();
//        }
//        else if(request.indexOf("/stop")>0){
//          stopp();
//        }
      }
      webpage(client);//Return webpage
      break;
    }    
  }

}
void webpage(WiFiClient client){
  // Display the HTML web page
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println(".button {background-color: #008CBA; /* Green */border: none;border-radius: 12px;color: white;padding: 40px 32px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 6px 10px;cursor: pointer;}");
  client.println("</style>");
  client.println("<title> UGV_Wifi_Navigation </title>");
  client.println("<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("<meta http-equiv='refresh' content='5'>");
  client.println("</head>");
  client.println("<body bgcolor = '#e7e7e7'> ");
  client.println("<hr/><hr>");
  client.println("<h1 style='color : #3AAA35;'><center> UGV - Web Controller </center></h1>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><center><h2 style='color : #3AAA35;'> LED </h2></center><center>");
  client.println("  <a href='/dig0on'><button>Turn On </button></a>");
  client.println("  <a href='/dig0off'><button>Turn Off </button></a><br /> ");
  client.println("  </center><center>");
  client.println("<table>");
  client.println("<tr>");
  client.println("</tr>");
  client.println("<br><h2 style='color : #3AAA35;'> Navigation </h2><center>");
  client.println("  <a href='/forward'><button>Forward </button></a><br><br>");
  client.println("  <a href='/left'><button>Left</button></a>&ensp ");
  client.println("  <a href='/stop'><button>Stop</button></a>&ensp ");
  client.println("  <a href='/right'><button>Right </button></a> <br>  <br>"); 
  client.println("  <a href='/back'><button>Back </button></a><br > ");
  client.println("<br><h2 style='color : #3AAA35;'> Fixed Path Control </h2><center>");
  client.println("  <a href='/circle'><button>Circle</button></a>&ensp ");
  client.println("  <a href='/rectangle'><button>Rectangle</button></a>&ensp ");
  client.println("  <a href='/square'><button>Square </button></a> <br>  <br>"); 
  client.println("</table></center></body></html>");  
  delay(1);  
}
