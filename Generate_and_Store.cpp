#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <signal.h> 

using namespace std;
string userData="";
string currentProcessFile="first.txt";

void spawn()
{
	int ParentPID = getpid(); //the parent pid
	pid_t pid;

	ostringstream _fileName;
	_fileName<<ParentPID;
	::currentProcessFile=_fileName.str()+".txt"; //get the parent pid as a file name
	
	while (ParentPID==getpid()){
		string fileName="aFile";
		ostringstream convert;
		ofstream file;
		
		cout<<"Enter some text..."<<endl;
		getline(cin,::userData);
		
		while (::userData.empty()){ //validate input
			cout<<"Not accepted.\nEnter some text...  "<<endl;	
			getline(cin,::userData);
		}
		
		if (userData=="Done"){
			return;
		}
		
		pid=fork();
		
		if (pid<0){ //error
			perror("Fork Error\n");
		}
		
		else if(pid==0){ //child
			cout<<"Writing to file: '"<<::currentProcessFile<<"'"<<endl;
			while (true){
				file.open(::currentProcessFile.c_str(),ios::out|ios::app);
				file<<::userData+"\r\n";
				file.close();
				sleep(1);
			}
		}
		
		else{ //parent
			ParentPID=getpid();
			convert<<pid;
			fileName = convert.str()+".txt";
			::currentProcessFile=fileName;
		}
	}
	return;
}
int main()
{  
	spawn();
	kill(0,SIGKILL);
	return 0;
}