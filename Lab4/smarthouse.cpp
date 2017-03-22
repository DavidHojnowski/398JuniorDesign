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
	//Rooms:
	Gpio attic("");
	Gpio bedroom1("");
	Gpio bedroom2("");
	Gpio bathroom("");
	Gpio livroom("");
	Gpio kitchen("");
	//Other:
	Gpio fan("");
	Gpio heat("");
	Gpio cold("");
	Gpio laser("");


	while(true){
		string fromESP = read(4);
			   if(!fromESP.compare("ATIC"){
			   if(attic.get() == 1){
			   
			   }else{
			   
			   }
			
		} else if(!fromESP.compare("BED1"){
		
		} else if(!fromESP.compare("BED2"){	
		
		} else if(!fromESP.compare("BATH"){	
		
		} else if(!fromESP.compare("LVRM"){	
		
		} else if(!fromESP.compare("KCHN"){	
		
		} else if(!fromESP.compare("DOOR"){	
		
		} else if(!fromESP.compare("HEAT"){
		
		} else if(!fromESP.compare("COLD"){
				
		} else if(!fromESP.compare("PRTY"){
		
		} else if(!fromESP.compare("HONN"){
				
		} else if(!fromESP.compare("HOFF"){			
			
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
