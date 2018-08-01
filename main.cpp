#include <iostream>
#include <wiringPi.h>

using namespace std;

int main()
{
    cout << "Raspi led control" << endl;
    if(wiringPiSetup() == -1)
    {
        return 1;
    }
    while(true)
    {
        digitalWrite(0,1);
    delay(500);
    digitalWrite(0,0);
    delay(500);
    }
    return 0;
}
