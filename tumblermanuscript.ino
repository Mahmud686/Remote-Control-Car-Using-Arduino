char t;

const int ftrigPin = 8;
const int fechoPin = 9;
const int trigPin = 6;
const int echoPin = 7;

int ledL = 2;
int ledR = 4;

int enA = 5;
int enB = 3;

long duration;
int distance;

long fduration;
int fdistance;



void setup() {
  pinMode(13, OUTPUT);  //left motors forward
  pinMode(12, OUTPUT);  //left motors reverse
  pinMode(11, OUTPUT);  //right motors forward
  pinMode(10, OUTPUT);  //right motors reverse
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(ledL, OUTPUT);
  pinMode(ledR, OUTPUT);

  //pinMode(9, OUTPUT);  //Led

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ftrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(fechoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600);
  Serial.setTimeout(10);

}


void fsonar()
{
  digitalWrite(ftrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(ftrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ftrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  fduration = pulseIn(fechoPin, HIGH);
  // Calculating the distance
  fdistance = fduration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("FDistance: ");
  Serial.println(fdistance);
  
}
void sonar()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
}

void stop()
{
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
}

void loop() {

  sonar();
  fsonar();

  analogWrite(enA, 100);
  analogWrite(enB, 100);
  
  if (Serial.available()) {
    t = Serial.read();
    Serial.println(t);
  }
  //if((t == 'F' || t == 'B')&&  (distance<30 ||  fdistance<30)) stop();
  if(t == 'F' && fdistance<30) stop();
  else if(t == 'B' && distance<30) stop();
  
  else if (t == 'F' && fdistance>=30) {          //move forward(all motors rotate in forward direction)
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(ledL, LOW);
    digitalWrite(ledR, LOW);
    analogWrite(enA, 100);
    analogWrite(enB, 100);
  }

  else if (t == 'B' && distance>=30) {    //move reverse (all motors rotate in reverse direction)
    digitalWrite(12, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(ledL, LOW);
    digitalWrite(ledR, LOW);
    analogWrite(enA, 100);
    analogWrite(enB, 100);
  }

  else if (t == 'L') {    //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
    digitalWrite(11, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(ledL, HIGH);
    digitalWrite(ledR, LOW);
    analogWrite(enA, 85);
    analogWrite(enB, 85);
    
  }

  else if (t == 'R') {    //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
    digitalWrite(13, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(ledR, HIGH);
    digitalWrite(ledL, LOW);
    analogWrite(enA, 85);
    analogWrite(enB, 85);

  }

  else if (t == 'W') {  //turn led on or off)
    digitalWrite(9, HIGH);
  }
  else if (t == 'w') {
    digitalWrite(9, LOW);
  }

  else if (t == 'S') {    //STOP (all motors stop)
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(ledL, LOW);
    digitalWrite(ledR, LOW);
  }
  //delay(100);
}
