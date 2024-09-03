#include "ctrl.h"
//#include "std_msgs/Int64MultiArray.h"
/// @//set RTOS parameters
unsigned long prevTime = 0; //init prev time with 0

//configure encoder L & R
volatile long encoderLeftCount = 0 ;
volatile long encoderRightCount = 0 ;

//glopal var to take pwm for motors
std_msgs::Float32MultiArray inputPwm;
//subscriber cb for motor speed
void callback(const std_msgs::Float32MultiArray & velMsg){
  inputPwm = velMsg;
}
//sub to "/AgribotVelWpid" topic for pwm data
ros::Subscriber<std_msgs::Float32MultiArray> sub("/AgribotVel", &callback);

//global var to take encoder values
std_msgs::Float32MultiArray msg;
//pub for angular velocity for both motors
ros::Publisher pub("/encoder", &msg);
// std_msgs::Int64MultiArray msgenc;
// //pub for angular velocity for both motors
// ros::Publisher pubenc("/encodercount", &msgenc);

//init for motor & encoder
void ctrlInit(void){
    //sub & pub
    nh.advertise(pub);
    nh.subscribe(sub);
//    nh.advertise(pubenc);

    msg.data_length=2;
    msg.data= new float[msg.data_length];
  //  msgenc.data_length=2;
    //msgenc.data= new int64_t[msgenc.data_length];
 
    //motor init
    pinMode(pinDirLeft1,OUTPUT);
    pinMode(pinDirRight1,OUTPUT);
    pinMode(pinPwmLeft1,OUTPUT);
    pinMode(pinPwmRight1,OUTPUT);
    pinMode(pinDirLeft2,OUTPUT);
    pinMode(pinDirRight2,OUTPUT);
    pinMode(pinPwmLeft2,OUTPUT);
    pinMode(pinPwmRight2,OUTPUT);
    //init robot with speed = 0
    analogWrite(pinPwmLeft1,0);
    analogWrite(pinPwmRight1,0);
    analogWrite(pinPwmLeft2,0);
    analogWrite(pinPwmRight2,0);
    //encoder pin setups
    pinMode(encoderLeftA,INPUT_PULLUP);
    pinMode(encoderLeftB,INPUT_PULLUP);
    pinMode(encoderRightA,INPUT_PULLUP);
    pinMode(encoderRightB,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(encoderLeftA), updateEncoderLeft, RISING);
    attachInterrupt(digitalPinToInterrupt(encoderRightA), updateEncoderRight, RISING);
    //robotMove();
}
void robotMove(void){
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { // Read the position in an atomic block to avoid a potential misread if the interrupt coincides with this code running
        unsigned long currentTime = millis();  // get the current time
        if (currentTime - prevTime > interval) {  // check if enough time has elapsed since the last interrupt
            //meassuring angular velocity for left & right motors
            double motorLeftSpeed = double((encoderLeftCount / PPR) * (2 * PI) * (1000.0 / interval)); // Revs per second to radians per second
            double motorRightSpeed = - double((encoderRightCount / PPR) * (2 * PI) * (1000.0 / interval)); // Revs per second to radians per second
                       
            /*
            //Set motors speed with pwm in case of pid
            //for front engines
            setSpeed(inputPwm.data[1],pinDirRight1,pinPwmRight1);   //set right Motor with input speed.
            setSpeed(inputPwm.data[0],pinDirLeft1,pinPwmLeft1);     //set left Motor with input speed.
            //for rear engines
            setSpeed(inputPwm.data[1],pinDirRight2,pinPwmRight2);   //set right Motor with input speed.
            setSpeed(inputPwm.data[0],pinDirLeft2,pinPwmLeft2);     //set left Motor with input speed.
            */
           
            //convert linear velocity data to pwm in case no pid
            //for front engines
            setSpeed(mypwm(inputPwm.data[1]),pinDirRight1,pinPwmRight1);   //set right Motor with input speed.
            setSpeed(mypwm(inputPwm.data[0]),pinDirLeft1,pinPwmLeft1);     //set left Motor with input speed.
            //for rear engines
            setSpeed(mypwm(inputPwm.data[1]),pinDirRight2,pinPwmRight2);   //set right Motor with input speed.
            setSpeed(mypwm(inputPwm.data[0]),pinDirLeft2,pinPwmLeft2);     //set left Motor with input speed.
            //give feedback to be published
            msg.data[0]=motorLeftSpeed;
            msg.data[1]=motorRightSpeed;
            pub.publish(&msg);//publishing encoder angular velocity msgs

            // msgenc.data[0]=encoderLeftCount;
            // msgenc.data[1]=encoderRightCount;
            // pubenc.publish(&msgenc);//publishing encoder ticks msgs

            //reset counts to 0
            encoderLeftCount = 0;
            encoderRightCount = 0;
            prevTime = currentTime;
        }
   
    }

}
//set motor speed
void setSpeed(int pwm, int dirPin, int PwmPin){
    if(pwm > 0){
        digitalWrite(dirPin,LOW);
    }else if (pwm < 0)
    {
        digitalWrite(dirPin,HIGH);        
    }
    analogWrite(PwmPin,abs(pwm));
}
//convert speed to motor effort//////////////
int mypwm(float x){
            int m_pwm= round((x*255)/2);
            return m_pwm;
}
//update left encoder
void updateEncoderLeft(void){
    if(digitalRead(encoderLeftB)>0){
        encoderLeftCount++;
    }
    else{
        encoderLeftCount--;
    }

}
//update Right encoder
void updateEncoderRight(void){
    if(digitalRead(encoderRightB)>0){
        encoderRightCount++;
    }
    else{
        encoderRightCount--;
    }

}
