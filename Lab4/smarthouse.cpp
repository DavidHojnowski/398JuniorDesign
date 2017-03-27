#include <iostream>
#include <string.h>
#include <cstdio>
#include <unistd.h>
#include "Gpio.h"
#include "smarthouse.h"

using namespace std;

smarthouse::smarthouse(int tty){
	espDevice = new esp(tty);
	
}

string smarthouse::read(int bytes){
	return espDevice->readIn(bytes);
}

void smarthouse::write(const char* data){
	espDevice->writeOut(data);
}

void smarthouse::run(){
	//Party boolean
	bool party = false;
	//Configure gpio/uart pins
	system("/home/debian/Lab4/config.sh");
	//Initialize GPIO pins:
	//Rooms:
	Gpio attic1("71");
	Gpio attic2("75");
	Gpio attic3("66");
	Gpio bedroom1("72");
	Gpio bedroom2("73");
	Gpio bathroom("74");
	Gpio livroom("69");
	Gpio kitchen("51");
	//Other:
	Gpio fan("70");
	Gpio heat("112");
	Gpio cold("110");
	Gpio door("5");
	
	//Set all GPIO to out direction
	//Rooms:
	attic1.changeDirection("out");
	attic2.changeDirection("out");
	attic3.changeDirection("out");
	bedroom1.changeDirection("out");
	bedroom2.changeDirection("out");
	bathroom.changeDirection("out");
	livroom.changeDirection("out");
	kitchen.changeDirection("out");
	//Other:
	fan.changeDirection("out");
	heat.changeDirection("out");
	cold.changeDirection("out");
	door.changeDirection("out");
	
	//Initialize them all to off when the app starts
	//Rooms:
	attic1.set("1");
	attic2.set("1");
	attic3.set("1");
	bedroom1.set("1");
	bedroom2.set("1");
	bathroom.set("1");
	livroom.set("1");
	kitchen.set("1");
	//Other:
	fan.set("0");
	heat.set("1");
	cold.set("1");
	door.set("0");	
	string fromESP;
	string trimmed;
	fromESP = read(100);

	while(true){
		fromESP = "";
		trimmed = "";
		fromESP = read(13);//TODO: accomodate for header info
		fromESP = fromESP[9] + fromESP[10] + fromESP[11] + fromESP[12]; 
		strcat();
		cout << "Our string: " << fromESP << endl;
		//9,10,11,12 index
			if(!fromESP.compare("ATIC")){ //Turns on/off all attic lights
				if(!attic1.get().compare("0")){
					attic1.set("1");
					attic2.set("1");
					attic3.set("1");
				}else{
			   		attic1.set("0");
			   		attic2.set("0");
			   		attic3.set("0");
				}	
			}else if(!fromESP.compare("BED1")){//Turn on/off LEDs in Bedroom1
				if(!bedroom1.get().compare("0")){
					bedroom1.set("1");
				}else{
			   		bedroom1.set("0");
				}
			}else if(!fromESP.compare("BED2")){//Turn on/off LEDs in Bedroom2
				if(!bedroom2.get().compare("0")){
					bedroom2.set("1");
				}else{
			   		bedroom2.set("0");
				}
			}else if(!fromESP.compare("BATH")){//Turn on/off LEDs in Bathroom
				if(!bathroom.get().compare("0")){
					bathroom.set("1");
				}else{
			   		bathroom.set("0");
				}
			}else if(!fromESP.compare("LVRM")){//Turn on/off LEDs in Living Room
				if(!livroom.get().compare("0")){
					livroom.set("1");
				}else{
			   		livroom.set("0");
				}
			}else if(!fromESP.compare("KCHN")){//Turn on/off LEDs in Kitchen
				if(!kitchen.get().compare("0")){
					kitchen.set("1");
				}else{
			   		kitchen.set("0");
				}
			}else if(!fromESP.compare("DOOR")){//Lock/Unlock Door
				if(!door.get().compare("0")){
					door.set("1");
				}else{
			   		door.set("0");
				}
			}else if(!fromESP.compare("HEAT")){//Enable the model cooling system
				if(!cold.get().compare("0")){ //if cold is on turn it off
					cold.set("1");
				} 
				
				if(!heat.get().compare("0")){
					heat.set("1");
					fan.set("1");
				}else{
			   		heat.set("0");
			   		fan.set("0");
				}
			}else if(!fromESP.compare("COLD")){//Enable the model heating system
				if(!heat.get().compare("0")){//if heat is on turn it off
					heat.set("1");
				} 
				
				if(!cold.get().compare("0")){//if cold is on turn it off
					cold.set("1");
					fan.set("0");
				}else{
			   		cold.set("0");
			   		fan.set("1");
				}
			}else if(!fromESP.compare("PRTY")){//Enables or disables party mode
				if(!party){
					party = true;
				}else{
					party = false;
				}
			}else if(!fromESP.compare("HOFF")){//Turn all components off
					//Rooms:
					attic1.set("1");
					attic2.set("1");
					attic3.set("1");
					bedroom1.set("1");
					bedroom2.set("1");
					bathroom.set("1");
					livroom.set("1");
					kitchen.set("1");
					//Other:
					fan.set("0");
					heat.set("1");
					cold.set("1");
					door.set("0");
			}else if(!fromESP.compare("HONN")){//Turn all components on	
					//Rooms:
					attic1.set("0");
					attic2.set("0");
					attic3.set("0");
					bedroom1.set("0");
					bedroom2.set("0");
					bathroom.set("0");
					livroom.set("0");
					kitchen.set("0");
					//Other:
					fan.set("0");
					heat.set("0");
					cold.set("1");
					door.set("0");
			}	
			
			if(party){//TODO: PARTY MODE
				//do party things
			}
			
			
	}
}

smarthouse::~smarthouse(){
	if(espDevice !=NULL){
		delete(espDevice);
	}
}

#ifdef TEST_smart
using namespace std;

int main(){
	smarthouse sm(1);
	sm.run();

	//"(DEV#) (SIDE) (IO#) (VALU)"
	//"(1or2) (AorB) (0-7) (0or1)"
	//ex: "1 B 0 0"
	//String array; array[0] = 1, array[1] = B, array[2] = 0, array[3] = 0;
	//string for storing binary value of GPIO value: "00000000"
	//string at position 'array[2]' is value 'array[3]', eliminates bitwise anding/oring

}
#endif
