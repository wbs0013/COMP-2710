// name: Blake Schilleci, wbs0013
// partner: Will Bianca, wcb0020
// filename: hw2.cpp
// due date: 09/07/18
// collaboration: We did not receive any outside help.
// problem: determine how many months it takes to pay off a loan.

#include <iostream>
#include <iomanip>
using namespace std;

int main() {

   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2); // this sets the decimal format to be that of money.

   double loan_amount, interest_rate, monthly_payment, annual_interest;
   int month;
  
   cout << "Loan Amount: ";
   cin >> loan_amount;

   cout << "Interest Rate (% per year): ";
   cin >> interest_rate;

   cout << "Monthly Payments: ";
   cin >> monthly_payment;

   cout << "******************************************************************" << endl;
   cout << "        Ammortization Table" << endl;
   cout << "******************************************************************" << endl;
   cout << left << setw(8) << "Month";
   cout << left << setw(12) << "Balance"; 
   cout << left << setw(12) << "Payment";
   cout << left << setw(12) << "Rate";   
   cout << left << setw(12) << "Interest";
   cout << left << setw(8) << "Principal" << endl;

   
   interest_rate = interest_rate/100;
   interest_rate = interest_rate/12;
   
   double balance = loan_amount;
   double interest = 0.0;
   double principal = 0.0;
   double total = 0.0;
   month = 0;
   
   bool canPay; // boolean value to check if total is more than the interest.
   interest = balance * interest_rate;

   if (monthly_payment <= interest) {
      cout << "\nYou will need a higher monthly payment, otherwise you will not be able to pay off the loan" << endl;
      canPay = false;
      
   }
      
   else {
      canPay = true;
   }
         
   if (canPay) {
      
      // gives the first line of the ammortization table.
   
      cout << left << setw(8) << "0";
      cout << '$' << left << setw(11) << loan_amount; 
      cout << left << setw(12) << "N/A";
      cout << left << setw(12) << "N/A";   
      cout << left << setw(12) << "N/A";
      cout << left << setw(8) << "N/A" << endl;    
    
   
      while (balance > 0.0) {
      
      // creates a loop to iterate through the payments until the loan is paid off.
      
         month++;
         interest = balance * interest_rate;
         annual_interest += interest;
      
         total = total + interest;
      
         if (monthly_payment > (balance + interest)) {
         
            monthly_payment = balance + interest;
         
         }
      
         principal = monthly_payment - interest;
      
         balance = balance - principal;
      
      // this is the spacing for the output.
         
         cout << left << setw(8) << month;
         cout << '$' << left << setw(11) << balance; 
         cout << '$' << left << setw(11) << monthly_payment;
         cout << left << setw(12) << interest_rate * 100;   
         cout << '$' << left << setw(11) << interest;
         cout << '$' << left << setw(8) << principal << endl;
      
      
      }
   
      cout << "******************************************************************" << endl;
      cout << "\n";
      cout << "It takes " << month << " months to pay off the loan." << endl;
      cout << "Total interest paid is: $" << annual_interest;
   }
   
}






