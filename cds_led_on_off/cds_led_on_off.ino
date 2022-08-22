int ledPin = 23;
int cds = A0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
void loop() {
  
  int cdsvalue = analogRead(cds);
  Serial.println(cdsvalue);
   
  if(cdsvalue>1000){
    digitalWrite(ledPin,HIGH );
    
  }
  else{
  digitalWrite(ledPin, LOW);
 
  }
  delay(500);                  
}
