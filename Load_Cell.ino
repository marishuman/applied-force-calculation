#include <Adafruit_NAU7802.h>
int compZero = 0;
int i = 0;
int zero = 0;
double avgGiven = 0;
int given = 0;
double slope = 0;
double compRead = 0;
double yAvg = 0;
double yMax = 0;
double proceed = 0;
double max = 0;
Adafruit_NAU7802 nau;

void setup() {
  Serial.begin(115200);
  Serial.println("NAU7802");
  if (! nau.begin()) {
    Serial.println("Failed to find NAU7802");
  }
  Serial.println("Found NAU7802");

  nau.setLDO(NAU7802_3V0);
  Serial.print("LDO voltage set to ");
  switch (nau.getLDO()) {
    case NAU7802_4V5:  Serial.println("4.5V"); break;
    case NAU7802_4V2:  Serial.println("4.2V"); break;
    case NAU7802_3V9:  Serial.println("3.9V"); break;
    case NAU7802_3V6:  Serial.println("3.6V"); break;
    case NAU7802_3V3:  Serial.println("3.3V"); break;
    case NAU7802_3V0:  Serial.println("3.0V"); break;
    case NAU7802_2V7:  Serial.println("2.7V"); break;
    case NAU7802_2V4:  Serial.println("2.4V"); break;
    case NAU7802_EXTERNAL:  Serial.println("External"); break;
  }

  nau.setGain(NAU7802_GAIN_128);
  Serial.print("Gain set to ");
  switch (nau.getGain()) {
    case NAU7802_GAIN_1:  Serial.println("1x"); break;
    case NAU7802_GAIN_2:  Serial.println("2x"); break;
    case NAU7802_GAIN_4:  Serial.println("4x"); break;
    case NAU7802_GAIN_8:  Serial.println("8x"); break;
    case NAU7802_GAIN_16:  Serial.println("16x"); break;
    case NAU7802_GAIN_32:  Serial.println("32x"); break;
    case NAU7802_GAIN_64:  Serial.println("64x"); break;
    case NAU7802_GAIN_128:  Serial.println("128x"); break;
  }

  nau.setRate(NAU7802_RATE_10SPS);
  Serial.print("Conversion rate set to ");
  switch (nau.getRate()) {
    case NAU7802_RATE_10SPS:  Serial.println("10 SPS"); break;
    case NAU7802_RATE_20SPS:  Serial.println("20 SPS"); break;
    case NAU7802_RATE_40SPS:  Serial.println("40 SPS"); break;
    case NAU7802_RATE_80SPS:  Serial.println("80 SPS"); break;
    case NAU7802_RATE_320SPS:  Serial.println("320 SPS"); break;
  }

  // Take 10 readings to flush out readings
  for (uint8_t i=0; i<10; i++) {
    while (! nau.available()) delay(1);
    nau.read();
  }

  while (! nau.calibrate(NAU7802_CALMOD_INTERNAL)) {
    Serial.println("Failed to calibrate internal offset, retrying!");
    delay(1000);
  }
  Serial.println("Calibrated internal offset");

  while (! nau.calibrate(NAU7802_CALMOD_OFFSET)) {
    Serial.println("Failed to calibrate system offset, retrying!");
    delay(1000);
  }
  Serial.println("Calibrated system offset");
  Serial.println();

  Serial.println("Make sure nothing is on the scale");
  Serial.println();

  delay(3000);
  
  while (! nau.available()) {
    delay(1);
  }
  int32_t val = nau.read();
  for(int j = 0; j < 10; j++){
    compZero += val;
    val = nau.read();
  }
  compZero = compZero/10;

  while(!nau.available()){
    delay(1);
  }

  Serial.println("Now place the weight on the scale"); 
  Serial.println("Enter the number 1 when ready");

  while(proceed == 0){
    proceed = Serial.parseFloat();
  }

  proceed = 0;


  Serial.print("Now input the known weight in grams: "); 
    while(given == 0){

    given = Serial.parseFloat();

  }
  Serial.println(given);

  int32_t val2 = nau.read();
  //double doubleVal = 0;
  
  for(int m = 0; m < 20; m++){
    avgGiven = avgGiven + val2;
    val2 = nau.read();
  }
  avgGiven = (avgGiven/20);

  slope = (avgGiven-compZero)/given;

  Serial.println("Now place a new weight on the scale"); 
  Serial.println("Enter the number 1 when ready");

  while(proceed == 0){

    proceed = Serial.parseFloat();

 

  }
  proceed = 0;
  

}

void loop() {


  while (! nau.available()) {
    delay(1);
  }
  int32_t val3 = nau.read();
  i++;
  compRead+= val3;
  if(val3 > max){
    max = val3;
  }
  if(i == 20){
    compRead = compRead/20;
    yAvg = (compRead/slope) - zero;
    yMax = (max/slope) - zero;
    Serial.print("The average grams of weight on the scale is: "); Serial.println(yAvg);
    Serial.print("The maximum grams of weight on the scale is: "); Serial.println(yMax);
    Serial.print("The average force of the weight  on the scale is: "); Serial.println((yAvg/1000)*9.81);

    Serial.print("The maximum force of the weight  on the scale is: "); Serial.println((yMax/1000)*9.81);
    Serial.println("Put a new weight on the scale");
    i = 0;
    compRead = 0;
    max = 0;
    Serial.println();
    Serial.println("Now place a new weight on the scale"); 
    Serial.println("Enter the number 1 when ready");

    while(proceed == 0){
      proceed = Serial.parseFloat();
    }
    proceed = 0;
  }

}
