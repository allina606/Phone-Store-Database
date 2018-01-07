/*Phone Class Header file */
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#ifndef HW6
#define HW6

class Phone
{
private:
    char id[5];
    string brand;
    double price;
    int quantity;
public:
    bool validate(char*);
    void display( int );
    // getters / accessors
    char* getId() { return id; }
    string getBrand() const { return brand; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    // setters / mutators
    void setID(char * id) { strcpy(this -> id, id); }
    void setBrand(string brand) { this -> brand = brand; }
    void setPrice(double price ) { this -> price = price; }
    void setQuantity(int quantity) { this -> quantity = quantity; }
};

#endif

