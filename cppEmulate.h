/*
 * cppEmulate.h
 *
 *  Created on: Jan 23, 2020
 *      Author: cs205848914
 */

#ifndef CPPEMULATE_H_
#define CPPEMULATE_H_

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

class cppEmulate {
public:
	class myInnerClass{ /*for write function*/
		public:
			myInnerClass(fstream &file,fstream::pos_type pos_): outputFile(file),pos(pos_) {}
			myInnerClass& operator=(char c) {
				outputFile.seekp(pos);
				outputFile.put(c);
				return *this;
			}
			operator char() {
				outputFile.seekg(pos);
				return char(outputFile.get());
			}
			~myInnerClass(){
				outputFile.close();
			}
		private:
			std::fstream& outputFile;
			fstream::pos_type pos;
	};

	/*the big three - but copy c'tor and placement operator are no need in this work*/
	cppEmulate(std::fstream &file): fileToOpen(file) {}
	cppEmulate(std::fstream &file,string name): fileToOpen(file),fileName(name) {}
	~cppEmulate();

	myInnerClass operator[](int index) { /*for read and write*/
		fileToOpen.seekg(0,fileToOpen.end);
		int size = fileToOpen.tellg();
		if (index > size) /*or >= should check*/
    	{
			string name = getFileName();
			fileToOpen.close();
			throw notExist(name);
    	}
		return myInnerClass(fileToOpen,index); 
	}

	void setFileName(string fileName);
	string getFileName() const;
	void read(string str);
	void write(string str);
	void touch(string str);
	void copy(string str);
	void remove(string fileToRemove);
	void move(string str);
	void cat(string toPrint);
	void head(string str);
	void tail(string str);

	/* exception classes */
	class notExist {
	public:
		notExist(string name):fileName(name){}
		virtual void PrintError() const{
			cout << "error: " << fileName << " does not exist or cannot be processed." << endl;
		}
	private:
		string fileName;
	};

	class notSupported {
	public:
		notSupported(){}
		virtual void PrintError() const{
			cout << "error: command is not supported." << endl;
		}
	};

	class usageError {
	public:
		usageError(string name,string com,int num):fileName(name),command(com),number(num){}
		virtual void PrintError() const{
			cout << "error: USAGE " << command << " " << fileName << " [" << number << "]." << endl;
		}
	private:
		string fileName;
		string command;
		int number;
	};

	class errorForCopy {
	public:
		errorForCopy(string name):command(name){}
		virtual void PrintError() const{
			cout << "error: USAGE " << command << " SOURCE_FILENAME TARGET_FILENAME." << endl;
		}
	private:
		string command;
	};

	class errorForRemove {
	public:
		errorForRemove(string name):command(name){}
		virtual void PrintError() const{
			cout << "error: USAGE " << command << " FILENAME." << endl;
		}
	private:
		string command;
	};

private:
	std::fstream& fileToOpen;
	string fileName;
};

#endif /* CPPEMULATE_H_ */