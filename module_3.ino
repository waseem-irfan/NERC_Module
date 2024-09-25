#include <Servo.h>

//Motor pins
const int A = 2;  //right backward
const int B = 3;  //right forward
const int C = 4;  //left backward
const int D = 5;  //left forward

//Line following sensor pins
const int left_foll = 24;
const int right_foll = 26;

//junction sensor pins
const int left_junc = 28;
const int right_junc = 30;

//servo
const int servo_pwm = 13;
int servo_delay = 700;
const int maxspeed = 700;
const int stope = 1500;
Servo servo;

int junction_no = 0;  //declare the starting junction

int move_back_drop = 530;              // delay for move back when placing rock or tree
int move_back_after_Pick_Place = 740;  //delay for backward after place

bool parking = false;  // for last stop in the arena

//int backing = 300;
//int stall = 500;
//int thoraAgay = 200;

void setup() {
  // put your setup code here, to run once:
  servo.attach(9);  // attach servo

  //set motors as output
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  //set sensors as input
  pinMode(left_foll, INPUT);
  pinMode(right_foll, INPUT);
  pinMode(left_junc, INPUT);
  pinMode(right_junc, INPUT);
  pinMode(servo_pwm, OUTPUT);

  Serial.begin(9600);

  delay(1000);  // starting delay
                // halfrev(1200);

  //main loop
  while (!parking) {
    follower();
    if (digitalRead(left_junc) == HIGH && digitalRead(right_junc) == HIGH) {
      junction();
    }
  }
}


void loop() {
  /*Serial.println("left junc:");
    Serial.println(digitalRead(left_foll));
    Serial.println("right junc:");
    Serial.println(digitalRead(right_foll));
    delay(1000);*/
}


void follower() {
  if (digitalRead(left_foll) == HIGH && digitalRead(right_foll) == LOW) {
    left();
  } else if (digitalRead(left_foll) == LOW && digitalRead(right_foll) == HIGH) {
    right();
  } else if (digitalRead(left_junc) == HIGH && digitalRead(right_junc) == LOW) {
    extLeft();
  } else if (digitalRead(left_junc) == LOW && digitalRead(right_junc) == HIGH) {
    extRight();
  } else {
    moveForward();
  }
}

void backFollower() {
  if (digitalRead(left_foll) == HIGH && digitalRead(right_foll) == LOW) {
    B_right();
  } else if (digitalRead(left_foll) == LOW && digitalRead(right_foll) == HIGH) {
    B_left();
  } else if (digitalRead(left_junc) == HIGH && digitalRead(right_junc) == LOW) {
    B_extRight();
  } else if (digitalRead(left_junc) == LOW && digitalRead(right_junc) == HIGH) {
    B_extLeft();
  } else {
    moveBackward();
  }
}


void junction() {
  junction_no++;
  //Serial.println(junction_no);

  switch (junction_no) {
    case 4:
      stop(500);
      right90();
      break;
    case 6:
      stop(500);
      right90();
      break;
    case 10:
      stop(500);
      left90();
      break;
    case 11:
      stop(500);
      left90();
      break;
    case 14:  //1st rock lifting
      stop(500);
      lift();
      delay(3000);
      break;
    case 15:
      stop(500);
      right90();
      break;
    case 19:  //1st rock placing
      stop(500);
      moveBackward(move_back_drop);
      stop(500);
      drop();
      delay(3000);
      moveBackward(move_back_after_Pick_Place);
      stop(500);
      halfrev(1115);
      break;
    case 21:
      stop(500);
      left90();
      break;
    case 22:
      stop(500);
      left90();
      break;
    case 25:  //1st tree lifting
      stop(500);
      lift();
      delay(3000);
      stop(500);
      moveBackward(move_back_drop);
      moveBackward(50);
      moveBackward(move_back_after_Pick_Place);
      stop(500);
      halfrev(1170);
      stop(500);
      moveForward(100);
      break;
    case 28:  //1st tree placing
      stop(500);
      moveBackward(move_back_drop);
      stop(500);
      drop();
      delay(3000);
      moveBackward(move_back_after_Pick_Place);
      stop(500);
      // moveForward(100);
      // stop(500);
      halfrev(1320);
      break;
    case 30:
      stop(500);
      right90();
      break;
    case 31:
      stop(500);
      moveForward(100);
      stop(500);
      right90(600);
      stop(500);
      moveBackward(300);
      break;
    case 33:  //2nd rock lifting
      stop(500);
      lift();
      delay(3000);
      // moveForward(100);
      stop(500);
      right90();
      break;
    case 34:
      stop(500);
      right90();
      break;
    case 37:  //2nd rock placing
      stop(500);
      moveBackward(move_back_drop);
      stop(500);
      drop();
      delay(3000);
      moveBackward(move_back_after_Pick_Place);
      stop(500);
      // moveForward(100);
      // stop(500);
      halfrev(1150);
      break;
    case 39:
      stop(500);
      left90();
      break;
    case 40:
      stop(500);
      left90();
      break;
    case 43:  //2nd tree lifting
      stop(500);
      lift();
      stop(3000);
      // moveBackward(100);
      // delay(3000);
      break;
    case 44:
      stop(500);
      moveForward(50);
      stop(500);
      halfrev(1118);
      break;
    case 48:  //2nd tree placing
      stop(500);
      moveBackward(move_back_drop);
      stop(500);
      drop();
      delay(3000);
      moveBackward(move_back_after_Pick_Place);
      stop(500);
      moveForward(100);
      stop(500);
      halfrev(1150);
      break;
    case 49:
      stop(500);
      right90();
      break;
    case 51:
      stop(500);
      right90();
      break;
    case 55:
      stop(500);
      right90();
      break;
    case 56:
      stop(500);
      right90();
      break;
    case 59:  //3rd rock lifting
      stop(500);
      lift();
      delay(3000);
      left90();
      break;
    case 60:
      stop(500);
      right90();
      break;
    case 62:  //3rd rock placing
      stop(500);
      moveBackward(move_back_drop);
      stop(500);
      drop();
      delay(3000);
      moveBackward(move_back_after_Pick_Place);
      stop(500);
      moveForward(100);
      stop(500);
      halfrev();
      break;
    case 63:
      stop(500);
      left90();
      break;
    case 65:
      stop(500);
      right90();
      break;
    case 67:
      stop(500);
      right90();
      break;
    case 68:
      stop(500);
      right90();
      break;
    case 72:  //3rd tree lifting
      stop(500);
      lift();
      delay(3000);
      right90();
      break;
    case 73:
      stop(500);
      right90();
      break;
    case 77:
      stop(500);
      right90();
      break;
    case 78:
      stop(500);
      right90();
      break;
    case 80:  //3rd tree placing
      stop(500);
      moveBackward(move_back_drop);
      stop(500);
      drop();
      delay(3000);
      moveBackward(move_back_after_Pick_Place);
      stop(500);
      moveForward(100);
      stop(500);
      halfrev();
      break;
    case 81:
      stop(500);
      left90();
      break;
    case 82:
      stop(500);
      left90();
      break;
    case 85:
      stop(500);
      left90();
      break;
    case 90:  //Parking
      moveForward(500);
      parking = true;
      break;
    default:
      moveForward(100);
      break;
  }
}


void moveForward(int a) {
  analogWrite(A, 0);
  analogWrite(B, 70);
  analogWrite(C, 0);
  analogWrite(D, 85);
  delay(a);
}


void moveForward() {
  analogWrite(A, 0);
  analogWrite(B, 70);
  analogWrite(C, 0);
  analogWrite(D, 85);
}


void moveBackward() {
  analogWrite(A, 70);
  analogWrite(B, 0);
  analogWrite(C, 85);
  analogWrite(D, 0);
}


void moveBackward(int a) {
  analogWrite(A, 70);
  analogWrite(B, 0);
  analogWrite(C, 85);
  analogWrite(D, 0);
  delay(a);
}


void stop(int a) {
  analogWrite(A, 0);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 0);
  delay(a);
}


void stop() {
  analogWrite(A, 0);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 0);
}


void left() {
  analogWrite(A, 0);
  analogWrite(B, 92);
  analogWrite(C, 0);
  analogWrite(D, 52);
}

void B_left() {
  analogWrite(A, 88);
  analogWrite(B, 0);
  analogWrite(C, 50);
  analogWrite(D, 0);
}


void extLeft() {
  analogWrite(A, 0);
  analogWrite(B, 210);
  analogWrite(C, 0);
  analogWrite(D, 50);
}


void B_extLeft() {
  analogWrite(A, 200);
  analogWrite(B, 0);
  analogWrite(C, 50);
  analogWrite(D, 200);
}


void right() {
  analogWrite(A, 0);
  analogWrite(B, 50);
  analogWrite(C, 0);
  analogWrite(D, 93);
}


void B_right() {
  analogWrite(A, 50);
  analogWrite(B, 0);
  analogWrite(C, 93);
  analogWrite(D, 0);
}


void extRight() {
  analogWrite(A, 0);
  analogWrite(B, 50);
  analogWrite(C, 0);
  analogWrite(D, 220);
}


void B_extRight() {
  analogWrite(A, 50);
  analogWrite(B, 0);
  analogWrite(C, 210);
  analogWrite(D, 0);
}


void right90() {
  moveBackward(70);
  analogWrite(A, 75);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 92);
  delay(600);
  while (digitalRead(right_foll) == LOW) {
    analogWrite(A, 75);
    analogWrite(B, 0);
    analogWrite(C, 0);
    analogWrite(D, 92);
  }
  stop(500);
}


void right90_withJunc() {
  moveBackward(70);
  analogWrite(A, 75);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 92);
  delay(600);
  while (digitalRead(right_junc) == LOW) {
    analogWrite(A, 75);
    analogWrite(B, 0);
    analogWrite(C, 0);
    analogWrite(D, 92);
  }
  stop(500);
}


void left90() {
  //moveBackward(120);
  moveForward(65);
  analogWrite(A, 0);
  analogWrite(B, 90);
  analogWrite(C, 100);
  analogWrite(D, 0);
  delay(600);
  while (digitalRead(left_foll) == LOW) {
    analogWrite(A, 0);
    analogWrite(B, 90);
    analogWrite(C, 100);
    analogWrite(D, 0);
  }
  stop(500);
}


void right90(int a) {
  //moveBackward(120);
  analogWrite(A, 75);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 85);
  delay(a);
  stop(500);
}


void left90(int a) {
  //moveBackward(120);
  analogWrite(A, 0);
  analogWrite(B, 80);
  analogWrite(C, 90);
  analogWrite(D, 0);
  delay(400);
  while (digitalRead(left_foll) == LOW) {
    analogWrite(A, 0);
    analogWrite(B, 80);
    analogWrite(C, 90);
    analogWrite(D, 0);
  }
  stop(500);
  delay(a);
}


void halfrev() {
  stop(500);
  analogWrite(A, 80);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 90);
  delay(1200);
  while (!(digitalRead(right_foll) == HIGH)) {
    analogWrite(A, 80);
    analogWrite(B, 0);
    analogWrite(C, 0);
    analogWrite(D, 90);
  }
  // analogWrite(A, 0);
  // analogWrite(B, 80);
  // analogWrite(C, 101);
  // analogWrite(D, 0);
  // delay(80);
  stop(1000);
}


void halfrev_withJunc() {
  stop(500);
  analogWrite(A, 80);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 90);
  delay(1200);
  while (!(digitalRead(right_junc) == HIGH)) {
    analogWrite(A, 80);
    analogWrite(B, 0);
    analogWrite(C, 0);
    analogWrite(D, 90);
  }
  // analogWrite(A, 0);
  // analogWrite(B, 80);
  // analogWrite(C, 101);
  // analogWrite(D, 0);
  // delay(80);
  stop(1000);
}


void halfrev_withLeftFoll() {
  stop(500);
  analogWrite(A, 80);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 90);
  delay(1200);
  while (!(digitalRead(left_foll) == HIGH)) {
    analogWrite(A, 80);
    analogWrite(B, 0);
    analogWrite(C, 0);
    analogWrite(D, 90);
  }
  // analogWrite(A, 0);
  // analogWrite(B, 80);
  // analogWrite(C, 101);
  // analogWrite(D, 0);
  // delay(80);
  stop(1000);
}


void halfrev(int a) {
  stop(500);
  analogWrite(A, 80);
  analogWrite(B, 0);
  analogWrite(C, 0);
  analogWrite(D, 90);
  delay(a);
  stop(1000);
}



void lift() {
  //  if (!(digitalRead(left_foll) == HIGH && digitalRead(right_foll) == HIGH))
  {
    servo.attach(servo_pwm);
    rotate(0, 1000);
    rotate(-50, servo_delay);
    servo.detach();
  }
}


void drop() {
  //  if (!(digitalRead(left_foll) == HIGH && digitalRead(right_foll) == HIGH))
  {
    servo.attach(servo_pwm);
    rotate(0, 1000);
    rotate(+50, servo_delay);
    servo.detach();
  }
}


void rotate(int speed, int wait) {
  speed = map(speed, -100, +100, stope - maxspeed, stope + maxspeed);
  servo.writeMicroseconds(speed);
  delay(wait);
}