/* 
   Author: Zakaria Almatar
   Date: 07/31/09
   Class: CS163
   Assignment: Program#3
*/
/*
   File name: implementation.h
   Contains: This file has the class' member functions' implementations 
             and definitions 
*/


#include <cstdlib>
#include <string.h>
#include <iostream>
#include "header.h"
using namespace std;




/*************************************************************************
***                            Constructor                             ***
*************************************************************************/
//initializes main pointers and set heads to NULL

cont_list::cont_list()
{
  NAME_MAX=71;   //name hash table will have 71 head pointers

  //initializing main pointers and setting heads to NULL
  h_tbl_d = new cont_info*[31];                       
  for(int i=0;i<31;++i)
    h_tbl_d[i]=NULL;
    
  h_tbl_n = new cont_info*[NAME_MAX];
  for(int i=0;i<NAME_MAX;++i)
    h_tbl_n[i]=NULL;
}


/*************************************************************************
***                            Destructor                              ***
*************************************************************************/
//deallocates dynamic memory and sets main pointers to NULL

cont_list::~cont_list()
{
  cont_info *temp;  //temporary pointer
  
  //deallocating dynamic memory in the date hash table
  for(int i=0;i<31;++i)
  {
    while(h_tbl_d[i])
    {
      temp = h_tbl_d[i];
      h_tbl_d[i]=h_tbl_d[i]->next;
      delete temp;
    }
  } 

  //deallocating dynamic memory in the name hash table    
  for(int i=0;i<NAME_MAX;++i)
  {
    while(h_tbl_n[i])
    {
      temp = h_tbl_n[i];
      h_tbl_n[i]=h_tbl_n[i]->next;
      delete temp;
    }
  } 
  
  //Setting main pointers to NULL
  delete h_tbl_d;
  delete h_tbl_n;
}




/*************************************************************************
***                             Hash by date                           ***
*************************************************************************/
//takes a date and returns an array index
//it takes the first two digits of the date(the day) and returns them as an index

int cont_list::hash_d(char *date)
{
  char day[3];
  int index;  
  
  day[0]=date[0];  //taking the first two digits
  day[1]=date[1];  // which are the day digits
  index = atoi(day); 
  
  //returning the results
  if (index<32 && index >0)
    return index-1;
  else
    return -1;
}


/*************************************************************************
***                             Hash by name                           ***
*************************************************************************/
//takes a name and returns an array index
//it adds the curresponding numbers of the first and last two letters of
//the name and returns the remainder of the sum divided by the prime number

int cont_list::hash_n(char *name)
{
  int i[4];
  int index;

  //taking first and last two letters
  i[0]=name[0];
  i[1]=name[1];
  i[2]=name[strlen(name)-1];
  i[3]=name[strlen(name)-2];

  index=(i[0]+i[1]+i[2]+i[3]) % NAME_MAX;  //adding and dividing

  //returning result
  if (index<NAME_MAX && index >=0)
    return index;
  else
    return -1;
}


/*************************************************************************
***                         Assign Data                                ***
*************************************************************************/
// Copys a call's information into a node

void cont_list::assign_data(cont_info *&ptr, char*name, char*phone, char*email, char*fax, char*date)
{
  ptr->name = new char[strlen(name)+1];
  ptr->phone = new char[strlen(phone)+1];
  ptr->email = new char[strlen(email)+1];
  ptr->fax = new char[strlen(fax)+1];
  ptr->date = new char[strlen(date)+1];

  strcpy(ptr->name, name);
  strcpy(ptr->phone, phone);
  strcpy(ptr->email, email);
  strcpy(ptr->fax, fax);
  strcpy(ptr->date, date);
}

/*************************************************************************
***                              Store                                 ***
*************************************************************************/
//stores a call's info into both the date table and the name table

int cont_list::store(char*name, char*phone, char*email, char*fax, char*date)
{
  int index;
  cont_info *cur;

  //a function to store information by caller's name into name table
  store_n(name, phone, email, fax, date);
  
  index = hash_d(date); //get index 
  if (index ==-1)   
    return 0;
  else 
  {
    if(h_tbl_d[index]==NULL)  //if head is null give it a node
    {
      h_tbl_d[index] = new cont_info;

      assign_data(h_tbl_d[index], name, phone, email, fax, date);
      h_tbl_d[index]->next = NULL;
    }
    else  //if head is not null add a node at the end of the chain
    {
      cur = h_tbl_d[index];
      while(cur->next)
        cur = cur->next;

      cur->next = new cont_info;
      cur = cur->next;

      assign_data(cur, name, phone, email, fax, date);
      cur->next = NULL;
    }
    return 1;
  }  
}

/*************************************************************************
***                        Store by name                               ***
*************************************************************************/
//stores data into name table by callers name

void cont_list::store_n(char*name, char*phone, char*email, char*fax, char*date)
{
  int index;
  cont_info *cur;

  index = hash_n(name); //get index

  if(h_tbl_n[index]==NULL)  //if head[index] is null give it a node
  {
    h_tbl_n[index] = new cont_info;
    assign_data(h_tbl_n[index], name, phone, email, fax, date);
    h_tbl_n[index]->next = NULL;
  }
  else  //if not add node to end of the chain
  {
    cur = h_tbl_n[index];
    while(cur->next)
      cur = cur->next;
    cur->next = new cont_info;
    cur = cur->next;
    assign_data(cur, name, phone, email, fax, date);
    cur->next = NULL;
  }
}


/*************************************************************************
***                        Retrieve by date                            ***
*************************************************************************/
//returns a pointer to a LLL holding information of a date

cont_info *cont_list::retrieve(char *date)
{
  int index;
  cont_info *temp, *head2, *cur2;   //head2 is the head of the LLL

  index = hash_d(date);  //get index
  if (index ==-1)
    return NULL;
  else
  {
    if(h_tbl_d[index]==NULL)  //if empty return failure
      return NULL;
    else
    { //copy all info at that date into a new LLL
      temp = h_tbl_d[index];
      head2 = new cont_info;

      assign_data(head2, temp->name, temp->phone, temp->email, temp->fax, temp->date);

      head2->next = NULL;
      cur2 = head2;
      temp=temp->next;

      while(temp)
      {
        cur2->next = new cont_info;
        cur2 = cur2->next;
    
        assign_data(cur2, temp->name, temp->phone, temp->email, temp->fax, temp->date);

        temp = temp->next;
        cur2->next=NULL;
      }
      return head2;  //return head of the new LLL
    }
  }
}


/*************************************************************************
***                        Retrieve by name                            ***
*************************************************************************/
//returns a pointer to a LLL holding records of all calls made by one person

cont_info *cont_list::retrieve_n(char *name)
{
  int index;
  cont_info *temp, *cur2;
  cont_info *head2 =NULL;

  index = hash_n(name);  //get index
  if (index ==-1)
    return NULL;
  else
  {
    if(h_tbl_n[index]==NULL)   //if empty return failure
      return NULL;
    else
    {  //copy all calls information made by "name" into a new LLL
      temp = h_tbl_n[index];
      while(temp)
      {
        if(strcmp(temp->name, name)==0)
        {
          if(!head2)
          {
            head2 = new cont_info;
            assign_data(head2, temp->name, temp->phone, temp->email, temp->fax, temp->date);
            head2->next = NULL;
            cur2 = head2;
          }            
          else
          {
            cur2->next = new cont_info;
            cur2 = cur2->next;
            assign_data(cur2, temp->name, temp->phone, temp->email, temp->fax, temp->date);
            cur2->next=NULL;
          }
        }
        temp = temp->next;
      }
      return head2; //return head to the new LLL
    }
  }
}


/*************************************************************************
***                               ReMove                               ***
*************************************************************************/
//takes a date and removes all calls made on that date

int cont_list::remove(char *date)
{
  int index;
  cont_info *temp;
  
  index = hash_d(date); //get index
   
  if(index == -1)
    return 0;
  else
  {
    if(h_tbl_d[index]==NULL)  //if empty returns failure
      return 0;
    else
    {  //deallocating memory
      while(h_tbl_d[index])
      {
        temp = h_tbl_d[index];
        h_tbl_d[index] = h_tbl_d[index]->next;
        delete temp;
      }
      temp = NULL; 
      return 1;   //returns success     
    }
  } 
}

