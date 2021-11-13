#define kp -1 //tune according to needs
#define ki -1 //tune according to needs

#include <Adafruit_AHTX0.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "user_interface.h"

extern os_timer_t *timer_list;
timer_list = nullptr;

const char* ssid = "Vayu";
const char* password = "1234";

String server = "http://"; //set according to the server val
boolean flag = false;

Adafruit_AHTX0 aht;


void setup() 
{

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {}

  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  wifi_fpm_set_wakeup_cb(fpm_wakup_cb_func);
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();

  pinMode(15,OUTPUT);
    
  Serial.begin(115200);
  aht.begin();
}

double error=0, terror=0, dtemp=0;
double pid[100];

void loop() 
{
 
  sensors_event_t humidity, temp;

  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      http.begin(client, server.c_str());
      
      drive();

  PCMSK0 ^= (1 << PCINT0);
  wifi_fpm_do_sleep(10000 * 1000);

  }

void pidcalc()
{
  if(http.GET()>0)
  temp=http.getString().toFloat;
  
  for(int i=0;i<100;i++)
  {
  
    aht.getEvent(&humidity, &temp);
    
    error = dtemp-temp.temperature;
    pid[i] = kp*error + ki*terror;
    terror+=error;
  }
}


void drive()
{
  if(flag)
    for(int i=0;i<100;i++)
      for(float z=0.0;z<pid[i];z+=0.5)
      {
        digitalWrite(15, 0);
        delayMicroseconds(z);
        digitalWrite(15, 1);
        delayMicroseconds(z);
        digitalWrite(15, 0);
      }
}

void fpm_wakup_cb_func(void) 
{
  PCMSK0 ^= (1 << PCINT0);
  pidcalc();
}

ISR(PCINT0_vect){
  
  if(PINB & B00000001){                               
    if(last_CH1_state == 0){                          
      flag = true;                      
    }
  }
  else if(last_CH1_state == 1){                      
    flag = false;                                  
    last_CH1_state = 0;                             
    }
}
