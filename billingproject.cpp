//----------------HEADER FILES REQUIRED FOR THE PROGRAMS-------------------


#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>   // this header file  contains the functions to manipulate  the input and output format  i.e setfill,setiosflags(sets the specified flags)
 using namespace std;   // to include the std function such as cout,cin,endl
//global variable declaration
  int k=7,r=0,flag=0;
  COORD coord = {0, 0};
                             //Header File : windows.h---------
                             //Function : gotoxy
                             //Return Type : Void
 void gotoxy(int x, int y)
  {
    COORD coord;  
    coord.X = x;       // Create a COORD structure and fill in its members.     
                        //This specifies the new position of the cursor that we will set.
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);   //Obtain a handle to the console screen buffer.
                                                                    // (we're just using the standard console, so we can use STD_OUTPUT_HANDLE
                                                                    // in conjunction with the GetStdHandle() to retrieve the handle.)
                                                                    // Note that because it is a standard handle, we don't need to close it.
  }
  struct date           //created a structure of name date
   {
          int mm,dd,yy;    ////structure members
   };

ofstream fout;  //derived from the fstream class and enables user to access files and read data from them
ifstream fin;  //derived from the fstream class and enables user to access files and write data to them

class item           
{
   int itemno;           //variable of type int itemno
   char name[25];        //character array to store the name of the items
   date d;               //structure variables as d of type date
  public:                //declaring the functions as public
  void add()
   {
     cout<<"\n\n\tItem No: ";     //enter the item no
     cin>>itemno;
     cout<<"\n\n\tName of the item: ";      //entering the name of the item
                                            //gets(name);
     cin>>name;
    //gets(name);
     cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";  //enter the date in mm-dd-yyyy format
     cin>>d.mm>>d.dd>>d.yy;
   }
  void show()                           //function to show the details
   {
     cout<<"\n\tItem No: ";
     cout<<itemno;
     cout<<"\n\n\tName of the item: ";      //print the name of the item
     cout<<name;
     cout<<"\n\n\tDate : ";
     cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;       // print the date in the given format
   }
  void report()                //function to show the report
   {
     gotoxy(3,k);               // to place the cursor at x=3, y=k(i.e 7)
     cout<<itemno;
     gotoxy(13,k);              //to place the cursor at x=13, y=k(i.e 7) "Declared as global variable
     puts(name);
   }
  int retno()
   {
    return(itemno);            //returning the itemno to the function

   }

};                             

class amount: public item        //derived class  "USING THE CONCEPT OF INHERITANCE"  sub class amount inheriting the features of base class
{
   float price,gst,gross,dis,netamt;
   int qty;
   public:                                   
          void add();             //declaring the function as public to make it acessible anywhere
          void show();
          void report();           //declaring the function as public to make it acessible anywhere
          void calculate();
          void pay();
   float retnetamt()               //if the amount is in float
    {
      return(netamt);              //then return the amount in float retnetamt()
    }
 }amt;                             //creating a class variable

 void amount::add()                 ///using the scope resolution operator as we are using the function outside the class
  {
    item::add();
    cout<<"\n\n\tPrice: ";
    cin>>price;
    cout<<"\n\n\tQuantity: ";
    cin>>qty;  //enter the quantity of the item
    cout<<"\n\n\tenter the state gst: ";
    cin>>gst;  //enter the gst
    cout<<"\n\n\tDiscount percent: ";
    cin>>dis;    //enter the discount percent
    calculate();   //calling the calculate function
    fout.write((char *)&amt,sizeof(amt));    // writing to the file
    fout.close();
  }
  void amount::calculate()       ///susing the scope resolution operator as we are using the calculate function outside the clas
    {


       gross=price+(price*(gst/100));
       netamt=qty*(gross-(gross*(dis/100)));    //calculating the net amount   after deducting the discount on the  gross value
    }
  void amount::show()                   //using the scope resolution operator as we are using the  show function outside the class
   {
       fin.open("itemstore.dat",ios::binary);   //opening the file in the read mode in "BINARY FORMAT"
       fin.read((char*)&amt,sizeof(amt));       ///reading the details from the file
       item::show();
       cout<<"\n\n\tNet amount: ";
       cout<<netamt;                      //entering the net amount
       fin.close();                       //closing the file
   }

  void amount::report()                    //using the scope resolution operator as we are using the  report function outside the class
   {
       item::report();
       gotoxy(23,k);                       ////this goto x,y function is used to take the cursor at x=23 and y=k i.e 7
       cout<<price;                        ///printing the price of the item at the co-ordinate (23,k)
       gotoxy(33,k);
       cout<<qty;
        gotoxy(44,k);
       cout<<gst;
       gotoxy(54,k);
       cout<<dis;
       gotoxy(64,k);                       //this goto x,y function is used to take the cursor at x=64 and y=k i.e 7 
       cout<<netamt;                       //printing the price of the item at the co-ordinate (64,k)
       k=k+1;                              //incrementing the value of k
     if(k==50)
      {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        getch();
        k=7;
        system("cls");                     //clearing the system
        gotoxy(30,3);                      //this goto x,y function is used to take the cursor at x=30 and y=3  
        cout<<" ITEM DETAILS ";
        cout<<"NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";       //headings
        gotoxy(44,5);          //taking the cursor position to the co-ordinate (44,5)
        cout<<"SGST";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(64,5);
        cout<<"NET AMOUNT";
    }
}

  void amount::pay()
 {
       show();
       cout<<"\n\n\n\t\t*********************************************";
       cout<<"\n\t\t                 DETAILS                  ";
       cout<<"\n\t\t*************************************************";
       cout<<"\n\n\t\tPRICE                     :"<<price;                  // displaying the details of the items stored on file
       cout<<"\n\n\t\tQUANTITY                  :"<<qty;
       cout<<"\n\t\tTAX PERCENTAGE              :"<<gst;
       cout<<"\n\t\tDISCOUNT PERCENTAGE         :"<<dis;
       cout<<"\n\n\n\t\tNET AMOUNT              :Rs."<<netamt;
       cout<<"\n\t\t*********************************************";
 }
 
int main()                            // main function
 {
       cout.setf(ios::fixed);
       cout.setf(ios::showpoint);
       cout<<setprecision(2);
       fstream tmp("temp.dat",ios::binary|ios::out);
menu:
     system("cls");
     gotoxy(25,2);
     cout<<"ACHARYA SUPERMARKET BILLING SYSTEM ";
     gotoxy(25,3);
     cout<<"====================================\n\n";
     cout<<"\n\t\t1.Bill Report\n\n";
     cout<<"\t\t2.Add/Remove/Edit Item\n\n";
     cout<<"\t\t3.Show Item Details\n\n";
     cout<<"\t\t4.Exit\n\n";
     cout<<"\t\tPlease Enter Required Option: ";
     int ch,ff;                   //declaring the variables of type int  ch for choice of the user 
     float gtotal;                //declaring the variable  gtotal for grandtotal
     cin>>ch;                     // taking the choice of the user as the input
     switch(ch)                    ////I am using nested switch here
{
     case 1: 
             ss:
            system("cls");                //clear the screen
            gotoxy(25,2);
            cout<<"Bill Details";          //print the bill details
            gotoxy(25,2);
            cout<<"================\n\n";
            cout<<"\n\t\t1.All Items\n\n";
            cout<<"\t\t2.Back to Main menu\n\n";
            cout<<"\t\tPlease Enter Required Option: ";
            int cho;
            cin>>cho;
            if(cho==1)
              {
                system("cls");
                gotoxy(30,3);
                cout<<" BILL DETAILS ";
                gotoxy(3,5);
                cout<<"ITEM NO";
                gotoxy(13,5);
                cout<<"NAME";         //heading or label to print the name
                gotoxy(23,5);         /////taking the cursor position to the co-ordinate (23,5)
                cout<<"PRICE";
                gotoxy(33,5);
                cout<<"QUANTITY";
                gotoxy(44,5);
                cout<<"SGST %";
                gotoxy(54,5);
                cout<<"DISCOUNT %";
                gotoxy(64,5);
                cout<<"NET AMOUNT";
               fin.open("itemstore.dat",ios::binary);         //opening the file in the read mode
               if(!fin)                                       //if not equal to file
                 {
                   cout<<"\n\nFile Not Found...";              //file not found
                   goto menu;}
                   fin.seekg(0);                    //seekg is a function in the iostream library (part of the standard library) that allows us to seek to an arbitrary position in a file. 
                   gtotal=0;
                  while(!fin.eof())                 //while it has not reached the end of the file
                    {
                      fin.read((char*)&amt,sizeof(amt));    //reading from the file
                      if(!fin.eof())
                       {
                         amt.report();
                         gtotal+=amt.retnetamt();           //calculating the grandtotal
                         ff=0;                              //re-intializing ff=0;
                       }
                if(ff!=0) gtotal=0;                        //if ff not equal to 0 then grand total equal to 0
           }
                gotoxy(17,k);
                cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;   //printing the grand total at x=17, y=7
                 getch();
                fin.close();                                //closing the file
          }
        if(cho==2)              //If the users  choice is 2 then go to the menu
          {
            goto menu;
          }
            goto ss;
case 2:
        db:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Editor";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t1.Add Item Details\n\n";
        cout<<"\t\t2.Edit Item Details\n\n";
        cout<<"\t\t3.Delete Item Details\n\n";
        cout<<"\t\t4.Back to Main Menu ";
        int apc;
        cin>>apc;
       switch(apc)      //started using nested switch
         {
           case 1:
                   fout.open("itemstore.dat",ios::binary|ios::app);
                   amt.add();
                   cout<<"\n\t\tItem Added Successfully!";   //item added successfully
                   getch();
                   goto db;    //then go to label db

          case 2:
                  int ino;       //declaring a variable ino for item no of type int
                  flag=0;
                  cout<<"\n\n\tEnter Item Number to be Edited :";
                  cin>>ino;     //enter the item number to be edited
                  fin.open("itemstore.dat",ios::binary);     //open the file in binary format
                  fout.open("itemstore.dat",ios::binary|ios::app);
                    if(!fin)    //check if  the file is present or not  
                     {
                     cout<<"\n\nFile Not Found...";
                     goto menu;
                   }
                   fin.seekg(0);     //seekg is a function in the iostream library (part of the standard library) that allows you to seek to an arbitrary position in a file.
                   r=0;
                   while(!fin.eof())     //while it has not reached to the end of file
                    {
                       fin.read((char*)&amt,sizeof(amt));   //again reading from the file
                       if(!fin.eof())                  //IF WE THEN HAVE NOT REACHED TO THE END OF THE FILE
                        {
                          int x=amt.item::retno();   //RETURN THE AMOUNT IN THE VARIABLE X  " WE ARE ACESSING THE CLASS ITEM USING (.) OPERATOR
                          if(x==ino)                 //CHECKING THAT THE ENTERED ITEM NO IS PRESENT OR NOT
                           {
                             flag=1;                  //IF PRESENT SET THE FLAG TO 1 I.E FLAG=1;
                             fout.seekp(r*sizeof(amt));
                             system("cls");      //CLEAR THE Screen
                             cout<<"\n\t\tCurrent Details are\n";
                             amt.show();    //ACESSING THE SHOW FUNCTION
                             cout<<"\n\n\t\tEnter New Details\n";
                             amt.add();      //calling the add function to add the new details
                             cout<<"\n\t\tItem Details editted";
                           }
                   }r++;    // increment r by 1
              }
    if(flag==0)  // if flag==0 means the entered item number does not exist
      {
           cout<<"\n\t\tItem No does not exist...Please Retry!";
           getch();
           goto db;
      }
           fin.close();    //close the file
           getch();
           goto db;

case 3:
        flag=0;
        cout<<"\n\n\tEnter Item Number to be deleted :";
        cin>>ino;      //enter the item number to be deleted
        fin.open("itemstore.dat",ios::binary);    //open the file in read mode
        if(!fin)      // if the file is not present print the message file not found
          {
            cout<<"\n\nFile Not Found...";
            goto menu;      //go to menu
           }
     //fstream tmp("temp.dat",ios::binary|ios::out);
       fin.seekg(0);     //seekg is a function in the iostream library (part of the standard library) that allows you to seek to an arbitrary position in a file. 
                         //seekg() is used to move the get pointer to a desired location with respect to reference point
      while(fin.read((char*)&amt, sizeof(amt)))  //it will read the data from the file in to an object(&obj represent the memory address)
                                                 // (char*)&amt - it means i am type casting  &amt in to a character pointer
                                                 // fin.read is the function call invoked by the fin object
       {
          int x=amt.item::retno();
          if(x!=ino)          //if the item no is not equal to entered item number then
          tmp.write((char*)&amt,sizeof(amt));   //write on to a different file i.e temporary file
          else
           {
          flag=1;      //else set the flag to 1 i.e flag=1
      }
}
  fin.close();  //close the file
  tmp.close();
  fout.open("itemstore.dat",ios::trunc|ios::binary);
  fout.seekp(0);
  tmp.open("temp.dat",ios::binary|ios::in);
  if(!tmp)
    {
          cout<<"Error in File";    //if the file is unable to open then print error in file
          goto db;
    }
       while(tmp.read((char*)&amt,sizeof(amt)))
       fout.write((char*)&amt,sizeof(amt));
       tmp.close();    //close the temporary file
       fout.close();
       if(flag==1)
       cout<<"\n\t\tItem Succesfully Deleted";   // if the flag is set to 1 item succesfully deleted
       else if (flag==0)
       cout<<"\n\t\tItem does not Exist! Please Retry";   //otherwise please retry else item does not exist
       getch();
       goto db;
case 4:
        goto menu;
        default: cout<<"\n\n\t\tWrong Choice!!! Retry";
        getch();
        goto db;
}
case 3:
       system("cls");
       flag=0;
       int ino;
       cout<<"\n\n\t\tEnter Item Number :";
       cin>>ino;
       fin.open("itemstore.dat",ios::binary);
       if(!fin)
        {
          cout<<"\n\nFile Not Found...\nProgram Terminated!";
          goto menu;
        }
         fin.seekg(0);
         while(fin.read((char*)&amt,sizeof(amt)))
          {
            int x=amt.item::retno();
            if(x==ino)
             {
               amt.pay();
               flag=1;
               break;
             }
       }
      if(flag==0)    ///if flag==0 item does not exist
      cout<<"\n\t\tItem does not exist....Please Retry!";
      getch();
      fin.close();     //close the file
      goto menu;
case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
         {
           gotoxy(12,20);
           system("cls");
           cout<<"************************** THANKS **************************************";   //print the message thanks to the user
           getch();
           exit(0);
         }
      else if((yn=='N')||(yn=='n'))   //checking what character the user has pressed
      goto menu;                             //if he or she has pressed y or n then go to menu
      else
      {
           goto menu;
      }
      default:cout<<"\n\n\t\tWrong Choice....Please Retry!";  //default wrong choice
      getch();
      goto menu;  //go to menu
    }
   return 0;       //return as main is of type int
}
