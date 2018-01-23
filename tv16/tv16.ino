#include <Arduino.h>
#include <MsTimer2.h>

int encoderAPin=14;
int encoderBPin=15;


volatile long int FEncoderClicks;
volatile long int FLastEncoderClicks;
volatile long int FLastMillis;


volatile bool FDirection; // ����������� �������� true- ������, false - �����

void Init(){
  FLastEncoderClicks=0;
  FEncoderClicks=0;
}



// ���������� �� �������. ���������� ��� ���������� �������� �������� ���������
// � �������� �������� �� ����� ���������� �������� ���������
void timerInterrupt(){
  if (FEncoderClicks<FLastEncoderClicks) {
    // ������������� ��������� - ������� �������� � ������ �������
  }
  else {
    unsigned long XCurrentMillis=millis();
    long int XMilis=XCurrentMillis-FLastMillis;
    long int XClick=FEncoderClicks-FLastEncoderClicks;



    FLastMillis=XCurrentMillis;
    FLastEncoderClicks=FEncoderClicks;
  }
}

// ���������� �� ������� ��������. ���������� ��� ���������� ���������� "�������" ��������
void encoderInterrupt(){
  bool XDir=digitalRead(encoderBPin);   // ������ �����������
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
