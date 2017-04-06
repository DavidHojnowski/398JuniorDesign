	int partyVal;
	int randWait;
	
	
	
	if(party){
		
		partyVal = rand() % 8;	   //allows for random selection of colors 
		randWait = rand() % 1000;  //allows for more random flashing and what not; likely needs tweaks

		if(partyVal == 0){
			Tristate1.set("0");
			Tristate2.set("0");
			Tristate3.set("0");
		}else if(partyVal == 1){
			Tristate1.set("0");
			Tristate2.set("0");
			Tristate3.set("1");	
		}else if(partyVal == 2){
			Tristate1.set("0");
			Tristate2.set("1");
			Tristate3.set("0");	
		}else if(partyVal == 3){
			Tristate1.set("0");
			Tristate2.set("1");
			Tristate3.set("1");	
		}else if(partyVal == 4){
			Tristate1.set("1");
			Tristate2.set("0");
			Tristate3.set("0");	
		}else if(partyVal == 5){
			Tristate1.set("1");
			Tristate2.set("0");
			Tristate3.set("1");	
		}else if(partyVal == 6){
			Tristate1.set("1");
			Tristate2.set("1");
			Tristate3.set("0");	
		}else if(partyVal == 7){
			Tristate1.set("1");
			Tristate2.set("1");
			Tristate3.set("1");	
		}
		usleep(randWait);
	}

	//include and initialize Servo(pwm) object w/ gpio

	if(input == door){
		if(door == open)
			door.angle(0);
		else
			door.angle(90);
	}












