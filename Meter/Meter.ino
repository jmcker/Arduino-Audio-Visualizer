// Number of rows that make up the bar
#define METER_HEIGHT 9

void setup() 
{

    Serial.begin(9600);

    // Initialize pins
    for (int i = 2; i <= METER_HEIGHT + 1; i++)
        pinMode(i, OUTPUT);

    // Blink twice and run startup pattern
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

    // Read values from the 3.5mm feed on A0 and convert it to "voltage" 
    int sensorValue = analogRead(A0);
    float voltage = sensorValue * (5.0 / 1023.0);

    Serial.println(voltage);

    // Block extraneous signal when the 3.5mm is unplugged
    if (voltage > 1)
        screenSaver();
    else
    {

        // Turn on or off rows based on the "volume"
        for (int i = 2; i <= METER_HEIGHT + 1; i++)
        {
            float threshold = 0.5 / METER_HEIGHT * (i - 2) + 0.05;
            digitalWrite(i, voltage > threshold);
        }

    }

}

// LED chase effect that serves as a screensaver
void screenSaver() 
{

    for (int i = 2; i <= METER_HEIGHT + 1; i++)
    {
        digitalWrite(i, HIGH);
        delay(50);
    }

    for (int i = 2; i <= METER_HEIGHT + 1; i++)
    {
        digitalWrite(i, LOW);
        delay(50);
    }

    for (int i = METER_HEIGHT + 1; i >= 2; i--)
    {
        digitalWrite(i, HIGH);
        delay(50);
    }

    for (int i = METER_HEIGHT + 1; i >= 2; i--)
    {
        digitalWrite(i, LOW);
        delay(50);
    }

}
