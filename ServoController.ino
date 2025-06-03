#include<ESP8266WebServer.h>
#include<ESP8266WiFi.h>
#include "LittleFS.h"

//Your wifi Name 
const char* SSID = "MyTeritoryMyRules";

//your password - at least 8 characters!
const char* password = "12341234";

IPAddress local_IP(192,168,10,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

#define LED_G D13
#define LED_R D12

class LED{
    public:

    //htpp adresses of each json endpoint to turn on/off led
    const char* led_on;
    const char* led_off;

    //1 - LED ON
    //0 - LED OFF
    bool turn;

    int led_pin;

      LED(int led_pin1, const char* led_on1,const char* led_off1){
        led_pin = led_pin1;
        led_on = led_on1;
        led_off = led_off1;
        turn = false;
        };
};

LED Led_g(LED_G,"/led_g_on","/led_g_off");
LED Led_r(LED_R,"/led_r_on","/led_r_off");


void LedControl(){

//TURN RED LED ON
  server.on(Led_r.led_on,HTTP_GET,[](){ Led_r.turn = true; }); 

//TURN GREEN LED ON
     server.on(Led_g.led_on,HTTP_GET,[](){Led_g.turn = true;}); 

//TURN REDLED Off
    server.on(Led_r.led_off,HTTP_GET,[](){Led_r.turn = false;});
  
//TURN GREEN LED Off
    server.on(Led_g.led_off,HTTP_GET,[](){Led_g.turn = false; });

}

void HandleRoot(){

  File file = LittleFS.open("/index.html","r");

  if(!file){
     server.send(404,"text/plain","ERROR, NO HTML detected!");
    return ;
  }
  
  server.streamFile(file,"text/html");
  file.close();
}

void HandleCss(){
  File file = LittleFS.open("/styles.css","r");
  server.streamFile(file,"text/css");
  file.close();
}

void HandleJs(){
  File file = LittleFS.open("/server_API.js","r");
  server.streamFile(file,"application/javascript");
  file.close();
}

void setup() {

  Serial.begin(115200);
  
  //optional - manually setting up the IP adress of our WiFI;
  WiFi.softAPConfig(local_IP,local_IP ,subnet);

  WiFi.softAP(SSID,password);

  Serial.println(WiFi.softAPIP());

  while(!LittleFS.begin()){
    Serial.print("SPIFFS not init!");
    return;
  }
  
  server.on("/",HTTP_GET,HandleRoot);
  server.on("/styles.css",HTTP_GET,HandleCss);
  server.on("/server_API.js",HTTP_GET,HandleJs);

  LedControl();

  pinMode(LED_G,OUTPUT);
  pinMode(LED_R,OUTPUT);
  server.begin();
}

void loop() {

  server.handleClient();

    if(Led_r.turn){
      digitalWrite(LED_R,HIGH);
      delay(50);
      digitalWrite(LED_R,LOW);
      delay(50);
    }
    else digitalWrite(LED_R,LOW);

    if(Led_g.turn){
      digitalWrite(LED_G,HIGH);
      delay(50);
      digitalWrite(LED_G,LOW);
      delay(50);
    }
    else digitalWrite(LED_G,LOW);
}
