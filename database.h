/*Database Header file*/
#include <iostream>
#include "phoneItem.h"
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

#ifndef DATABASE_H
#define DATABASE_H

class Database {
	private:
	    Phone *items;
	    int arrSz;
	    int arrCapacity;
	public:
       Database(const Database &);
       Database operator=(const Database&);
       Database() {arrSz=0;}
       Database(int);
       ~Database();
       //Function prototypes
	   void print();
	   void del(char *);
	   void update(char *);
	   void addPhone();
	   int searching(char *);
	   void save();
	   void getFromFile();
	   void options(int);
	   void menu();
};

#endif

