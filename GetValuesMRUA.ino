// Include the Arduino Stepper Library
#include <Stepper.h>
#include <Ultrasonic.h>

const int trigPin = 5; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
const int echoPin = 6; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
Ultrasonic ultrasonic(trigPin,echoPin);

const int stepsPerRevolution = 48;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int var = 0;

double positionNow = 30;
double positionFinal = 20;


double catetoOposto = 7.6;
double pi = 3.141592653;

float angle_rad = positionNow * pi / 180;
float tan_result = tan(angle_rad);
double catetoAdj = catetoOposto / tan_result;

float angle_rad_final = positionFinal * pi / 180;
float tan_result_fianl = tan(angle_rad_final);
double catetoAdjFinal = catetoOposto / tan_result_fianl;

double steps = (catetoAdj - catetoAdjFinal) / 0.004508;

long microsec = ultrasonic.timing();
float cmMsec, cmMsecNew = ultrasonic.convert(microsec, Ultrasonic::CM);

double timeInit = 0;
bool firstTime = false;

void setup()
{
	// set the speed at 60 rpm:
	myStepper.setSpeed(30);
	// initialize the serial port:
	Serial.begin(9600);   
}

void loop() 
{

  microsec = ultrasonic.timing();
  cmMsecNew = ultrasonic.convert(microsec, Ultrasonic::CM);

  double timeNow = millis();
  
  if (cmMsecNew < 10){
    timeInit = timeNow;
    firstTime = false;
  }

  if (cmMsecNew > 10 && !firstTime)  
  {
    timeInit = timeNow;
    firstTime = true;
  }  

  if((timeNow - timeInit) > 0 && cmMsecNew > 8 && cmMsecNew < 34)
  {
    Serial.print(timeNow - timeInit);
    Serial.print("-");
    Serial.println(cmMsecNew);
  }
  

}
