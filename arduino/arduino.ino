#define OPEN_BUTTON  7
#define CLOSE_BUTTON 8

#define MOTOR_OUT1   9
#define MOTOR_OUT2   10

#define STATUS_IDLE    0
#define STATUS_OPENING 1
#define STATUS_CLOSING 2

// Duration to spin the motor for closing / opening the gate
#define ACTION_DURATION 15000

int status = STATUS_IDLE;
long actionTime = 0;

void setup(){
  Serial.begin(115200);

  // Setup manual button input
  pinMode(OPEN_BUTTON, INPUT);
  pinMode(CLOSE_BUTTON, INPUT);
  digitalWrite(OPEN_BUTTON, HIGH);
  digitalWrite(CLOSE_BUTTON, HIGH);

  // Setup motor controller connection
  pinMode(MOTOR_OUT1, OUTPUT);
  pinMode(MOTOR_OUT2, OUTPUT);
  digitalWrite(MOTOR_OUT1, LOW);
  digitalWrite(MOTOR_OUT2, LOW);
}

void doOpen() {
  digitalWrite(MOTOR_OUT1, HIGH);
  digitalWrite(MOTOR_OUT2, LOW);
}

void doClose() {
  digitalWrite(MOTOR_OUT1, LOW);
  digitalWrite(MOTOR_OUT2, HIGH);
}

void idle() {
  digitalWrite(MOTOR_OUT1, LOW);
  digitalWrite(MOTOR_OUT2, LOW);
}

void loop(){
  long now = millis();
  // Check if TPLink has send us some command
  if(Serial.available() > 0) {
    char ch = Serial.read();
    if(ch == 'o') status = STATUS_OPENING;
    if(ch == 'c') status = STATUS_CLOSING;
    actionTime = now;
  }
  // Do action based on status or button press
  if(status == STATUS_OPENING || digitalRead(OPEN_BUTTON)) doOpen();
  if(status == STATUS_CLOSING || digitalRead(CLOSE_BUTTON)) doClose();
  if(status == STATUS_IDLE) idle();

  if(now - actionTime > ACTION_DURATION) status = STATUS_IDLE;
}
