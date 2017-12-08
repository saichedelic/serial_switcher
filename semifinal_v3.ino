#include <avr/io.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include "SoftTimer.h"
//#include "LowPower.h"

#define NODE_ID 1

SoftTimer timer;
  //Serial data buffer
String inputString = "";

  //Restore_Update Latest value
void sync_val()
{
  digitalWrite(2,EEPROM.read(0));
  digitalWrite(3,EEPROM.read(1));
  digitalWrite(4,EEPROM.read(2));
  digitalWrite(5,EEPROM.read(3));
  digitalWrite(6,EEPROM.read(4));
  digitalWrite(7,EEPROM.read(5));
  digitalWrite(8,EEPROM.read(6));
  digitalWrite(9,EEPROM.read(7));
  digitalWrite(10,EEPROM.read(8));
  digitalWrite(11,EEPROM.read(9));
  digitalWrite(12,EEPROM.read(10));
  digitalWrite(A0,EEPROM.read(11));
  digitalWrite(A1,EEPROM.read(12));
  digitalWrite(A2,EEPROM.read(13));
  digitalWrite(A3,EEPROM.read(14));
  digitalWrite(A4,EEPROM.read(15));
} 

void rst_val()
{
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
} 

  //Send Master Current Value
void read_val_send()
{
  String readval;
  readval.concat(NODE_ID);
  readval.concat(":");
  readval.concat(EEPROM.read(0));
  readval.concat(EEPROM.read(1));
  readval.concat(EEPROM.read(2));
  readval.concat(EEPROM.read(3));
  readval.concat(EEPROM.read(4));
  readval.concat(EEPROM.read(5));
  readval.concat(EEPROM.read(6));
  readval.concat(EEPROM.read(7));
  readval.concat(EEPROM.read(8));
  readval.concat(EEPROM.read(9));
  readval.concat(EEPROM.read(10));
  readval.concat(EEPROM.read(11));
  readval.concat(EEPROM.read(12));
  readval.concat(EEPROM.read(13));
  readval.concat(EEPROM.read(14));
  readval.concat(EEPROM.read(15));
  Serial.println(readval);
}

// Update Master with monitor data
void monitor_req()
{
  String readvalu;
  readvalu.concat(NODE_ID);
  readvalu.concat(":");
  readvalu.concat(digitalRead(2));
  readvalu.concat(digitalRead(3));
  readvalu.concat(digitalRead(4));
  readvalu.concat(digitalRead(5));
  readvalu.concat(digitalRead(6));
  readvalu.concat(digitalRead(7));
  readvalu.concat(digitalRead(8));
  readvalu.concat(digitalRead(9));
  readvalu.concat(digitalRead(10));
  readvalu.concat(digitalRead(11));
  readvalu.concat(digitalRead(12));
  readvalu.concat(digitalRead(A0));
  readvalu.concat(digitalRead(A1));
  readvalu.concat(digitalRead(A2));
  readvalu.concat(digitalRead(A3));
  readvalu.concat(digitalRead(A4));
  Serial.println(readvalu);
}

  //Update received Value from Master
void wrt_val_rvc()
{
  String updater = getValue(inputString, ':', 1);
  updater.trim();
  EEPROM.write(0,(char(updater[0])-'0'));
  EEPROM.write(1,(char(updater[1])-'0'));
  EEPROM.write(2,(char(updater[2])-'0'));
  EEPROM.write(3,(char(updater[3])-'0'));
  EEPROM.write(4,(char(updater[4])-'0'));
  EEPROM.write(5,(char(updater[5])-'0'));
  EEPROM.write(6,(char(updater[6])-'0'));
  EEPROM.write(7,(char(updater[7])-'0'));
  EEPROM.write(8,(char(updater[8])-'0'));
  EEPROM.write(9,(char(updater[9])-'0'));
  EEPROM.write(10,(char(updater[10])-'0'));
  EEPROM.write(11,(char(updater[11])-'0'));
  EEPROM.write(12,(char(updater[12])-'0'));
  EEPROM.write(13,(char(updater[13])-'0'));
  EEPROM.write(14,(char(updater[14])-'0'));
  EEPROM.write(15,(char(updater[15])-'0'));
  sync_val();
}


void setup() 
{
  Serial.begin(9600);

  timer.every(5000, watchdogReset);

  //Watch Dog Timer Enable
  wdt_enable(WDTO_8S);

  //Output Pins Declaration
  pinMode(A5, INPUT);
  bool ctrlpin = digitalRead(A5);
  if (ctrlpin == 1)
  { 
    String readval;
    readval.concat(NODE_ID);
    readval.concat(":AUTO");
    Serial.println(readval);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    sync_val();
  }
  else if (ctrlpin == 0)
  {
    String readval;
    readval.concat(NODE_ID);
    readval.concat(":MANW");
    Serial.println(readval);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    pinMode(12, INPUT);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    rst_val();
  }
  // Restore Previous Value
  
  
  
}

bool ctrlpin = digitalRead(A5);


  // String Splitter

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void loop() 
{
  timer.update();
  //Low Power Idler
  //LowPower.idle(SLEEP_4S, ADC_ON, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_ON, TWI_OFF);
  //delay(2000);
  //wdt_reset();
  //Serial.println("RESET!");
}


boolean watchdogReset(EventBase* evt)
{
    wdt_reset();

    return false;
}


  // Serial - Pins Update

void serialEvent() 
{
  //bool ctrlpin = digitalRead(A5);
  while (Serial.available()) 
  {
    inputString = Serial.readString();
  if ((getValue(inputString, ':', 0)).toInt() == NODE_ID)
  {
    String MODE = getValue(inputString, ':', 1);
    MODE.trim();
    if (MODE == "READ")
    { 
      read_val_send();
    }
    else if (MODE == "SYNC")
    {
      if (ctrlpin == 0)
      {
        sync_val();
      }
    }
    else if (MODE == "MON_REQ")
    {
      if (ctrlpin == 0)
      {
        monitor_req();
      }
    }
    else
    {
      if (ctrlpin == 1);
      {
        wrt_val_rvc();
      }
    }
   }
  }
}

