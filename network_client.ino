//  ---  |     ---   ---  |\  |  ---
// |     |      |   |--   | \ |   |
//  ---   ---  ---   ---  |  \|   |


#include <ESP8266WiFi.h>

const char* ssid = "MTKV-3HXK-HHP4-AXDA";
const char* password = "*[}P!'Ww4({)";

const char * host = "192.168.4.1";        // IP Server

const int httpPort = 80;

const char* Commands;                       // The command variable that is sent to the server                     

int button = 5;                             // push button is connected
bool btn_press = true;                      // The variable to detect the button has been pressed
int con = 0;                                // Variables for mode

IPAddress staticIP(192,168,1,22);
IPAddress gateway(192,168,1,9);
IPAddress subnet(255,255,255,0);

void setup(void)
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Successfully Connecting");  
  Serial.println("Status : Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("-------------------------------------");
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead(button) == LOW) {
    Serial.println("Client-------------------------------");
    Serial.print("Send Command = ");
    if (btn_press == true){
      if (con >= 3) {
        con=0;
      }
      con++;

      switch (con){
        case 1:
          Commands="LED_Blink";
          Serial.println(Commands);
          send_commands();
          break;
        case 2:
          Commands="LED_On";
          Serial.println(Commands);
          send_commands();
          break;
        case 3:
          Commands="LED_Off";
          Serial.println(Commands);
          send_commands();
          break; 
      }
      
      btn_press = false;
    }
  }
  else {
    btn_press = true;
  }
  delay(100);
}


void send_commands(){
  Serial.println("Sending command...");
  Serial.println("Don't press the button for now...");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  // We now create a URI for the request  
  Serial.print("Requesting URL : ");
  Serial.println(Commands);

  // This will send the request to the server
  client.print(String("GET ") + Commands + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: Close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {      
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  Serial.print("Server Reply = "); 
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println("Now you can press the button ...");
  Serial.println("-------------------------------------");
  Serial.println("");
}
