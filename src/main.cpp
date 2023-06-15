#include <WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Define the LED pin
#define LEDPINA 13
#define LEDPINB 12

// Insert your network credentials
#define WIFI_SSID "iPhone van ******"
#define WIFI_PASSWORD "*********"

// Insert Firebase project API Key
#define API_KEY "AIza***********************MGXz1Kw"

// Insert RTDB URL
#define DATABASE_URL "https://led-lampjes-*******************ope-west1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

int ledValue1 = 0;
int ledValue2 = 0;

void setup(){
  Serial.begin(115200);
  pinMode(LEDPINA, OUTPUT); // Set the LED pin as an output
  pinMode(LEDPINB, OUTPUT); // Set the LED pin as an output
  digitalWrite(LEDPINA, LOW); // Turn off the LED
  digitalWrite(LEDPINB, LOW); // Turn off the LED
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  
  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Set up initial LED values in Firebase
  Firebase.RTDB.setInt(&fbdo, "/leds/led1", ledValue1);
  Firebase.RTDB.setInt(&fbdo, "/leds/led2", ledValue2);
  Serial.println("LEDs initialized in Firebase");
}

void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    
    // Toggle LED values
    ledValue1 = !ledValue1;
    ledValue2 = !ledValue2;
    
    // Turn on or off the LED depending on the value of ledValue1
    if (ledValue1) {
      digitalWrite(LEDPINA, HIGH);
    } else {
      digitalWrite(LEDPINA, LOW);
    }

    if (ledValue2) {
      digitalWrite(LEDPINB, HIGH);
    } else {
      digitalWrite(LEDPINB, LOW);
    }
    
    // Update Firebase with LED values
    if (Firebase.RTDB.setInt(&fbdo, "/leds/led1", ledValue1)){
      Serial.println("LED1 set successfully");
    }
    else {
      Serial.println("Error setting LED1");
      Serial.println(fbdo.errorReason());
    }
    if (Firebase.RTDB.setInt(&fbdo, "/leds/led2", ledValue2)){
      Serial.println("LED2 set successfully");
    }
    else {
      Serial.println("Error setting LED2");
      Serial.println(fbdo.errorReason());
    }
  }
}