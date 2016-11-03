#include <DHT.h>

#define DHTIN 2
#define DHTOUT 3

#define DHTTYPE DHT22



#define LIQUID_PIN A0

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

DHT dht(DHTIN, DHTOUT, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  int h = dht.readHumidity()*1000;
  int t = dht.readTemperature()*1000;

  if (h >=0 && h <= 100000){
    if(isnan(h))
  {
    Serial.println("Couldn't read humidity!");
  }
  else
  {
    String hString = String(h);
    String commandHumidity = String("echo `date -u +\"%Y-%m-%dT%H:%M:%SZ\"`,"+ hString + ">>~/humidity.txt");
    char commandHumidityArray[commandHumidity.length()+1];
    commandHumidity.toCharArray(commandHumidityArray,commandHumidity.length()+1);
    system(commandHumidityArray);
    Serial.print(h);

    
    }
    
  }

  if (t >= -50000 && t <= 100000) {
    if(isnan(h) || isnan(t))
  {
    Serial.println("Couldn't read temp!");
  }
  else
  {
    String tString = String(t);
    String commandTemperature = String("echo `date -u +\"%Y-%m-%dT%H:%M:%SZ\"`,"+ tString + ">>~/temperature.txt");
    char commandTemperatureArray[commandTemperature.length()+1];
    commandTemperature.toCharArray(commandTemperatureArray,commandTemperature.length()+1);
    system(commandTemperatureArray);
    Serial.println(t);   
    }
      }


  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(LIQUID_PIN);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings)
    // ...wrap around to the beginning:
    readIndex = 0;

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  //Serial.println(average);
  //char averageChar = average;

  String averageString = String(average);
  
  String command = String("echo `date -u +\"%Y-%m-%dT%H:%M:%SZ\"`,"+ averageString + ">>~/liquid.txt");
  char commandArray[command.length()+1];
  command.toCharArray(commandArray,command.length()+1);
  system(commandArray);
  delay(1000);
    

  
  delay(1000);
}
