
const int pingPin = 4;
const int ledPin = 7;
const int buttonPin = 5;
int buttonVal = 0;
boolean driving = false;
const long maxDistance = 15;
const int forwardSpeed = 220;
const int reverseSpeed = 180;
const int turnSpeed = 150;

void setup() {
  pinMode(ledPin, OUTPUT);    
  pinMode(buttonPin, INPUT);   
  
  //motor pins
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT); //Initiates Brake Channel B pin
}

void loop()
{
  buttonVal = digitalRead(buttonPin);
  if (buttonVal != 0)
  {
    runRobot();
  }
  delay(100);
}

void runRobot(){
  long distance = getDistance();
  
  if (distance < maxDistance)
  {
    digitalWrite(ledPin, HIGH);
    if(driving == true)
    {
      driving = false;
      driveReverse();
    }    
  }
  else
  {
    digitalWrite(ledPin, LOW);
    if(driving == false)
    {
      driving = true;
      driveForward();
    } 
  }
}

void driveForward(){
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, forwardSpeed);   //Spins the motor on Channel A at full speed  
  
  digitalWrite(13, LOW); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, forwardSpeed);   //Spins the motor on Channel B at full speed  
}

void driveReverse(){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  delay(500);
  
  digitalWrite(12, HIGH); //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, reverseSpeed);   //Spins the motor on Channel A at half speed
  
  digitalWrite(13, HIGH); //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, reverseSpeed);   //Spins the motor on Channel B at half speed
  
  delay(2000);  
  
  turn();
}

void turn()
{
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  delay(500);
  
  digitalWrite(12, LOW); //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, turnSpeed);   //Spins the motor on Channel A at half speed
  
  digitalWrite(13, HIGH); //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, turnSpeed);   //Spins the motor on Channel B at half speed
  
  delay(2000);
}

long getDistance(){
  long duration, cm;

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  return cm;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
