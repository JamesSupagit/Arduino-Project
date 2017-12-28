#include <ESP8266WiFi.h>
#include "DHT.h"
 
const char* ssid = "Pitsanu_1";
const char* password = "054459096";
#define Relay1 D1
#define Relay2 D2
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
WiFiServer server(80);
void setup() {
  Serial.begin(9600);
  delay(10);
  dht.begin();
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  digitalWrite(Relay1,LOW);
  digitalWrite(Relay2,LOW);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
   
  if (req.indexOf("/r1off.html") != -1)
  {
    digitalWrite(Relay1,LOW);
      
  }
  else if (req.indexOf("/r1on.html") != -1)
  {
    digitalWrite(Relay1,HIGH);
  }
   else if (req.indexOf("/r2on.html") != -1)
  {
    digitalWrite(Relay2,HIGH);
  }
   else if (req.indexOf("/r2off.html") != -1)
  {
    digitalWrite(Relay2,LOW);
  }
  else if(req.indexOf("/Temp_.html") != -1)
  {
     float h = dht.readHumidity();
     float t = dht.readTemperature();
    client.flush();
    String humi="<h3>Temp = ";
    humi += String(t)+" C</h3>\r\n";
    humi += "<h3>Humidity = ";
    humi += String(h)+" %</h3>\r\n";
    client.print(humi);

    Serial.println(t);
  }
  else if(req.indexOf("/") != -1)
  {
    client.flush();
    String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    web += "<html>\r\n";
    web += "<head>\r\n";
    web += "<style>\r\n";
    web += ".button-red,.button-blue\r\n"; 
    web += "{color: white;\r\n";
    web += "border-radius: 9px;\r\n";
    web += "font-family:Arial;\r\n";
    web += "font-size:25px;\r\n";
    web += "padding:50px 80px;\r\n";
    web += "}\r\n";
    web += ".button-red:hover:active,.button-blue:hover:active\r\n"; 
    web += "{position:relative;top:3px;color: yellow;}\r\n";
    web += ".button-red {background: rgb(202, 60, 60);}\r\n";
    web += ".button-blue {background: rgb(100,116,255);}\r\n";
    web += "h1{color:black;font-family:Arial;font-size:40px;text-align:center;}\r\n";         
    web += "</style>\r\n";
    web += "<script>\r\n";
    web += "var ajax = null;\r\n";
    web += "if (window.XMLHttpRequest)\r\n";
    web += "{ajax =new XMLHttpRequest();}\r\n";
    web += "else\r\n";
    web += "{ajax=new ActiveXObject(\"Microsoft.XMLHTTP\");}\r\n";
    web += "function ajaxLoad(method ,URL,displayElementId,sendData)\r\n";
    web += "{\r\n";
    web += "if(!ajax){alert(\"not support\");return;}\r\n";
    web += "ajax.open(method,URL,true);\r\n";
    web += "ajax.on-readystatechange = function()\r\n";
    web += "{\r\n";
    web += "if(ajax.readyState == 4 && ajax.status==200)\r\n";
    web += "{\r\n";
    web += "var ajax_result = ajax.responseText;\r\n";
    web += "var el = document.getElementById(displayElementId);\r\n";
    web += "el.innerHTML = ajax_result;\r\n";
    web += "}\r\n";
    web += "}\r\n"; 
    web += "ajax.send(sendData);\r\n";
    web += "}\r\n";
    web += "function update_temp_humi()\r\n"; 
    web += "{\r\n";
    web += "var URL = \"/Temp_.html\";\r\n";
    web += "ajaxLoad(\"GET\",URL,\'temp_humi\',null);\r\n";
    web += "}\r\n";
    web += "</script>\r\n";
    web += "</head>";
    web += "<body>";
    web += "<h1>Demo Web Server Ajax</h1>"; 
    web += "<h2>Temp and Humidity</h2>";
    web += "<div id=\"temp_humi\">";
    web += "<h3>Temp = xx C</h3>"; 
    web += "<h3>Humidity = xx %</h3>";
    web += "</div>";
    web += "<p><div><input class=\"button-red\" type=\"button\" value=\"Relay 1 On\" on-click=\"Relay(\'r1on\')\">";
    web += "<input class=\"button-blue\" type=\"button\" value=\"Relay 1 Off\" on-click=\"Relay(\'r1off\')\"></P>";
    web += "<p><input class=\"button-red\" type=\"button\" value=\"Relay 2 On\" on-click=\"Relay(\'r2on\')\">";
    web += "<input class=\"button-blue\" type=\"button\" value=\"Relay 2 Off\" on-click=\"Relay(\'r2off\')\"></P>";
    web += "<script>";
    web += "function Relay(state){ajaxLoad(\"GET\",state+\'.html\',null,null);}";   
    web += "setInterval(\"update_temp_humi()\",2000);";
    web += "</script>";
    web += "</body>";
    web += "</html>";
    client.print(web);
 
    return;
  }
}
