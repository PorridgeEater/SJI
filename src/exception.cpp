#include "exception.h"

Exception::Exception(const string &s){
	msg=s;
}

void Exception::errMessage(){
	cout<<"Error : "<<msg<<endl;
}
