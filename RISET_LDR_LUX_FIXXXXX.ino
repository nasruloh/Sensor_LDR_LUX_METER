//nasruloh0@gmail.com
#define LDR A0                               //LDR pada pin A0
#define MAX_ADC_READING 1023
#define ADC_REF_VOLTAGE 5.0
#define REF_RESISTANCE 10000
#define LUX_CALC_SCALAR 125235178.3654270
#define LUX_CALC_EXPONENT -1.604568157

float MAX_V = 4.89;                         // nilai minimal sensor

void setup() {
  Serial.begin(9600);   //Mulai komunikasi serial
  pinMode(LDR,INPUT);
}

void loop() {
  int ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;
  
//  /* treshold get max */
//  float treshold_V = (ADC_REF_VOLTAGE-MAX_V)/ MAX_V * REF_RESISTANCE;
//  float treshold_value = LUX_CALC_SCALAR * pow(treshold_V, LUX_CALC_EXPONENT)*1000;

 
  ldrRawData = analogRead(LDR);   //Baca sensor
  ldrRawData = MAX_ADC_READING - ldrRawData;
  //------------Konversi  dari data analog ke nilai lux------------//
  resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
  if(resistorVoltage<0.001) resistorVoltage=0;
  Serial.print("resistorVoltage : ");
  Serial.println(resistorVoltage);
  
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
  ldrResistance = ldrVoltage / resistorVoltage * REF_RESISTANCE;
  ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT)*1000;
  
   
  /* reverse */
//  ldrLux = treshold_value -ldrLux;
  
  Serial.print("Intensitas Cahaya : ");
  Serial.print(ldrLux);                     //Tampilkan intensitas cahaya
  Serial.println(" Lux");
//  Serial.print("\t tresh : ");
//  Serial.println (treshold_value);
  delay(1000);
}
