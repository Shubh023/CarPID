#include <iostream>
#include <signal.h>
#include <wiringPi.h>
#include <softPwm.h>
 
using namespace std;

#define ENA 26
#define ENB 23
#define IN1 25
#define IN2 24
#define IN3 22
#define IN4 21

int speed = 0;
bool countUp = true;


static volatile bool keep_continue = true;


void setup()
{
    cout << "Setting up Pin Modes" << endl;
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    softPwmCreate(ENA, 0, 50);
    softPwmCreate(ENB, 0, 50);
}

void loop()
{
   cout << "Speed : " << speed << endl; 
   softPwmWrite(ENA, speed * 0.5);
   softPwmWrite(ENB, speed * 0.5);
   delay(15);
   if (speed == 500)
   {
	countUp = false;
   }
   if (speed == 200)
   {
	countUp = true;	
   }
   if (countUp)
   {
	speed++;
   }
   else
   {
	speed--;
   }
}

void reset()
{
    softPwmWrite(ENA, LOW);
    softPwmWrite(ENB, LOW);
    softPwmStop(ENA);
    softPwmStop(ENB);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void back()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

int main()
{
    cout << "Hello, World ! " << endl;
    if(wiringPiSetup() < 0){
	cout << "setup wiring pi failed" << endl;
	return 1;
    }
    signal(SIGINT, [](int) { keep_continue = false; });
    setup();
    back();
    while (keep_continue)
    {
        loop();
    }
    cout << "Resetting Everything, Bye !" << endl;
    reset();
    return 0;
};
