
wiringPiSetupGpio();
int servoPin = 10;
pinMode(servoPin, OUTPUT);
int value = 0;
for(int i = 0; i < Input1*2; i++)
{
	digitalWrite(servoPin,value);
	value = !value;
	delay(80);
}

