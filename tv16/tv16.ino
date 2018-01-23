#include <Arduino.h>
#include <MsTimer2.h>

int encoderAPin=14;
int encoderBPin=15;


volatile long int FEncoderClicks;
volatile long int FLastEncoderClicks;
volatile long int FLastMillis;


volatile bool FDirection; // Направление движения true- вперед, false - назад

void Init(){
  FLastEncoderClicks=0;
  FEncoderClicks=0;
}



// Прерывание по таймеру. Необходимо для вычисления скорости шагового двигателя
// и отправки комманды на плату управления шагового двигателя
void timerInterrupt(){
  if (FEncoderClicks<FLastEncoderClicks) {
    // останавливаем двигатель - енкодер крутится в другую сторону
  }
  else {
    unsigned long XCurrentMillis=millis();
    long int XMilis=XCurrentMillis-FLastMillis;
    long int XClick=FEncoderClicks-FLastEncoderClicks;



    FLastMillis=XCurrentMillis;
    FLastEncoderClicks=FEncoderClicks;
  }
}

// Прерывания по сигналу энкодера. Необходимо для увеличения количества "щелчков" энкодера
void encoderInterrupt(){
  bool XDir=digitalRead(encoderBPin);   // читаем направление
  if (XDir=FDirection) {
        FEncoderClicks++;
  }
  else {
  FDirection=not FDirection;
  FEncoderClicks=0;

  }

}


void setup()
{
	init();
	Serial.begin(9600);

	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
    pinMode(encoderAPin,INPUT);
    pinMode(encoderBPin,INPUT);


	pinMode(13, OUTPUT);

	MsTimer2::set(100,timerInterrupt);
	MsTimer2::start();


}

void loop()
{

	delay(1000);              // wait for a second
	digitalWrite(13, HIGH);   // set the LED on
	delay(1000);              // wait for a second
	digitalWrite(13, LOW);    // set the LED off
}
