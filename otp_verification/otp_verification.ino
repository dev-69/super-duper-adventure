#include "twilio.hpp"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <Keypad.h>
#include<string.h>

const byte ROWS = 4; // Number of rows in the keypad
const byte COLS = 4; // Number of columns in the keypad

// Define the keypad matrix
char keys[ROWS][COLS] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define the keypad pins
byte rowPins[ROWS] = {21, 19, 18, 5};
byte colPins[COLS] = {12, 13, 14, 15};



// Create the keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

static const char *ssid = ""; //WIFI SSID TO BE DECIDED BY THE PERSON SETTING UP
static const char *password = "";//PASSWORD

// Values from Twilio (find them on the dashboard)
static const char *account_sid = "AC747ba638bc7b793644d050a1a4da5d59";
static const char *auth_token = "f1b0850dc888e562830bb1b97492d69f";
// Phone number should start with "+<countrycode>"
static const char *from_number = "+15077057383";

// You choose!
// Phone number should start with "+<countrycode>"
static const char *to_number = "+918454987109"; //Have to find a way to make different numbers appear here.

int random_number = random(1000, 9999);
String otp = String(random_number);

String message = "https://chart.googleapis.com/chart?chs=300x300&cht=qr&chl="+otp+"\n\nTHe OTP is " + otp;

// Define the correct PIN
const String correctPIN = otp;


//Defining number of ATTEMPTS
int attempts = 0;

Twilio *twilio;

void setup() 
{
  Serial.begin(115200);
  Serial.print("Connecting to WiFi network ;");
  Serial.print(ssid);
  Serial.println("...");
  WiFi.begin("Wokwi-GUEST", "", 6);
  //WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("Connecting...");
    delay(500);
  }
  Serial.println("Connected!");

  normal_input();

  if(attempts >= 3)
  {
    Serial.println("\nInitiating the MASTER CALL function\n\n");
    master_input();
    Serial.println("\n\nExiting the Master Call function\n\n");
  }
}



void loop()
{
}

void normal_input()
{
  twilio = new Twilio(account_sid, auth_token);

  delay(1000);
  String response;
  bool success = twilio->send_message(to_number, from_number, message, response);
  if (success) 
  {
    Serial.println("Sent message successfully!");
  } 
  else 
  {
    Serial.println(response);
  }
  
  while(attempts < 4)
  {
    static String input = ""; 
    char key = keypad.getKey(); 
    if (key != NO_KEY)
    {  
      Serial.print(key);
      input += key; 
      if (input.length() == 4 ) 
      { 
        if (input == correctPIN) 
        {
          Serial.println("\nPIN accepted."); // Print a success message to the serial monitor
        }
        else  // If the input does not match the correct PIN
        {
          Serial.println("\nIncorrect PIN. Please try again."); // Print an error message to the serial monitor
          input = "";
          attempts+=1;
        }
      }
    }
  }
  if(attempts >= 4)
  {
    Serial.println("WHAT IS DIS BEHAVIOUR");
  }
}

void master_input()
{
  twilio = new Twilio(account_sid, auth_token);
  int master_number = random(1000, 9999);
  String masterotp = String(master_number);

  String master_message = "The master OTP is "+masterotp;

  delay(1000);
  String respons;
  bool success = twilio->send_message(to_number, from_number, master_message, respons);
  if (success) 
  {
    Serial.println("Sent master message successfully!");
  } 
  else 
  {
    Serial.println(respons);
  }   
  int trial = 1;
  while(trial == 1)
  {
    static String input = ""; 
    char key = keypad.getKey(); 
    
    if (key != NO_KEY)
    {
      Serial.print(key);
      input += key; 
      if (input.length() == 4) 
      { 
        if (input == masterotp) 
        {
          Serial.println("\nPIN accepted."); // Print a success message to the serial monitor
        }
        else  // If the input does not match the correct PIN
        {
          Serial.println("\nIncorrect PIN. Please try again."); // Print an error message to the serial monitor
          input = "";
          trial=0;
        }
      }
    }
  }
}
