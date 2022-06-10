//Servo motor library
#include <Servo.h>
Servo zenith_servo;
Servo azimuthal_servo;

int ldr1= A0;                  // top-right LDR input pin                       
int ldr2 = A1;                // top-left LDR input pin                     
int ldr3 = A2;               // bottom-right LDR input pin              
int ldr4 = A3;              // bottom-left LDR input pin   

//servos
int zenith_servo_pin = 10;
int azimuthal_servo_pin = 9;

//Variables to store the light intensities
int ldr1_getter,ldr2_getter, ldr3_getter, ldr4_getter;  
int sum_of_avg_ldr_values;
int zenith_difference;                  // |avg_top_ldr_value - avg_bottom_ldr_value|
const int rotation_threshold = 10;      //Threshold for stopping servo rotation
const int reset_threshold = 8;          //threshold for reseting the solar

void setup()
{
  Serial.begin(9600);                         
  zenith_servo.attach(zenith_servo_pin);            
  azimuthal_servo.attach(azimuthal_servo_pin);        
}

void loop()
{
   ldr1_getter = analogRead(ldr1);       
   ldr2_getter = analogRead(ldr2);         
   ldr3_getter = analogRead(ldr3);         
   ldr4_getter = analogRead(ldr4);
   
   int avg_top_ldr_value = (ldr1_getter + ldr2_getter) / 2;      
   int avg_bottom_ldr_value = (ldr3_getter + ldr4_getter) / 2;  
   int avg_left_ldr_value = (ldr1_getter + ldr3_getter) / 2; 
   int avg_right_ldr_value = (ldr2_getter + ldr4_getter) / 2; 

   int azimutal_difference = avg_right_ldr_value - avg_left_ldr_value;
   
//     automaticSolarTracker();
       Serial.println(azimutal_difference);
        
      moveServoHorizontal(azimutal_difference);
     
     delay(1000);
}

void moveServoHorizontal(int azimutal_difference){
  if(abs(azimutal_difference) > rotation_threshold){
    if (azimutal_difference > 0) {
        if (azimuthal_servo.read() < 180) {
          azimuthal_servo.write((azimuthal_servo.read() + 2));
        }
      }
    if (azimutal_difference <  0) {
      if (azimuthal_servo.read() > 0) {
        azimuthal_servo.writeMicroseconds((azimuthal_servo.read() - 2));
      }
    }
  }
}
//void moveServoVertical(){
//  
//}

//void automaticSolarTracker(){
//     sum_of_avg_ldr_values = avg_top_ldr_value + aavg_bottom_ldr_value + avg_left_ldr_value + avg_right_ldr_value;
//     
//    //Finding the difference between the average of the top and bottom LDR
//     zenith_difference = aavg_top_ldr_value - avg_bottom_ldr_value;  
//     
//    //Finding the difference between the average of the right and left LDR  
//     diffazi = avgright - avgleft;    //Get the different average betwen LDRs right and LDRs lef
//
//
//     if(sum_of_avg_ldr_values < 8){
//      rotateToInitialPosition();
//     }
//    //left-right movement of solar tracker
//     
//      
//             
//      //up-down movement of solar tracker
//
//      if (abs(diffelev) >= light_intensity_difference){    //Change position only if light difference is bigger then thelight_intensity_difference
//       if (diffelev > 0) {
//        if (vertical_servo.read() < 180) {
//          vertical_servo.writeMicroseconds((horizontal_servo.read() - 30));
//        }
//      }
//      if (diffelev <  0) {
//        if (vertical_servo.read() > 0) {
//          vertical_servo.writeMicroseconds((horizontal_servo.read() + 30));
//        }
//      }
//    }       
// }  

// void rotateToInitialPosition(){
//
//  //Setting the solar-panel to face sun's rising position
//  vertical_servo.write(30);
//  horizontal_servo.write(0);
// }
