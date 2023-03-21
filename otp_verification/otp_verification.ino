#include "twilio.hpp"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <Keypad.h>

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
static const char *to_number = "+918928479729"; //Have to find a way to make different numbers appear here.

int random_number = random(1000, 9999);
String otp = String(random_number);
String message = "Your OTP(One Time Password) code is " + otp;

// Define the correct PIN
const String correctPIN = otp;

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
}

void loop() {
  static String input = ""; // Initialize the input string as empty and make it static to preserve its value between loop iterations
  char key = keypad.getKey(); // Read the key pressed on the keypad
  if (key != NO_KEY) { // If a key was pressed
    Serial.print(key); // Print the key to the serial monitor
    input += key; // Append the key to the input string
    if (input.length() == 4) { // If 4 digits have been entered
      if (input == correctPIN) { // If the input matches the correct PIN
        Serial.println("\nPIN accepted."); // Print a success message to the serial monitor
      }
      else { // If the input does not match the correct PIN
        Serial.println("\nIncorrect PIN. Please try again."); // Print an error message to the serial monitor
      }
      input = ""; // Clear the input string for the next entry
    }
  }
}
