//
//  cardclass.cpp
//  CS_204_HW3
//
//  Created by Ege Berk Yurtkoruyan on 29.02.2020.
//  

#include "cardclass.hpp"
#include <fstream>
#include <sstream>
#include "strutils.h"

using namespace std;

/* THIS PART BELOW IS TAKEN FROM .pdf FILE OF CS204 HOMEWORK 3 FILES*/

struct creditCardNode{
     
    string creditCardNo;
    creditCardNode * next;
    
//    default constructure
    creditCardNode()
        : creditCardNo("") , next(NULL)
    {}
//    constructure
    creditCardNode(string s , creditCardNode* n)
        : creditCardNo(s) , next(n)
    {}
        
};

struct expirationNode{
    
    int month, year;
    creditCardNode * cHead;
    expirationNode * next;
    expirationNode * prev;
    
//    default constructure
    expirationNode()
        : month(0) , year(0) , cHead(NULL) , next(NULL) , prev(NULL)
    {}
//     constructure
    expirationNode(int m , int y , creditCardNode * c , expirationNode * n , expirationNode * p)
        : month(m) , year(y) , cHead(c) , next(n) , prev(p)
    {}

};

/* END OF THE PART TAKEN FRROM THE .pdf FILE OF THE HW3 FILES*/



class CardList{

public:
    CardList()
    {
//      default constructor that creates an empty list
        head = NULL;
        tail = NULL;
    }
        
    void insertCard (string creditCardNo, int month, int year){
        //inserts a new card to the structure in sorted fashion
        creditCardNode* ptr_card ;
        creditCardNode* ptr_card_check ;
        
        
        
        if(head == NULL){
            ptr_card = new creditCardNode(creditCardNo, NULL);
            head = new expirationNode(month, year , ptr_card , NULL ,NULL);
            cout << creditCardNo << " " << month << " " << year <<  ": added to a new expiration date node" << endl;

        }else{
            expirationNode * ptr;
            ptr = head;
            bool not_done = true;
            
            expirationNode * prev_ptr = head;
            
            while(ptr != NULL) {
                if(ptr->month == month && ptr->year == year) {
                    not_done = false;
                    ptr_card = ptr->cHead;
                    ptr_card_check = ptr->cHead;
                    
                    bool exists = false;
                    
                    while (ptr_card_check != NULL) {
                        if (creditCardNo == ptr_card_check->creditCardNo)
                            exists = true;
                        ptr_card_check = ptr_card_check->next;
                    }
                    
                    bool done = false;
                    creditCardNode* ptr_next;
                    
                    if(!exists && ptr->cHead->next == NULL && atoi(ptr->cHead->creditCardNo) > atoi(creditCardNo) ){
                        creditCardNode* next;
                        next = ptr->cHead;
                        ptr->cHead = new creditCardNode(creditCardNo, next);
                        done = true;
                        
                    }
                    
                    if(!done){
                        while(ptr_card->next != NULL && !exists){
                            
                            string check_next = ptr_card->next->creditCardNo, input_string = creditCardNo;
                            
                            if (atoi(check_next) > atoi(input_string) && !exists){
                                ptr_next = ptr_card->next;
                                
                                ptr_card->next = new creditCardNode(creditCardNo,ptr_next);
                                cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
                                done = true;
                                break;
                            }
                                
                          
                            ptr_card = ptr_card->next;
                        }
                    }
                
                    if(exists){
                        cout << creditCardNo << " " << month << " " << year << ": this card was already inserted" << endl;
                        exists = false;
                    }else if (!done && !exists){
                        ptr_card->next = new creditCardNode(creditCardNo,NULL);
                        cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
                        }
                    done = false;
                }
                
                prev_ptr = ptr;
                ptr = ptr->next;
            }
            
            if(not_done) {
                ptr_card = new creditCardNode(creditCardNo, NULL);
                prev_ptr->next = new expirationNode(month, year , ptr_card , NULL , prev_ptr);
                cout << creditCardNo << " " << month << " " << year <<  ": added to a new expiration date node" << endl;
                tail = prev_ptr->next;
                
            }
        }
    }
        
    void displayListChronological (){
        //displays entire structure in chronological order
         int min_m = 0 , min_y = 0 , m = 12, y=9999;
        //    m and y values should be the biggest possible in order to minimize them step by step until they are the values we seek.
        expirationNode* ptr = head;
        
             if(ptr != NULL){
                
                expirationNode* ptr2;
                ptr2 = ptr;
                
                creditCardNode* ptr3;
                expirationNode* start;
                start = ptr;
            
                while(ptr2 != NULL){
                    while(ptr != NULL){
                        if(((ptr-> month < m && ptr->year == y) || ptr->year < y) && (min_y < ptr->year || (min_y == ptr-> year && min_m < ptr->month))){
                            m = ptr-> month;
                            y = ptr-> year;
                            ptr3 = ptr->cHead;
                        }
                        
                        ptr = ptr->next;
                    }
                    if(y != 9999){
                        cout << "Expiration Date: " << m << " " << y << endl;
                        int counter = 1;
                        while(ptr3 != NULL){
                            cout << counter++ << ") " << ptr3->creditCardNo << endl;
                            ptr3 = ptr3->next;
                        }
                        cout << "-------------------" << endl << endl;
                    }
                    min_y = y;
                    min_m = m;
                    m = 12;
                    y = 9999;
                    ptr = start;
                    ptr2 = ptr2->next;
                    }
            }else{
        //        this part wil be activated if there is no node to list.
                cout << "List is empty!" << endl<< endl;
            }
    }
    void displayListReverseChronological (){
        //displays entire structure in reverse chronological order

                int max_m = 12 , max_y = 9999 , m = 0, y=0;
               //    m and y values should be the smallest possible in order to maximize them step by step until they are the values we seek.
               expirationNode* ptr = tail;
               
                    if(ptr != NULL){
                       
                       expirationNode* ptr2;
                       ptr2 = ptr;
                       
                       creditCardNode* ptr3;
                       expirationNode* start;
                       start = ptr;
                   
                       while(ptr2 != NULL){
                           while(ptr != NULL){
                               if(((ptr-> month > m && ptr->year == y) || ptr->year > y) && (max_y > ptr->year || (max_y == ptr-> year && max_m > ptr->month))){
                                   m = ptr-> month;
                                   y = ptr-> year;
                                   ptr3 = ptr->cHead;
                               }
                               
                               ptr = ptr->prev;
                           }
                           if(y != 0){
                               cout << "Expiration Date: " << m << " " << y << endl;
                               int counter = 1;
                               while(ptr3 != NULL){
                                   cout << counter++ << ") " << ptr3->creditCardNo << endl;
                                   ptr3 = ptr3->next;
                               }
                               cout << "-------------------" << endl << endl;
                           }
                           max_y = y;
                           max_m = m;
                           m = 0;
                           y = 0;
                           ptr = start;
                           ptr2 = ptr2->prev;
                           }
                   }else{
               //        this part wil be activated if there is no node to list.
                       cout << "List is empty!" << endl<< endl;
                   }
    }
    void cardSearch (string creditCardNo){
        //displays all of the occurrences of the given card number
        expirationNode* ptr;
        ptr = tail;
        
        bool exists = false;
        
        creditCardNode* card_ptr;
        
        while(ptr != NULL){
            card_ptr = ptr->cHead;
            while(card_ptr != NULL){
                if(creditCardNo == card_ptr->creditCardNo){
                    cout << endl << "There exists a credit card given number " << creditCardNo << " with expiration date: " << ptr->month << " " << ptr->year << endl;
                    exists = true;
                }
                card_ptr = card_ptr->next;
            }
            ptr = ptr->prev;
        }
        
        if(!exists)
            cout << endl << "There is no credit card with given credit card number: " << creditCardNo << endl;
        
    }
    void bulkDelete (int m, int y){
        //deletes all nodes up to and including given expiration date
        int min_m = 0 , min_y = 0 , m_start = m , y_start = y;
        expirationNode* ptr = head;
               
                    if(ptr != NULL){
                       
                       expirationNode* ptr2;
                       ptr2 = ptr;
                       bool happened = false;
                       creditCardNode* ptr3;
                       expirationNode* start;
                       start = ptr;
                       
                   
                       while(ptr2 != NULL){
                           expirationNode* will_be_deleted;
                           while(ptr != NULL){
                               if(((ptr-> month <= m && ptr->year == y) || ptr->year < y) && (min_y < ptr->year || (min_y == ptr-> year && min_m < ptr->month))){
                                   m = ptr-> month;
                                   y = ptr-> year;
                                   happened = true;
                                   ptr3 = ptr->cHead;
                                   will_be_deleted = ptr;
                               }
                               
                               ptr = ptr->next;
                           }
                           if(happened){
                               cout << "Node with expiration date " << m << " " << y << " and the following credit cards have been deleted! "<< endl;
                               int counter = 1;
                               
                               while(ptr3 != NULL){
                                   creditCardNode* garbage_card;
                                   garbage_card = ptr3;
                                   cout << counter << ") " << ptr3->creditCardNo << endl;
                                   counter++;
                                   ptr3 = ptr3->next;
                                   delete garbage_card;
                               }
                            
                               if(head == tail){
                                   head = NULL;
                                   tail = NULL;
                               }else if(head == will_be_deleted){
                                   head = head->next;
                                   will_be_deleted->next->prev = NULL;
                               }else if(tail == will_be_deleted){
                                   tail = tail->prev;
                                   will_be_deleted->prev->next = NULL;
                               }else{
                                   will_be_deleted->next->prev = will_be_deleted->prev;
                                   will_be_deleted->prev->next = will_be_deleted->next;
                               }
                               
                               delete will_be_deleted;
                            
                           }
                           min_y = y;
                           min_m = m;
                           m = m_start;
                           y = y_start;
                           ptr = start;
                           
                           if(!happened || ptr2->next == NULL)
                               ptr2 = ptr2->next;
    
                           happened = false;
                           }
                   }else{
               //        this part wil be activated if there is no node to list.
                       cout << "List is empty!" << endl<< endl;
                   }
        
    }
    void deleteAll (){
        //deletes the entire structure
        while(head != NULL){
            expirationNode* garbage;
            creditCardNode* card_ptr;
            garbage = head;
            card_ptr = garbage->cHead;
             while(card_ptr != NULL){
                creditCardNode* garbage_card;
                garbage_card = card_ptr;
                card_ptr = card_ptr->next;
                delete garbage_card;
                }
            head = head->next;
            delete garbage;
        }
        delete head;
    }
private:
    expirationNode * head;
    expirationNode * tail;

      
};

