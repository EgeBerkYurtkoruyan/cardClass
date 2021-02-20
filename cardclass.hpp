//
//  cardclass.hpp
//  CS_204_HW3
//
//  Created by Ege Berk Yurtkoruyan on 29.02.2020.
//

#ifndef _CARDCLASS_H_
#define _CARDCLASS_H_

#include <string>
#include <iostream>

using namespace std;

/* THIS PART BELOW IS TAKEN FROM .pdf FILE OF CS204 HOMEWORK 3 FILES*/

    void insertCard (string creditCardNo, int month, int year);
       //inserts a new card to the structure in sorted fashion
    void displayListChronological ();
       //displays entire structure in chronological order
    void displayListReverseChronological ();
       //displays entire structure in reverse chronological order
    void cardSearch (string creditCardNo);
       //displays all of the occurrences of the given card number
    void bulkDelete (int m, int y);
       //deletes all nodes up to and including given expiration date
    void deleteAll ();
       //deletes the entire structure

/* END OF THE PART TAKEN FRROM THE .pdf FILE OF THE HW3 FILES*/


#endif
