/* 
   Author: Zakaria Almatar
   Date: 07/31/09
   Class: CS163
   Assignment: Program#3
*/
/*
   File name: header.h
   Contains: This file has the class and struct declarations
*/



#include <cstdlib>
#include <string.h>
#include <iostream>
using namespace std;



struct cont_info  //structure which holds information of one call
{
  char *name, *phone, *email, *fax, *date;
  cont_info *next;
};       

class cont_list
{
  public:
    cont_list();     //initialize main pointers and set heads to NULL
    ~cont_list();    //deallocates dynamic memory and sets main pointers to NULL
    int store(char*name, char*phone, char*email, char*fax, char*date);  //stores a calls info
    cont_info *retrieve(char *date);      //checks calls by date
    cont_info *retrieve_n(char *name);   //checks calls by callers name
    int remove(char *date);           //removes calls by date

  private:
    //assigns data to a node;
    void assign_data(cont_info *&ptr, char*name, char*phone, char*email, char*fax, char*date); 
    //stores calls info by name;
    void store_n(char*name, char*phone, char*email, char*fax, char*date);
    int hash_d(char *date); // hashing by date
    int hash_n(char *name); // hashing by name
    cont_info **h_tbl_d;    //pointer to hash table by date
    cont_info **h_tbl_n;    //pointer to hash table by name
    int NAME_MAX;           //prime number for the name hash table 
};






