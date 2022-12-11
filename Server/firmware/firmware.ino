/*
 Web Server

 A Web server to accept requests from client apps and perform opperation.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Appliances at PIN 7 and PIN 8

 created 11 DEC 2022
 by EDWARD M. TLADI

 # MESSAGE STRUCTURE
    * ACCEPT HTTP REQUESTS    : [GET | POST | PUT | DELETE]
    * ARDUINO RESPONSE : [200 OK | 201 CREATED | 404 NOT FOUND | 301 REDIRECT| 500 SERVER PROBLEM] 

# PRESET COMMANDS
    * Toggle pin number (0x01) | 0x00
    * Get anolog data   (0x02)
    * Get device information (0x03)
    * char respose[6] = {0x01,0x08,0x08,0x04,0x08,0x00};
 */

 // File systems
#include <SD.h>

// Serial communication
#include <SPI.h>

// Http communication
#include <Ethernet.h>

// Server connection
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   
EthernetServer server(80);
EthernetServer telnet_server(23);

// Const
String http_request = "";
File Webpage;
#define EOF -1
#define SD_SLOT 4


void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  pinMode(SD_SLOT, OUTPUT);
  digitalWrite(SD_SLOT, HIGH);
   
  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
  telnet_server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  Serial.println("Initialzing SD card..");
  
  if(!SD.begin(SD_SLOT))
  {
     Serial.println("Error : SD card initialization failed! \n");
     return;
  }
  Serial.println("Success : SD card initialization Passed! \n");
  

  if(!SD.exists("index.htm"))
  {
    Serial.println("Error - can't find index.html file!\n");
    return;
  }
  Serial.println("Success : Found index.html (Nice Website though)! \n");
  
  
}


void loop() 
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) 
  {
    Serial.println("new client");
    
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 200");  // refresh the page automatically every 5 sec
          client.println();
   

          Webpage = SD.open("index.htm");
          if(Webpage)
          {
            while(Webpage.available())
            {
              client.write(Webpage.read());
            }
          }
          Webpage.close();          
          
          break;
        }
        if (c == '\n') 
        {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') 
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
