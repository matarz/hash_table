/* 
   Author: Zakaria Almatar
   Date: 07/31/09
   Class: CS163
   Assignment: Program#3

   Purpose: The progarm purpose is to keep a record of someone's calls 
            based on date or callers name. 
*/
/*
   File name: main.cpp
   Contains: This file has the client program and all interactions with
             the user(s)
*/



#include <cstdlib>
#include <string.h>
#include <iostream>
#include "header.h"
using namespace std;




//user's functions
int u_store(cont_list &cnts);      //store
int u_retrieve(cont_list &cnts);   //check
int u_remove(cont_list &cnts);     //remove
int main_menu();                   //main menu



int main()
{
  int choice;
  cont_list contacts;
  cont_info *temp;


  do 
  {
    choice = main_menu();  //get the user's choice

	if(choice == 1)  // Store
	{ 
      choice=u_store(contacts);
	}	 
    else if(choice ==2) // Retrieve
	{
      choice=u_retrieve(contacts);
	}	 
    else if(choice == 3)  // Remove
	{ 
      choice= u_remove(contacts);
	}	 
	else if(choice == 4)  // quit
	{ 
      cout<<"\nQuitting...";
      choice= 5;
	}	 
  }while(choice ==0); 

}


/*************************************************************************
***                         User's remove                              ***
*************************************************************************/
//user's funtion

int u_remove(cont_list &cnts)
{

  int result;
  char date[15];
  
  cin.ignore();
  cout<<"\nEnter the call's date(format: dd/mm/yy): ";
  cin.get(date,15);
  cin.ignore();   
   
  result=cnts.remove(date);
  
  if(result==1)
    cout<<"\nRemoval was successful.";
  else
    cout<<"\nRemoval failed. Make sure the date is in the right format.";
    
  return 0;
}

/*************************************************************************
***                       User's retrieve                              ***
*************************************************************************/
//user's funtion

int u_retrieve(cont_list &cnts)
{
  cont_info *temp, *temp2;
  int choice;
  char date[15];
  char name[50];
  

  cout<<"\nCheck calls by: ";
  cout<<"\n   1- Date of the call. ";
  cout<<"\n   2- Caller's name. "<<endl;
  cin>>choice;
  
  if(choice ==1)
  {
    cin.ignore();
    cout<<"\nEnter the call's date(format: dd/mm/yy): ";
    cin.get(date,15);
    cin.ignore();   
    temp = cnts.retrieve(date);
  }
  else
  {
    cin.ignore();
    cout<<"\nEnter the caller's name: ";
    cin.get(name,50);
    cin.ignore();   
    temp = cnts.retrieve_n(name);
  }
    temp2=temp;  
  
    if(temp == NULL)  
      cout<<"No matches were found.";
    else
    {
      if(choice ==1)
        cout<<"\nOn "<<date<<" you were called by:"<<endl;
      else  
        cout<<"\nCalls received by"<<name<<" :"<<endl;
    while(temp)
    {
      cout<<endl;
      cout<<"Name: "<<temp->name<<endl;
      cout<<"Phone: "<<temp->phone<<endl;
      cout<<"Email: "<<temp->email<<endl;
      cout<<"Fax: "<<temp->fax<<endl;
      cout<<"Date: "<<temp->date<<endl;
      cout<<"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
      temp=temp->next;
    }
    while(temp2)
    {
      temp=temp2;
      temp2=temp2->next;            
      delete temp;
    }
    temp =NULL;
    temp2=NULL;  
  }
  return 0;
}



/*************************************************************************
***                          User's store                              ***
*************************************************************************/
//user's funtion

int u_store(cont_list &cnts)
{
  int result;
  char name[50];
  char phone[20];
  char email[50];
  char fax[20];
  char date[15];

  cin.ignore();
  
  cout<<"\nEnter the contact's name: ";
  cin.get(name,50);
  cin.ignore();
  
  cout<<"\nEnter the contact's phone number: ";
  cin.get(phone,20);
  cin.ignore();
  
  cout<<"\nEnter the contact's email address: ";
  cin.get(email,50);
  cin.ignore();
  
  cout<<"\nEnter the contact's fax number: ";
  cin.get(fax,20);
  cin.ignore();
  
  cout<<"\nEnter the call's date (format:dd/mm/yy): ";
  cin.get(date,15);
  cin.ignore();
    
  result = cnts.store(name, phone, email, fax, date);
  if (result==1)
    cout<<"\nInformation was stored successfully";
  else
    cout<<"\n No information was stored. Make sure the date is in the right format";

  return 0;
}





/*************************************************************************
***                       Main menu function                           ***
*************************************************************************/
// This function's purpose is to get the user's choice and return it. 

int main_menu()
{

  int choice;  // to hold the user's choice
  do
  { 
    cout <<"\n\n  +---------------------------------------------+" <<endl;
    cout <<"     1- Store a call's information." <<endl;
    cout <<"     2- Check who called on a certain date." <<endl;
    cout <<"     3- Remove information form a certain date." <<endl;
    cout <<"     4- Quit." <<endl;
    cout <<"  +---------------------------------------------+" <<endl;
    cout << endl;

    cout <<"Please, enter the number of your choice: "; 
    cin>>choice;    //get choice

  }while (choice<1 || choice>4);

 return choice;
}




