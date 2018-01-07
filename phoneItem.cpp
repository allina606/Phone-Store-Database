/*Phone class implementation file */
#include <iostream>
#include <string>
#include "phoneItem.h"
using namespace std;

/* **************
 * Prints an item in phone database
 * ************/

void Phone::display(int index) {
		cout << "Printing Phone " << index << endl;
		cout << "ID = " << id << endl <<
			"Brand name = " << brand << endl <<
			"Price = " << price << endl <<
			"Quantity = " << quantity << endl << endl;
	return;
	}

/* *************************
Validates value for product ID, and then calls function to set it
************************* */

bool Phone::validate(char * id) {
    char validate;
    bool flag = true;

    //validating
    if(strlen(id)==4) {
        for (int i=0; i < strlen(id); i++) {
            validate = id[i];
            if (i<2) {
                if (!((validate <= 'z' && validate >= 'a') || (validate <= 'Z' && validate >= 'A')))
                    flag = false;
            }
            if (i>1) {
                if (!(validate <= '9' && validate >= '0'))
                    flag = false;
            }
        }
    }
    else
        flag = false;

    if(flag)
        setID(id);
    else
        cout << "You have entered invalid data for product ID." << endl;

    return flag;
}

