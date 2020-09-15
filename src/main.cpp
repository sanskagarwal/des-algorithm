#include <base/des_interface.h>
#include <iostream>

int main() {
	des::Des check_obj;

	std::string enc;
	try {
		check_obj.encrypt("12345678", "23415678", enc);
	} catch (const char *msg) {
		std::cout << msg;
	}

	std::cout << "Encrypted form: " << enc << "\n";

	for(int i=0;i<enc.size();i+=4)
	{
		int num=enc[i]-'0';
		int ans=(enc[i]-'0')*8 + (enc[i+1]-'0')*4 + (enc[i+2]-'0')*2 + (enc[i+3]-'0');
		if(ans>9)
			std::cout << (char)(ans-10+'a');
		else
			std::cout << ans;
		if(i%4==0 && i%8!=0 && i>0)
			std::cout << " ";
	}

	return 0;
}
