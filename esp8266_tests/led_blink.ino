int outPin = 12; //on board D7

void setup() {

  pinMode(outPin,OUTPUT);
  Serial.begin(115200);  
  Serial.println("Start...");
  delay(2000);
}

void loop() { 
   
  digitalWrite(outPin,HIGH);//state high to output pin
  Serial.println("HIGH"); //just a comment
  delay(1000); //some delay to see light
  digitalWrite(outPin,LOW);;//state low to output pin
  Serial.println("LOW");  
  delay(1000);
  
}
