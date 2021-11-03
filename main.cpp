#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <iostream>

//wiringpi library is used to define the pins of the things attached
//the below code has been taken reference from www.circuitpython.com/dht11
//Dht11 is attached to pin number 7
//dht11 gives output in terms of temperature and humidity, three services have been created with dht11
//temperature in celsius, temperature in fahranheit and humidity
//fourth service is the button and led functionality.
//the main function gives the options to choose from available functionalities and calls the corresponding service

#define MAXTIMINGS	85
#define DHTPIN		7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };
volatile int f;
using namespace std;
void read_dht11_dat(string type)
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	//float	f; 
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	pinMode( DHTPIN, INPUT );
 
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
 
		if ( counter == 255 )
			break;
 
		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
 
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		if (type.compare("fahrenheit") == 0) {
			f = (int)(dht11_dat[2] * 9. / 5. + 32);
			//return dht11_dat[2] * 9. / 5. + 32;
		}
		//Return the temp in celsius
		else if (type.compare("celsius") == 0) {
			f = dht11_dat[2] + 0.01*dht11_dat[3];
			//return dht11_dat[2] + 0.01*dht11_dat[3];
		}
		//Return the percent humidity
		else if (type.compare("humidity") == 0) {
			f = dht11_dat[0] + 0.01*dht11_dat[1];
			//return dht11_dat[0] + 0.01*dht11_dat[1];
		}
		else {
			f = 0;
		}
	}

	//return 00.00;
}



 
int main( void )
{
	printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );
	float a;
	if ( wiringPiSetup() == -1 )
		exit( 1 );
	//a = read_dht11_dat();
	//printf("%.1f F",a);
	pinMode(0, OUTPUT);		// Configure GPIO0 as an output
	pinMode(2, INPUT);
	int user_input = 0;
	std::cout << "Test the different sensors" << std::endl;
	
	std::cout << "Enter 1 for Temperature in Fahrenheit" << std::endl;
	std::cout << "Enter 2 for Temperature in Celsius" << std::endl;
	std::cout << "Enter 3 for Humidity" << std::endl;
	std::cout << "Enter 4 for led and button" << std::endl;
	std::cin >> user_input;
	
	switch(user_input){
		case 1:{
			while ( 1 )
			{
				read_dht11_dat("fahrenheit");
				printf("(%i F)\n",f);
				delay( 100 ); 
			}
			break;
		}
			
		case 2:{
			while ( 1 )
			{
			read_dht11_dat("celsius");
			printf("(%i C)\n",(int)f);
			delay( 100 ); 
			}
			break;
		}
			
		case 3:{
			while ( 1 )
			{
				read_dht11_dat("humidity");
				printf("(%i %)\n",f);
				delay( 100 ); 
			}
			break;
		}
		case 4:{
			while(1)
			{
	// Button is pressed if digitalRead returns 0
				//if(digitalRead(2) == 1)
				//{	
	// Toggle the LED
				digitalWrite(0, !digitalRead(0));
				delay(500); 	// Delay 500ms
				
			}
			break;
		}
		default:{
			break;
		}
	}
	
	return(0);
}
