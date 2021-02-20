//
//  main.cpp
//  CS_204_HW3
//
//  Created by Ege Berk Yurtkoruyan on 29.02.2020.
//

#include <iostream>
#include <string>
#include "cardclass.cpp"
#include <fstream>
#include <sstream>

using namespace std;

/* THIS PART IS TAKEN FROM MY OWN HW2 */
bool CheckCardNumber(string card_no){
//    THIS FUNCTION CONTROLS IF THE INPUT CARD NUMBER IS VALID OR NOT.
//    THIS FUNCTION WILL BE SUMMONED IF THE USER PICKS 2 FROM THE MENU.
    if(card_no.length() != 16){
        return false;
    }else{
    
        for(int i = 0 ; i < 16 ; i++ ){
            if ( card_no[i] > '9' || '0' > card_no[i] )
                return false;
        }
        return true;
    }
    
}
/* END OF PART TAKEN FROM MY OWN HW2 */

int main() {
    
//    CLASS FUNC UNUT MA
    CardList cards_list;
    
    string input;
    
    do{
    
        cout << "1) Upload Card(s) from a File" << endl
            << "2) Display List Chronological" << endl
            << "3) Display List Reverse Chronological" << endl
            << "4) Card Search" << endl
            << "5) Bulk Delete" << endl
            << "6) Exit" << endl
            << "Please choose option from the menu: " ;
            
        cin >> input;
        
        if(input == "1"){
            ifstream file;
            string filename;
            cout << "Please enter file name: ";
            cin >> filename;
            
            file.open(filename.c_str());
            
            if(file.fail())
                cout << "\nCould not find a file named " << filename << "\n\n";
            else{
                string card_no , line;
                int month , year;
                
                cout << endl;
                
                while(getline(file,line)){
                    stringstream ss(line);
                    ss >> card_no >> month >> year;
                    
                    cards_list.insertCard(card_no, month, year);
                }
                cout << endl;
            }
            
            
        }else if(input == "2"){
            cout << endl;
            cards_list.displayListChronological();
        }else if(input == "3"){
            cout << endl;
            cards_list.displayListReverseChronological();
        }else if(input == "4"){
            string card;
            cout << "Please enter the credit card number: ";
            cin >> card;
            
            if(CheckCardNumber(card))
                cards_list.cardSearch(card);
            else
                cout << "Invalid format!" << endl;
            
            cout << endl;
    
        }else if(input == "5"){
            
            int month_input, year_input;
            string error;
            
            cout << "Please enter month and year: " ;
            
            cin >> month_input >> year_input;
            
            bool mi = month_input , yi = year_input;
            
            if(mi && yi && month_input <= 12 && month_input >= 1){
                
                cout << endl;
                cards_list.bulkDelete(month_input, year_input);
                
                
            }else if (mi && (month_input > 12 || month_input < 1) && yi){
                
                cout << "Invalid format!" << endl;
                
            }else if (mi || yi){
                
                cout << "Invalid format!" << endl;
                cin.clear();
                cin >> error;
                
            }else{
                
                cout << "Invalid format!" << endl;
                cin.clear();
                cin >> error;
                cin.clear();
                cin >> error;
                
            }
            
            cout << endl;
            
            
        }else if(input != "6"){
            cout << "Invalid operation!" << endl << endl;
        }
        
    }while(input != "6");
    cards_list.deleteAll();
    cout << "All the nodes have been deleted!" << endl
        << "Terminating!!!" << endl;
    
    return 0;
}
