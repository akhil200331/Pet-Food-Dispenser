//----------------------------------------Include the NodeMCU ESP8266 Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <AccelStepper.h> //Include the AccelStepper library
#define MP1  5 // D1
#define MP2  4 // D2
#define MP3  14 // D5
#define MP4  12 // D6
//#define ON_Board_LED 2  //--> Defining an On Board LED (GPIO2 = D4), used for indicators when the process of connecting to a wifi router
const int BUZZER_PIN       = 0; //D3

#define MotorInterfaceType 8 // Define the interface type as 8 = 4 wires * step factor (2 for half step)
AccelStepper stepper = AccelStepper(MotorInterfaceType, MP1, MP3, MP2, MP4);//Define the pin sequence (IN1-IN3-IN2-IN4)
const int SPR = 512;//Steps per revolution
 
//#define LED_D8 15 //--> Defines an LED Pin. D8 = GPIO15

//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "Akhil"; //--> Your wifi name or SSID.
const char* password = "1234567899"; //--> Your wifi password.
//----------------------------------------

//----------------------------------------Web Server address / IPv4
/// If using IPv4, press Windows key + R then type cmd, then type ipconfig (If using Windows OS).
// String host_or_IPv4 = "http://Your_Host_or_IP";
// Example :
// String host_or_IPv4 = "http://192.168.0.0/";
String host_or_IPv4 = "http://192.168.35.246/";

String Destination = "";
String URL_Server = "";
String Destinationn = "";
String URL_Serverr = "";
char server[] = "192.168.35.246";
//----------------------------------------
String StatResultSend="";
//----------------------------------------
String getData = "";
String payloadGet = "";
String postData="";
String payloadSend = "";
//----------------------------------------

//----------------------------------------
HTTPClient http; //--> Declare object of class HTTPClient
WiFiClient client;
//----------------------------------------
int requestdata_sending_back_to_server=9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  pinMode(BUZZER_PIN, OUTPUT); 
  stepper.setMaxSpeed(3000);//Set the maximum motor speed in steps per second
  stepper.setAcceleration(600);//Set the maximum acceleration in steps per second^2
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  //pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  //digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //pinMode(LED_D8,OUTPUT); //--> LED port Direction output
  //digitalWrite(LED_D8, LOW); //--> Turn off Led

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    //digitalWrite(ON_Board_LED, LOW);
   // delay(250);
    //digitalWrite(ON_Board_LED, HIGH);
    //delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  //digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  delay(2000);
}
void motor_run(){
  stepper.moveTo(-1*SPR); //Set the target motor position (i.e. turn motor for 3 full revolutions)
  stepper.runToPosition(); // Run the motor to the target position 
  delay(1000);
  stepper.moveTo(1*SPR);//Same as above: Set the target motor position (i.e. turn motor for 3 full revolutions)
  stepper.runToPosition(); // Run the motor to the target position 
}
void loop() {
  // put your main code here, to run repeatedly:
  
  //----------------------------------------
  // From my tests, after uploading the program code, the connection for the first time may fail (-1). But the next connection is fine/runs smoothly.
  //----------------------------------------

  //----------------------------------------Getting Data from MySQL Database

  int id = 0; //--> ID in Database 
  getData = "ID=" + String(id);
  Destination = "ECS/GetData.php";
  URL_Server = host_or_IPv4 + Destination;
  Serial.println("----------------Connect to Server-----------------");
  Serial.println("Get LED Status from Server or Database");
  Serial.print("Request Link : ");
  Serial.println(URL_Server);
  http.begin(client, URL_Server); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCodeGet = http.POST(getData); //--> Send the request
  payloadGet = http.getString(); //--> Get the response payload from server
  Serial.print("Response Code : "); //--> If Response Code = 200 means Successful connection, if -1 means connection failed. For more information see here : https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
  Serial.println(httpCodeGet); //--> Print HTTP return code
  Serial.print("Returned data from Server : ");
  Serial.println(payloadGet); //--> Print request response payload
  String res=String(payloadGet);
  if (res=="1"){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(5000);
    digitalWrite(BUZZER_PIN, LOW);
    motor_run();
    delay(40000);
  }
  else{
    Serial.println("Not Time");
  }
  delay(1000);
  //if (payloadGet != "1") {
    //Motor Rotation we set motor status
    //requestdata_sending_back_to_server=1;

  //}
  /*if (payloadGet == "0") {
    digitalWrite(LED_D8, LOW); //--> Turn off Led
  }
  LEDStatResultSend = String(digitalRead(LED_D8));
  //----------------------------------------*/
  /*/----------------------------------------Sends Which Conveyor Belt feedback data to server
  Serial.println();
  Serial.println("Sending Coneyor Belt Status to Server");
  Destinationn = "NodeMCU/getConveyorBeltStatFromNodeMCU.php";
  URL_Serverr = host_or_IPv4 + Destinationn;
  StatResultSend=String(requestdata_sending_back_to_server);
  postData = "getConveyorBeltStatusFromNodeMCU=" + StatResultSend+"&hello=6";
  Serial.print("Request Link : ");
  Serial.println(URL_Serverr);
  http.begin(client, URL_Serverr); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //--> Specify content-type header
  int httpCodeSend = http.POST(postData); //--> Send the request
  payloadSend = http.getString(); //--> Get the response payload
  Serial.print("Response Code : "); //--> If Response Code = 200 means Successful connection, if -1 means connection failed
  Serial.println(httpCodeSend); //--> Print HTTP return code
  Serial.print("Returned data from Server : ");
  Serial.println(payloadSend); //--> Print request response payload
  //----------------------------------------*/

  Serial.println("----------------Closing Connection----------------");
  http.end(); //--> Close connection
  Serial.println();
  Serial.println("Please wait 10 seconds for the next connection.");
  Serial.println();
  delay(5000);
  //sendtoserver();
  delay(10000); //--> GET Data at every 10 seconds. From the tests I did, when I used the 5 second delay, the connection was unstable
}
/*void sendtoserver(){
if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET/ecs/getConveyorBeltStatFromNodeMCU.php?st=");
    client.print("GET/ecs/getConveyorBeltStatFromNodeMCU.php?st=");     //YOUR URL
    Serial.println(requestdata_sending_back_to_server);
    client.print(requestdata_sending_back_to_server);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(23);
    Serial.println(23);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: Your Local IP");
    client.println("Connection: close");
    client.println();
    client.stop();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}*/