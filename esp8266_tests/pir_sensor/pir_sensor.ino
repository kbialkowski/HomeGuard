/////
//HC-SR501 pir sensor
////

int pirPin = 5;    //PIR pin
int ledPin = 13;   //led pin
int prevState = LOW;
int state = LOW;
int i = 0;

/////////////////////////////
//SETUP 
void setup(){ 
  Serial.begin(9600); 
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.println("Waiting for module to settle...");  
  state = digitalRead(pirPin);  

  //Loop util state is LOW
  while(state==HIGH){
    state = digitalRead(pirPin);    
    Serial.print(i);
    Serial.print(" state:" );
    Serial.print(state);
    Serial.println("");
    delay(1000);
    i++;
  }

  Serial.println("Ready !!!");  
}

////////////////////////////
void loop(){
  
  state = digitalRead(pirPin);

  if(state==HIGH and prevState==LOW){
    Serial.println("Move detected !!!");  
    prevState=HIGH;
    digitalWrite(ledPin,state);
    i=0;
  }

  if(state==LOW and prevState==HIGH){
    Serial.println("Waiting...");
    prevState=LOW;    
    digitalWrite(ledPin,state);
    i=0;
  }   
  Serial.println(i);
  i++;
  delay(1000);
}
