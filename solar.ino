//How Servo Motor works: https://docs.idew.org/internet-of-things-project/references-for-wiring-and-coding/continuous-rotation-servo-motor
#include <Servo.h>
Servo up_down_servo;
Servo left_right_servo;

int ldr1 = A0;
int ldr2 = A1;
int ldr3 = A2;
int ldr4 = A3;
int up_down_servo_pin = 9;
int left_right_servo_pin = 10;

//This is based on values stated in the research paper
int initial_up_down_position = 180;
int initial_left_right_position = 180;

const int CLOCKWISE_FULL_SPEED = 180;
const int COUNTER_CLOCKWISE_FULL_SPEED = 0;
const int ARBITRARY_SPEED = 60;

const int STOP_MOTOR = 90;

const int MOTOR_MOVEMENT_TIME = 1000;

void move_up();
void move_down();
void move_right();
void move_left();

void setup() {

  Serial.begin(9600);
  up_down_servo.attach(up_down_servo_pin);
  left_right_servo.attach(left_right_servo_pin);
}

void loop(){

//  testMotors();  
  automatic_solar_tracker();
//  moto_goto_position();    
}

void automatic_solar_tracker(){
  
  
 int ldr1_value = analogRead(ldr1);
 int ldr2_value = analogRead(ldr2);
 int ldr3_value = analogRead(ldr3);
 int ldr4_value = analogRead(ldr4);

 int averageTop=(ldr1_value+ldr2_value)/2;
 int averageBottom=(ldr3_value+ldr4_value)/2;
 int averageLeft=(ldr1_value+ldr3_value)/2;
 int averageRight=(ldr2_value+ldr4_value)/2;


  if (averageTop > averageBottom ){
     String light_data = "Zenith: " + String(averageTop) + " " + String(averageBottom);
     Serial.println(light_data);
     move_up();
  }
  else if (averageTop < averageBottom ){
    String light_data = "Zenith: " + String(averageTop) + " " + String(averageBottom);
    Serial.println(light_data);
    move_down();
  }
  
  if(averageLeft > averageRight) {
    String light_data = "Azimuthal: " + String(averageLeft) + " " + String(averageRight);
    Serial.println(light_data);
    move_left();
  }
  else ifM (averageLeft < averageRight){
    String light_data = "Azimuthal: " + String(averageLeft) + " " + String(averageRight);
    Serial.println(light_data);
    move_right();
  }
 delay(MOTOR_MOVEMENT_TIME); 
}

void move_up(){ 
  int motor_position= up_down_servo.read();  
  motor_position += 30;
  up_down_servo.write(motor_position);
  delay(MOTOR_MOVEMENT_TIME);
}

void move_down(){  
  int motor_position= up_down_servo.read();  
  motor_position -= 30;
  up_down_servo.write(motor_position);
  delay(MOTOR_MOVEMENT_TIME);
}

void move_right(){
  int motor_position = left_right_servo.read();
  motor_position += 30;
  left_right_servo.write(motor_position);
  delay(MOTOR_MOVEMENT_TIME);
}

void move_left(){
  int motor_position = left_right_servo.read();
  motor_position -= 30;
  left_right_servo.write(motor_position);
  delay(MOTOR_MOVEMENT_TIME);
}

void testMotors(){
  for(int p=0; p<=180; p++){
    up_down_servo.write(p);
    left_right_servo.write(p);
    delay(15);
  }

 for(int p=180; p>=0; p--){
    up_down_servo.write(p);
    left_right_servo.write(p);
    delay(15);
   }
}

//Look before touch obfuscated!!!
void moto_goto_position(){
     up_down_servo.write(ARBITRARY_SPEED);
//     left_right_servo.write(CLOCKWISE_FULL_SPEED);
     delay(300000);

     up_down_servo.write(STOP_MOTOR);
//     left_right_servo.write(STOP_MOTOR);
     delay(1000);

     up_down_servo.write(COUNTER_CLOCKWISE_FULL_SPEED);
//     left_right_servo.write(COUNTER_CLOCKWISE_FULL_SPEED);
     delay(1000);

     up_down_servo.write(STOP_MOTOR);
//     left_right_servo.write(STOP_MOTOR);
     delay(2000);
}

