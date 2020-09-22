//============================================================================
// Name        : BuildInFile.cpp
// Author      : Shir Bar Maoz
//============================================================================

#include <iostream>
#include <fstream>
#include <vector> 
#include "cppEmulate.h"
using namespace std;

int main() {
	while(true){ 
		try{
			string str;
			string space = " ";
			getline(cin,str);
			stringstream line(str);
			int findSpace = str.find(space);
			string makeAct = str.substr(0,findSpace); /*substring for the acting*/
			str = str.substr(findSpace+1,str.length());
			fstream file;
			cppEmulate start(file);
			if(makeAct=="read"){
				start.read(str);
			}
			else if(makeAct=="write"){
				start.write(str);
			}
			else if(makeAct=="touch"){
				start.touch(str);
			}
			else if(makeAct=="copy"){
				start.copy(str);
			}
			else if(makeAct=="remove"){
				start.remove(str);
			}
			else if(makeAct=="move"){
				start.move(str);
			}
			else if(makeAct=="cat"){
				start.cat(str);
			}
			else if(makeAct=="head"){
				start.head(str);
			}
			else if(makeAct=="tail"){
				start.tail(str);
			}
			else if(makeAct=="exit"){
				return 0;
			}
			else{
				throw cppEmulate::notSupported();
			}
		}
		catch(cppEmulate::notExist &e1){
			e1.PrintError();
		}
		catch(cppEmulate::notSupported &e2){
			e2.PrintError();
		}
		catch(cppEmulate::usageError &e3){
			e3.PrintError();
		}
		catch(cppEmulate::errorForCopy &e4){
			e4.PrintError();
		}
		catch(cppEmulate::errorForRemove &e5){
			e5.PrintError();
		}
	}
	return 0;
}