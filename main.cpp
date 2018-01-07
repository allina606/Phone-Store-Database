/*Allina Khan
 * HW#7 Phone database with two classes
 */
#include <iostream>
#include "database.h"
#include "phoneItem.h"

int main() {
    int arrSz;
    cerr << "Enter array size: ";
    cin >> arrSz;
	Database items(arrSz);

	items.menu();

return 0; }
