// name: Blake Schilleci, wbs0013
// partner: Will Bianca, wcb0020
// filename: hw1.cpp
// due date: 08/31/18
// collaboration: We did not receive any outside help.
// problem: determine how much diet soda one can drink without
//       dying as a result.

#include <iostream>
using namespace std;

const double RATE = 0.001;

int main() {


   double lethal, weight_mouse, weight_human, amount;

   cout << "What is the amount of artificial sweetener needed to kill a mouse: " << endl;
   cin >> lethal;

   cout << "\nWhat is the weight of the mouse: ";
   cin >> weight_mouse;
   
   cout << "\nWhat is the weight of the dieter: ";
   cin >> weight_human;
   
   amount = ((lethal/weight_mouse)*(weight_human/RATE));
   cout << "\nYou can drink " << amount << " diet soda without dying as a result.";
   

   return 0;

}