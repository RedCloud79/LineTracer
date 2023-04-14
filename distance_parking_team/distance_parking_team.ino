/*
millis를 이용하여 일정 시간 라인트레이서 센서 값을 받아 주행을 한 후에
일정 시간이 끝나게 되면 초음파 센서 값을 받아 후진을 하고 일정 거리가
되었으면 멈추는 코드 입니다.
*/

// 모터 핀 번호
const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;

// 초음파 센서 핀 번호
const int trigPin = 3;
const int echoPin = 11;

// 부저 핀 번호
const int buzzer = 7;

// 라인트레이서 센서 핀 번호
const int IR_R = A1;
const int IR_M = A3;
const int IR_L = A5;

// 라인트레이서 센서 데이터
int IR_L_data;
int IR_M_data;
int IR_R_data;

// millis 변수 설정
unsigned long Timer_move = millis();

// 초음파 센서 거리 변수
float duration, distance;

void setup() {
  // 모터
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  
  // 초음파 센서
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // 부저
  pinMode(buzzer, OUTPUT);
  
  // 라인트레이서
  pinMode(IR_L, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_R, INPUT);
}


void loop() {
  // 라인트레이서 센서 값 
  IR_L_data = digitalRead(IR_L);
  IR_M_data = digitalRead(IR_M);
  IR_R_data = digitalRead(IR_R);

  if (Timer_move + 7500 > millis()){
    if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
      // 전진
      forward();
    }
    else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
      // 좌회전
      left ();
    }
    else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
      // 우회전
      right ();
    }
    else if (IR_L_data == 1 and IR_M_data == 1  and IR_R_data == 1) {
      // 정지
      stop();
    }
  }else if(Timer_move + 7500 < millis()){
    // backward();
    stop();
    delay(10);
    // delay(50000);
    // backward();
    // delay(50);

    // 초음파 센서 값
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    delay(50);

    // 거리별 부저 및 후진
    if (distance > 70 && distance <= 150) {
    backward();
    // delay(1500);
    // delay(750);
    // delay(500);
    delay(50);
    // tone(buzzer, 740, 1000/8);
    // delay(1000 / 8*1.30);
    // noTone(buzzer);
    }
    // else if (distance > 10 && distance <= 30) {
    //   backward();
    //   // backward_60();
    //   delay(5);
    //   tone(buzzer, 740, 1000/8);
    //   delay(1000 / 16*1.30);
    //   noTone(buzzer);
    
    // }
    // else if (distance > 40 && distance <= 50) {
    //   backward();
    //   // backward_50();
    //   delay(100);
    //   tone(buzzer, 880, 1000 / 8);
    //   delay(1000 / 8*1.30);
    //   noTone(buzzer);
    // }
    // else if (distance > 30 && distance <= 40) {
    //   backward();
    //   // backward_40();
    //   delay(100);
    //   tone(buzzer, 1109, 1000 / 8);
    //   delay(1000 / 16*1.30);
    //   noTone(buzzer);
    // }
    // else if (distance > 20 && distance <= 30) {
    //   backward();
    //   // backward_30();
    //   delay(100);
    //   tone(buzzer, 1568, 1000/8);
    //   delay(1000 / 32*1.30);
    //   noTone(buzzer);
    // }
    else if (distance > 25 && distance <= 70) {
      // backward();
      backward_20();
      delay(50);
      tone(buzzer, 1568, 1000 / 8);
      delay(1000 / 16 * 1.30);
      noTone(buzzer);
    }
    else if (distance <= 25) {
      tone(buzzer, 1760, 1000/ 8);
      stop();
    }

    Timer_move = 0;
  }

}


void right () {
  //우
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}
void rightback () {
  //우로 후진
  digitalWrite(motor_A1, LOW);
  analogWrite(motor_A2, 100);
  analogWrite(motor_B1, 100);
  digitalWrite(motor_B2, LOW);
}
void left() {
  //좌
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
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
  analogWrite(motor_A2, 255);
  digitalWrite(motor_B1, LOW);
  analogWrite(motor_B2, 255);
}

void stop() {
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
  analogWrite(motor_A2, 150);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  analogWrite(motor_B1, 0);
  analogWrite(motor_B2, 150);
}