// Define LED pins
const int LED_PIN_1 = 9;
const int LED_PIN_2 = 10;
const int LED_PIN_3 = 11;
const int LED_PIN_4 = 5;
const int LED_PIN_5 = 6;
const int LED_PIN_6 = 7;

// Define delay time in milliseconds
const int DELAY_TIME = 125; // Adjust the delay time as needed for your desired effect

// Function to run startup sequence
void startupSequence() {
  /*// Initialize each LED individually before the sweep
  digitalWrite(LED_PIN_1, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_1, LOW);
  delay(DELAY_TIME);
  
  digitalWrite(LED_PIN_2, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_2, LOW);
  delay(DELAY_TIME);
  
  digitalWrite(LED_PIN_3, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_3, LOW);
  delay(DELAY_TIME);
  
  digitalWrite(LED_PIN_4, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_4, LOW);
  delay(DELAY_TIME);
  
  digitalWrite(LED_PIN_5, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_5, LOW);
  delay(DELAY_TIME);
  
  digitalWrite(LED_PIN_6, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_6, LOW);
  delay(DELAY_TIME);*/

  // Sweep from left to right
  digitalWrite(LED_PIN_1, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_2, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_3, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_4, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_5, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_6, HIGH);
  delay(DELAY_TIME);

  /*// Turn off LEDs
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, LOW);
  digitalWrite(LED_PIN_5, LOW);
  digitalWrite(LED_PIN_6, LOW);*/

  // Sweep from right to left
  digitalWrite(LED_PIN_6, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_5, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_4, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_3, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_2, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_1, LOW);
  delay(DELAY_TIME);

  /*// Turn off LEDs
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, LOW);
  digitalWrite(LED_PIN_5, LOW);
  digitalWrite(LED_PIN_6, LOW);*/

  // Sweep from left to right (twice as fast)
  digitalWrite(LED_PIN_1, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_2, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_3, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_4, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_5, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_6, HIGH);
  delay(DELAY_TIME);

  /*// Turn off LEDs
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, LOW);
  digitalWrite(LED_PIN_5, LOW);
  digitalWrite(LED_PIN_6, LOW);*/

  // Sweep from right to left (twice as fast)
  digitalWrite(LED_PIN_6, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_5, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_4, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_3, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_2, LOW);
  delay(DELAY_TIME);
  digitalWrite(LED_PIN_1, LOW);
  delay(DELAY_TIME * 3);

  /*// Turn off LEDs
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, LOW);
  digitalWrite(LED_PIN_5, LOW);
  digitalWrite(LED_PIN_6, LOW);*/

  // Blink all LEDs three times
  for (int j = 0; j < 3; j++) {
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, HIGH);
    digitalWrite(LED_PIN_4, HIGH);
    digitalWrite(LED_PIN_5, HIGH);
    digitalWrite(LED_PIN_6, HIGH);
    delay(DELAY_TIME);
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
    digitalWrite(LED_PIN_4, LOW);
    digitalWrite(LED_PIN_5, LOW);
    digitalWrite(LED_PIN_6, LOW);
    delay(DELAY_TIME);
  }
}

long result[6]; // array for storing results for six blocks
int numSamples = 4; // number of readings
int clearcount; // clear test variable
int clearsample = 25; // number of clear samples needed from sensor
int threshold = 525; // ADJUST THIS FOR SENSITIVITY minimum threshold for tripping the sensor
int values[6]; // array to store readings from six analog inputs
int outputs[6]; // array to store output states

void setup() {
  Serial.begin(9600); // starts serial monitor
  pinMode(LED_PIN_1, OUTPUT); // output for control
  pinMode(LED_PIN_2, OUTPUT); // output for control
  pinMode(LED_PIN_3, OUTPUT); // output for control
  pinMode(LED_PIN_4, OUTPUT); // output for control
  pinMode(LED_PIN_5, OUTPUT); // output for control
  pinMode(LED_PIN_6, OUTPUT); // output for control
  
  // Run LED startup sequence
  startupSequence();
}

enum OCCUPANCY {
  ST_OCCUPIED,
  ST_CLEAR,
}; // Our occupancy states

OCCUPANCY Occupancy = ST_CLEAR; // default state

void loop() {
  for (int block = 0; block < 6; ++block) {
    for (int sample = 0; sample < 10; ++sample) {
      result[block] = 0;

      // Read values from the analog pin for each block
      for (int i = 0; i < numSamples; ++i) {
        values[block] = analogRead(A1 + block * 2); // reads analog pin for each block
        result[block] += values[block]; // adds new reading to variable 'result'
        delay(5); // reading every 0.005 seconds
      }

      int averageValue = result[block] / numSamples; // averages readings
      Serial.print("Block ");
      Serial.print(block + 1);
      Serial.print(", Sample ");
      Serial.print(sample + 1);
      Serial.print(": ");
      Serial.println(averageValue); // displays average reading

      // Control digital pins 5, 6, 7, 9, 10, and 11 based on analog input values
      if (block == 0) {
        digitalWrite(LED_PIN_1, averageValue < threshold ? HIGH : LOW);
      } else if (block == 1) {
        digitalWrite(LED_PIN_2, averageValue < threshold ? HIGH : LOW);
      } else if (block == 2) {
        digitalWrite(LED_PIN_3, averageValue < threshold ? HIGH : LOW);
      } else if (block == 3) {
        digitalWrite(LED_PIN_4, averageValue < threshold ? HIGH : LOW);
      } else if (block == 4) {
        digitalWrite(LED_PIN_5, averageValue < threshold ? HIGH : LOW);
      } else if (block == 5) {
        digitalWrite(LED_PIN_6, averageValue < threshold ? HIGH : LOW);
      }

      // Additional logic for controlling outputs based on analog inputs if needed
      // ...

      // Additional logic for switching states based on conditions
      // ...
    }
  }
}
