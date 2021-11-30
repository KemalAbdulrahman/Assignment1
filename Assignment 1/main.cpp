//
//  main.cpp
//  Assignment 1
//
//  Created by Kemal Abdulrahman on 2/14/20.
//  Copyright © 2020 Kemal Abdulrahman. All rights reserved.
//

#include<iostream>
#include<math.h>
using namespace std;

class changeMaker{
private:
   int nickles;
   int dimes;
   int quarters;
   int ones;
   int fives;
   float price;
   int price_ones;
   int price_cents;
   bool illegal_price;
   char user_deposit;
   int change_cents;
   string cont;

public:
   changeMaker(){
      nickles = 25;
      dimes = 25;
      quarters = 25;
      ones = 0;
      fives = 0;
      price = 0;
      illegal_price = false;
      change_cents = 0;
   };

   changeMaker(int n, int d, int q){
      nickles = n;
      dimes = d;
      quarters = q;
   };

   inline void printMenu(){
      cout<<"Menu for deposits:"<<endl;
      cout<<"\t 'n' - deposit a nickel"<<endl;
      cout<<"\t 'd' - deposit a dime"<<endl;
      cout<<"\t 'q' - deposit a quarter"<<endl;
      cout<<"\t 'o' - deposit a one dollar bill"<<endl;
      cout<<"\t 'f' - deposit a five dollar"<<endl;
      cout<<"\t 'c' - Cancel the purchase"<<endl;
   };

   bool is_multiple5(int val){
      while(val > 0){
         val -= 5;
         if(val == 0) return true;
      }
      return false;
   }

   inline void greeting(){
      cout<<"Welcome to the vending machine change maker program"<<endl;
      cout<<"Change Maker initalized"<<endl;
      cout<<"Stock Contains:"<<endl;
      cout<<"\t"<<nickles<<" nickles"<<endl;
      cout<<"\t"<<dimes<<" dimes"<<endl;
      cout<<"\t"<<quarters<<" quarters"<<endl;
      cout<<"\t"<<ones<<" ones"<<endl;
      cout<<"\t"<<fives<<" fives"<<endl;
   }

   inline void user_input(){
      do{
         if(illegal_price == true) cout<<"Illegal price: Must be a non-negative multiple of 5 cents"<<endl;
         cout<<"Enter the purchase Price: "<<endl;
         cin>>price;
         illegal_price = true;
      }while(!is_multiple5(price*100));
   }

   inline void payment_due(){
      price_ones = (int)price;
      price_cents = (price * 100) - (price_ones*100);
      //if(price_cents < 0) price_cents += 100;
   }

   inline void payment_due_print(){
      if(price_ones && price_cents) cout<<price_ones<<" dollars and "<<price_cents<<" Cents"<<endl;
      else if(price_ones && !price_cents) cout<<price_ones<<" dollars"<<endl;
      else cout<<price_cents<<" cents"<<endl;
   }
   inline void deposit(){
      bool check;
      do{
         payment_due_print();
         cout<<"Indicate your deposit: "<<endl;
         cin>>user_deposit;
         switch(user_deposit){
            case 'n': {
               if(price_cents >= 5) price_cents -= 5;
               else if(price_cents < 5 && price_ones > 0){
                  price_ones--;
                  price_cents += 100;
                  price_cents -= 5;
               }
            }
               break;
            case 'd': {
               if(price_cents >= 10) price_cents -= 10;
               else if(price_cents < 10 && price_ones > 0){
                  price_ones--;
                  price_cents += 100;
                  price_cents -= 10;
               }
            }
               break;
            case 'q':{
               if(price_cents >= 25) price_cents -= 25;
               else if(price_cents < 25 && price_ones > 0){
                  price_ones--;
                  price_cents += 100;
                  price_cents -= 25;
               }
            }
               break;
            case 'o': {
               if(price_ones >= 1) price_ones--;
               else if(price_ones < 1 && price_cents > 0){
                  change_cents = 100 - price_cents;
                  price_cents = 0;
               }

            }
               break;
            case 'f': {
               if(price_ones >= 5) price_ones -= 5;
               else if(price_ones < 5 && price_cents > 0){
                  price_cents += (price_ones * 100);
                  price_ones = 0;
                  change_cents += (500 - price_cents);
                  price_cents = 0;
               }
            }
               break;
            case 'c': break;
            default: {
               cout<<"Illegal Selection: "<<user_deposit<<endl;
            }
               break;
         }
         check = (user_deposit != 'c') && (price_ones != 0 && price_cents != 0);
      }while(check);
   }


   void change(){
      int change_nickles=0, change_dimes=0, change_quarters=0;

      change_cents += price_cents;

      while(change_cents && (quarters && dimes && nickles)){
         while(quarters > 0 && change_cents >= 25){
            change_cents -= 25;
            quarters--;
            change_quarters++;
         }

         while(dimes>0 && change_cents >= 10){
            change_cents -= 10;
            dimes--;
            change_dimes++;
         }

         while(nickles>0 &&  change_cents >= 5){
            change_cents -= 5;
            nickles--;
            change_nickles++;
         }
      }

      cout<<"Please take the change below"<<endl;

      if(change_quarters && change_dimes  && change_nickles){
         cout<<change_quarters<<" quarters"<<endl;
         cout<<change_dimes<<" dimes"<<endl;
         cout<<change_nickles<<" nickles"<<endl;
      }

      else if(!change_quarters && !change_dimes){
         cout<<change_nickles<<" nickles"<<endl;
      }
      else if(!change_quarters && !change_nickles){
         cout<<change_dimes<<" dimes"<<endl;
      }
      else if(!change_dimes && !change_nickles){
         cout<<change_quarters<<" quarters"<<endl;
      }
      else if(!change_quarters){
         cout<<change_dimes<<" dimes"<<endl;
         cout<<change_nickles<<" nickles"<<endl;
      }
      else if(!change_dimes){
         cout<<change_quarters<<" quarters"<<endl;
         cout<<change_nickles<<" nickles"<<endl;
      }
      else{
         cout<<change_quarters<<" quarters"<<endl;
         cout<<change_dimes<<" dimes"<<endl;
      }

      if(nickles == 0 && dimes == 0 && quarters == 0 && change_cents > 0){
         cout<<"See store manager for the remaining refund"<<endl;
      }


   }
   void run(){
      do{
         greeting();
         user_input();
         printMenu();
         payment_due();
         deposit();
         change();
         cout<<"Do you want to continue? "<<endl;
         cin>>cont;
      }while(cont == "yes");

   }


};



int main(){

   changeMaker maker;
   maker.run();
   return 0;
}

