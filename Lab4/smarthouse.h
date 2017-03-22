#ifndef smarthouse_H_
#define smarthouse_H_

#include "esp.h"

using namespace std;
class smarthouse{
	public:
		smarthouse(int tty);
		void write(const char* data);
		string read(int bytes);
		void smarthouse::run()
		
		~smarthouse();
	private:
		esp* espDevice;
	
	
	
};
#endif
