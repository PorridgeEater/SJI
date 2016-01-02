#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

class Exception{
	string msg;
public:
	Exception(const string &s){
		msg=s;
	}
	void errMessage(){
		cout<<"Error : "<<msg<<endl;
	}
};

#endif