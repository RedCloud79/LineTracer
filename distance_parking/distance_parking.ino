// 모터 핀 번호
const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;

// 부저
const int buzzer = 7;

// 초음파 센서 핀 번호
const int trigPin = 3;
const int echoPin = 11;

// 라인트레이서 핀 번호
const int IR_R = A1;
const int IR_M = A3;
const int IR_L = A5;

// 라인트레이서 데이터
int IR_L_data;
int IR_M_data;
int IR_R_data;
// 초음파 센서 거리

float duration, distance;


void setup() {
  // 모터 출력
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);

  // 부저 출력
  pinMode(buzzer, OUTPUT);

  // 초음파 입출력
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // 라인트레이서 입력
  pinMode(IR_L, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_R, INPUT);
  //Serial.begin(9600);
  }


void loop() {

  // 라인트레이서 값
  IR_L_data = digitalRead(IR_L);
  IR_M_data = digitalRead(IR_M);
  IR_R_data = digitalRead(IR_R);

  // 초음파 센서 값
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 거리
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  //Serial.print("Distance: ");
  //Serial.println(distance);
  delay(100);


  // 직진 및 유턴
  if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    //Serial.println(" 직진 ");
    forward();
    delay(15);
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    //Serial.println(" 좌회전 ");
    left ();
    delay(15);
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    //Serial.println(" 우회전 ");
    right ();
    delay(15);
  }
  else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
    //Serial.println(" 정지 ");
    stop();
    delay(15);
  }
  else if (IR_L_data == 1 and IR_M_data == 1 and IR_R_data == 0) {
    //Serial.println(" 유턴 ");
    turn();
    delay(15);
  }
  else if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 1) {
    //Serial.println(" 유턴 ");
    turn();
    delay(15);
  }

  // 초음파 거리별 경보 및 주차
  if (distance > 60 && distance <= 70) {
    backward();
    delay(15);
    tone(buzzer, 523, 1000/8);
    delay(1000 / 2*1.30);
    noTone(buzzer);
  }
  else if (distance > 50 && distance <= 60) {
    backward_60();
    delay(15);
    tone(buzzer, 740, 1000/8);
    delay(1000 / 4*1.30);
    noTone(buzzer);
   
  }
  else if (distance > 40 && distance <= 50) {
    backward_50();
    delay(15);
    tone(buzzer, 1109, 1000 / 8);
    delay(1000 / 8*1.30);
    noTone(buzzer);
  }
  else if (distance > 20 && distance <= 30) {
    backward_40();
    delay(15);
    tone(buzzer, 1109, 1000 / 8);
    delay(1000 / 8*1.30);
    noTone(buzzer);
  }
  else if (distance > 10 && distance <= 20) {
    backward_20();
    delay(15);
    tone(buzzer, 1568, 1000/8);
    delay(1000 / 16*1.30);
    noTone(buzzer);
  }
  else if (distance <= 10) {
    stop();
  }
}

// 함수
void right () {
  //우
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  analogWrite(motor_B2, 150);
}

void rightback () {
  //우로 후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void left() {
  //좌
  digitalWrite(motor_A1, LOW);
  analogWrite(motor_A2, 150);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}
void leftback() {
  //좌로 후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
}

void forward() {
  //전진
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void backward() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
}

void turn(){
  //유턴
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void stop() {
  //정지
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

void backward_70() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  analogWrite(motor_A1, 0);
  analogWrite(motor_A2, 150);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  analogWrite(motor_B1, 0);
  analogWrite(motor_B2, 150);
}

void backward_60() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  analogWrite(motor_A1, 0);
  analogWrite(motor_A2, 150);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  analogWrite(motor_B1, 0);
  analogWrite(motor_B2, 150);
}

void backward_50() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  analogWrite(motor_A1, 0);
  analogWrite(motor_A2, 130);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  analogWrite(motor_B1, 0);
  analogWrite(motor_B2, 130);
}
void backward_40() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  analogWrite(motor_A1, 0);
  analogWrite(motor_A2, 100);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  analogWrite(motor_B1, 0);
  analogWrite(motor_B2, 100);
}

void backward_30() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  analogWrite(motor_A1, 0);
  analogWrite(motor_A2, 80);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  analogWrite(motor_B1, 0);
  analogWrite(motor_B2, 80);
}

void backward_20() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  analogWrite(motor_A1, 0);
  analogWrite(motor_A2, 60);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  analogWrite(motor_B1, 0);
  analogWrite(motor_B2, 60);
}