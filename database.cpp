/*Database class implementation file */
#include <iostream>
#include "database.h"
#include "phoneItem.h"
#include <fstream>
using namespace std;

/* ***************************************
 * Constructor to set items array size and
 * all elements to zero
 * ************************************ */

Database::Database(int size) {
    arrCapacity=size;
    arrSz=0;

    if(size < 0) {
        cout << "Cannot instantiate an array with negative size." << endl;
    }
    else {
        items=new Phone[size];
        //the constructor is automatically called for each of these,
        //so I can leave it as is, right?
    }
}

/* ***************************************
 * Copy constructor
 * ************************************ */

Database::Database(const Database &other) {
    arrCapacity=other.arrCapacity;
    arrSz = other.arrSz;
    //delete [ ] items;
    items= new Phone[arrCapacity];

    for (int i=0; i < arrSz; i++) {
        items[i]=other.items[i];
    }
}

/* ***************************************
 * Operator Overloading
 * ************************************ */
Database Database::operator = (const Database& right) {
    delete [ ] items;
    arrCapacity=right.arrCapacity;
    arrSz = right.arrSz;
    items= new Phone[arrCapacity];

    for (int i=0; i < arrSz; i++) {
        items[i]=right.items[i];
    }
    return *this;
 }

/* ***************************************
 * destructor
 * ************************************ */

 Database::~Database() {
    delete [ ] items;
 }

/* ****************************
 * Retrieves entire data and puts it in a file to
 * use for later.
 * ************************* */

void Database::save() {
    ofstream out("hw7sokol.txt");

    for (int i=0; i < arrSz; i++ ) {
        out << items[i].getId() << endl
            << items[i].getBrand() << endl
            << items[i].getPrice() << endl
            << items[i].getQuantity() << endl;
    	}

    cout << "Database successfully saved!" << endl;
return;
}

/* ****************************
 * uses same file as save function to retrieve
 * data and put into appropriate variables.
 * ************************* */

void Database::getFromFile() {
    ifstream infile("hw7sokol.txt");

    int quantity;
    double price;
    string brand;
    char productID[5];

    while(!infile.eof()) {
        infile >> productID;
        infile >> brand;
        infile >> price;
        infile >> quantity;

        items[arrSz].validate(productID);
        items[arrSz].setPrice(price);
        items[arrSz].setQuantity(quantity);
        items[arrSz].setBrand(brand);
        arrSz++;
    }
    items[arrSz-1].setQuantity(0);
    items[arrSz-1].setBrand( items[arrSz].getBrand() );
    items[arrSz-1].setQuantity( items[arrSz].getQuantity() );
    items[arrSz-1].setPrice( items[arrSz].getPrice() );
    arrSz--;

    cout <<"Database successfully populated!" << endl << endl;

return;
}

/* ****************************
 * Validates that product to delete exists and
 * has a quantity zero. Then shifts array
 * starting from the index of product to delete.
 * ************************* */

void Database::del(char * idfind) {
    int exist;
    exist = searching(idfind);

    if (exist==-1)
        cout << "Function Delete failed. "<< endl << "ID \"" << idfind <<"\" does not exist." <<endl<<endl;
    else {
        if (items[exist].getQuantity()==0) {
        cout << "Deletion of product completed\n"<<
                "Product to be deleted: " << idfind << endl <<
                "Old number of products: " << arrSz << endl;

        //shifting over values in the array
        for (int x=exist; x<=arrSz; x++) {
                items[x].setBrand( items[x+1].getBrand() );
                items[x].setQuantity( items[x+1].getQuantity() );
                items[x].setPrice( items[x+1].getPrice() );
        }

        for (int x=exist; x<(arrSz-1); x++) {
            items[x].setID( items[x+1].getId() );
        }

        arrSz--;
        cout << "New number of products: " << arrSz << endl << endl;
        }
        else {
        cout << "Function Delete failed. Item \"" << idfind
                <<"\" does not have quantity zero." <<endl<<endl;
                }
    }
    return;
}

/* ****************************
 * Finds whether product user wishes to update exists (held in variable idfind)
 * Changes price or quantity using switch statement
 * ***************************/

void Database::update(char * idfind) {
    int exist, option, quantity;
    double price;
    exist=searching(idfind);

    if (exist==-1)
        cout << "Function update failed." << endl << "Product \""<<
                idfind << "\" does not exist." << endl << endl;
    else {
        cerr << "Press 1 to change price, or 2 to change quantity. "<<endl;
        cin >> option;

        switch(option) {
            case 1:
                cout << "Function Update Price for ID "<<items[exist].getId() << endl << "Old Price: $" << items[exist].getPrice() <<endl;
                cin >> price;
                items[exist].setPrice(price);
                cout << "New Price: $" << items[exist].getPrice() << endl << endl;
                break;
            case 2:
                cout << "Function Update Quantity for ID "<<items[exist].getId() << endl << "Old Quantity: " << items[exist].getQuantity() <<endl;
                cin >> quantity;
                items[exist].setQuantity(quantity);
                cout << "New Quantity: " << items[exist].getQuantity() << endl << endl;
                break;
            default:
                cout << "Update Function falied. " << endl <<
                        "Incorrect input \"" << option << "\" for update function." << endl<<endl;
                break;
        }
   }
return;
}

/* **************
 * Prints phone database
 * ************/

void Database::print() {
	cout <<"Product ID: \tBrand: \t\tPrice: \t\tQuantity: " << endl;

	for (int i=0; i < arrSz; i++ ) {
        cout << items[i].getId() << "\t\t"
            << items[i].getBrand() << "\t\t$"
            << items[i].getPrice() <<"\t\t "
            << items[i].getQuantity() << endl;
    	}
        cout << endl;
	return;
	}

/* ******************************
 * Adds an object to items array and assign Phone member variables
 *******************************/

void Database::addPhone() {
    int exist,quantity;
    double price;
    char productID[5];
    string brand;
    bool validate;

    cerr << "Input product ID, then price, then quantity, then brand name of product. (seperate with space) ";
    cin >> productID >> brand >> price >> quantity;

    exist=searching(productID);

    if (exist==-1) {
        validate = items[arrSz].validate(productID);

        if (validate) {
        arrSz++;
        items[arrSz-1].setPrice(price);
        items[arrSz-1].setQuantity(quantity);
        items[arrSz-1].setBrand(brand);

        cout << "Add Phone Function Success" << endl
             << "ID = " << items[arrSz-1].getId() << endl
             << "Brand = " << items[arrSz-1].getBrand() << endl
             << "Price = " << items[arrSz-1].getPrice() << endl
             << "Quantity = " << items[arrSz-1].getQuantity()  << endl << endl;
        }
        else
            cout << "Function addPhone failed." << endl<<endl;
    }
    else
        cout << "Function addPhone failed."<< endl << "Item \"" <<productID<< "\" already exists." << endl<<endl;
    return;
}

/* searches for id name in the object items
 * returns -1 if id name is not an member of 'items'
 * returns index of the object id name belongs to otherwise
 */

int Database::searching(char *productID) {
    int exist=-1;
    if (arrSz!=0) {
        	for (int i=0; i < arrSz; i++) {
                	if ((strcmp(items[i].getId(), productID)==0) )
                        	exist=i;
		}
        }
    return exist;
}

void Database::options(int option) {
    //temp values
    char prdct[5];
    int exist;

    while(option) {
        switch(option) {
            	case 1:
               		addPhone();
                	break;
            	case 2:
                	cerr << "Which product do you want to update? Enter id: " << endl;
                	cin >> prdct;
                	update(prdct);
                	break;
            	case 3:
                	cerr << "Which product do you want to display? Enter id: " << endl;
               		cin >> prdct;
               		exist=searching(prdct);
               		if(exist!=-1)
                        items[exist].display(exist);
                    else
                        cout << "Display function failed" << endl <<
                                "This phone does not exist." << endl << endl;
                	break;
                case 4:
                	print();
                	break;
            	case 5:
                	cerr << "Which product do you want to delete? Enter id:  "<< endl;
                	cin >> prdct;
                	del(prdct);
                	break;
            	case 6:
                	save();
                	break;
                case 7:
                    getFromFile();
                    break;
                case 8:
                    cout << "You're now exiting the program."<<endl;
                	exit(1);
                	break;
		default:
                	cout << option << " is not a menu option." << endl<<endl;
        	        break;
   	     	}

        menu();
    }
return;
}

void Database::menu() {
    int option;

    cerr << "1. Add item \n"
         << "2. Update item" << endl
         << "3. Display item \n4. Print database" <<endl
         << "5. Delete item"<<endl
         << "6. Save database" << endl
         << "7. Populate database from file" << endl
         << "8. Exit program" << endl;
    cerr <<"Enter an option: 1,2,3,4,5,6,7, or 8 from the menu: " << endl;
    cin >> option;

    options(option);

    return;
}
