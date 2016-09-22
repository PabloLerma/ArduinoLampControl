#include <SPI.h>
#include <Ethernet.h>

boolean incoming = 0;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
IPAddress ip(192,168,1,177);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
  pinMode(2, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        
        //reads URL string from $ to first blank space
        if(incoming && c == ' ') { 
          incoming = 0;
        }
        if(c == '$') { 
          incoming = 1; 
        }
        
        //Checks for the URL string $1 or $2
        if(incoming == 1) {          
          if(c == '1') {
            Serial.println("ON");
            digitalWrite(2, HIGH);
            break;
          }
          if(c == '2') {
            Serial.println("OFF");
            digitalWrite(2, LOW);
            break;
          }
        }

        if (c == '\n') {
          // you're starting a new line
//          Serial.println("currentLineIsBlank");
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
//          Serial.println("character on the current line");
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    Serial.println("Closing connection");
    client.stop();
  }
}

