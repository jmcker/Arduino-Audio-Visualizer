void setup() 
{
  Serial.begin(9600);

  // Initialize pins
  for (int i = 2; i <= 10; i++)
    pinMode(i, OUTPUT);

  // Blinks twice and creates a startup pattern
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(10, HIGH);
    delay(100);
    digitalWrite(10, LOW);
    delay(100);
  }
  delay(100);
  screenSaver();
  
}

void loop() 
{
  // Gets the analog value from the AUX port and converts it to voltage 
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);

  // Checks if the AUX port is connected else starts the screen saver
  if (voltage > 1)
    screenSaver();
  else
  {
    // Turns on rows based on the volume of the music dissapates 
    for (int i = 2; i <= 10; i++)
    {
      float threshold = 0.5 / 9 * (i - 2) + 0.05;
      digitalWrite(i, voltage > threshold);
    }
  }
}


// Generates a continues cascade effect of the rows of light
void screenSaver() 
{
  for (int i = 2; i <= 10; i++)
  {
    digitalWrite(i, HIGH);
    delay(50);
  }

  for (int i = 2; i <= 10; i++)
  {
    digitalWrite(i, LOW);
    delay(50);
  }

  for (int i = 10; i >= 2; i--)
  {
    digitalWrite(i, HIGH);
    delay(50);
  }

  for (int i = 10; i >= 2; i--)
  {
    digitalWrite(i, LOW);
    delay(50);
  }
}
