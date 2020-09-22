/*
 * cppEmulate.cpp
 *
 *  Created on: Jan 23, 2020
 *      Author: cs205848914
 */

#include "cppEmulate.h"

void cppEmulate::read(string str){ 
	string space = " ";
	int location;
	int findSpace = str.find(space);
	if (findSpace==-1)
		throw notSupported();

	string myFile = str.substr(0,findSpace);
	str = str.substr(findSpace+1,str.length());
	stringstream ss(str); /*make the location a number*/
	ss >> location;

	fileToOpen.open(myFile.c_str());
	cppEmulate start(fileToOpen,myFile);
	if (!fileToOpen){
		fileToOpen.close();
		throw notExist(myFile);
	}
		
	fileToOpen.seekg(0,fileToOpen.end);
	int size = fileToOpen.tellg();
	if(size!=0)
		cout << start[location] <<endl;

	fileToOpen.close();
}

void cppEmulate::write(string str){
	string space = " ";
	int location;
	string loc;
	char toWrite;
	int findSpace = str.find(space); /*for file name*/
	if (findSpace==-1)
		throw notSupported();

	string myFile = str.substr(0,findSpace);
	str = str.substr(findSpace+1,str.length());
	findSpace = str.find(space); /*for location in file*/
	if (findSpace==-1)
		throw notSupported();

	loc = str.substr(0,findSpace);
	str = str.substr(findSpace+1,str.length());
	stringstream ss(loc); /*make the location a number*/
	ss >> location;
	toWrite = str[0];

	fileToOpen.open(myFile.c_str());
	cppEmulate start(fileToOpen,myFile);
	if (!fileToOpen){
		fileToOpen.close();
		throw notExist(myFile);
	}

	start[location]=toWrite;
	fileToOpen.close();
}

void cppEmulate::touch(string str){
	string space = " ";
	int findSpace = str.find(space);
	if(findSpace!=-1){
		throw notSupported();
	}
	string file = str.substr(0,findSpace);
	
	fstream sourceFile;
	ofstream targeFile;
    sourceFile.open(file.c_str());
	if (!sourceFile){
	    targeFile.open(file.c_str());
		targeFile.close();
	}
	sourceFile.close();
}

void cppEmulate::copy(string str){
	string space = " ";
	string file1,file2;
	int findSpace = str.find(space);
	if(findSpace==-1)
		throw errorForCopy("copy");
	file1 = str.substr(0,findSpace);
	file2 = str.substr(findSpace+1,str.length());
	if(file2=="")
		throw errorForCopy("copy");
	
	ifstream sourceFile;
	ofstream targeFile;
    sourceFile.open(file1.c_str());
	if (!sourceFile){
	    throw notExist(file1);
	}
	
	try{
		targeFile.open(file2.c_str()); /*if the file is not exsist - creat it*/
	}catch(...){ /*if open the target file is fail*/
		sourceFile.close();
		throw notExist(file2);
	}
	while(!sourceFile.eof()){
		char c = sourceFile.get();
		targeFile << c;
	}
	targeFile.close();
	sourceFile.close();
}

void cppEmulate::remove(string fileToRemove){
	if(std::remove(fileToRemove.c_str()) != 0)
		throw errorForRemove(fileToRemove);
}

void cppEmulate::move(string str){
	string space = " ";
	string file1,file2;
	int findSpace = str.find(space);
	if(findSpace==-1){
		throw errorForCopy("move");
	}
	file1 = str.substr(0,findSpace);
	file2 = str.substr(findSpace+1,str.length());
	if(file2==""){
		throw errorForCopy("move");
	}

	ifstream sourceFile;
	ofstream targeFile;
    sourceFile.open(file1.c_str());
	if (!sourceFile){
	    throw notExist(file1);
	}
	
	try{
		targeFile.open(file2.c_str()); /*if the file is not exsist - creat it*/
	}catch(...){ /*if open the target file is fail*/
		sourceFile.close();
		throw notExist(file2);
	}
	while(!sourceFile.eof()){
		char c = sourceFile.get();
		targeFile << c;
	}
	targeFile.close();
	sourceFile.close();

	if(std::remove(file1.c_str()) != 0)
		throw notExist(file1);
}

void cppEmulate::cat(string toPrint){
	string space = " ";
	ifstream sourceFile;
    sourceFile.open(toPrint.c_str());
	if (!sourceFile){
	    throw notExist(toPrint);
	}
	
	sourceFile.seekg(0,sourceFile.end);
	int size = sourceFile.tellg();
	sourceFile.close();

	if(size!=0){
		sourceFile.open(toPrint.c_str());
		if (!sourceFile){
			throw notExist(toPrint);
		}
		sourceFile.seekg(0);
		while(!sourceFile.eof()){
			char c = sourceFile.get();
			cout << c;
		}
		cout << endl;
	}
	sourceFile.close();
}

void cppEmulate::head(string str){
	string space = " ";
	string file;
	int number;
	int findSpace = str.find(space);
	if(findSpace==-1){ /* the number is 10 */
		if(str==""){
			throw notSupported();
		}
		file=str;
		str="10";
	} else {
		file = str.substr(0,findSpace);
		str=str.substr(findSpace+1,str.length());
	}
	stringstream ss(str); /*make the str a number*/
	ss >> number;

	ifstream sourceFile;
    sourceFile.open(file.c_str());
	if (!sourceFile){
	    throw notExist(file);
	}
	
	int lines=1;
	vector<char> g1;
	while(!sourceFile.eof()){ /* print the line for catch the exception of out of range*/
		char c = sourceFile.get();
		g1.push_back(c);
		if(c=='\n') lines++;
	}
	sourceFile.close();

	if(lines < number)
		throw usageError("head",file,number);

	vector<char>::iterator ptr; 
    for (ptr = g1.begin(); ptr < g1.end(); ptr++) {
		if(number==0)
			break;
		cout << *ptr;
		if((*ptr)=='\n'){
				number--;
		}
	}
}

void cppEmulate::tail(string str){
	string space = " ";
	string file;
	int number;
	int findSpace = str.find(space);
	if(findSpace==-1){ /* the number is 10 */
		if(str==""){
			throw notSupported();
		}
		file=str;
		str="10";
	} else {
		file = str.substr(0,findSpace);
		str=str.substr(findSpace+1,str.length());
	}
	stringstream ss(str); /*make the str a number*/
	ss >> number;

	ifstream sourceFile;
    sourceFile.open(file.c_str());
	if (!sourceFile){
	    throw notExist(file);
	}
	
	int lines=1;
	vector<char> g1;
	while(!sourceFile.eof()){
		char c = sourceFile.get();
		g1.push_back(c);
		if(c=='\n') lines++;
	}
	sourceFile.close();
	int skip=lines-number;
	if(lines < number){
		throw usageError("tail",file,number);
	}

	vector<char>::iterator ptr; 
    for (ptr = g1.begin(); ptr < g1.end(); ptr++) {
		if(skip==0){
			cout << *ptr;
			if((*ptr)=='\n'){
				number--;
			} 
			if(number==0) break;
		}
		else{
			if((*ptr)=='\n'){
				skip--; /*until skip == number*/
			} 
		}	
	}
	cout << endl;
}

void cppEmulate::setFileName(string fileName) {
	this->fileName = fileName;
}

string cppEmulate::getFileName() const {
	return fileName;
}

cppEmulate::~cppEmulate(){
	fileToOpen.close();
}