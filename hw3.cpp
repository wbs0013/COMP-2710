// name: Blake Schilleci, wbs0013
// partner: Will Bianca, wcb0020
// filename: hw3.cpp
// due date: 09/14/18
// collaboration: We did not receive any outside help.
// problem: determine the best strategy in a shooting simulation.

# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>
# include <cstdlib>
using namespace std;

//GLOBAL CONSTANTS
const int NUMBER_OF_DUELS = 10000;
const int AARON_PROBABILITY = 33; 
const int BOB_PROBABILITY = 50; 
const int CHARLIE_PROBABILITY = 100;

//Win amounts
int a_wins = 0;
int b_wins = 0;
int c_wins = 0;




/*************** FUNCTION PROTOTYPES ******************/

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);

/* Input: A_alive indicates whether Aaron is alive
B_alive indicates whether Bob is alive
C_alive indicates whether Charlie is alive
Return: true if at least two are alive
otherwise return false
*/

void Aaron_shoots1(bool& B_alive, bool& C_alive);
/* Strategy 1: Use call by reference
* Input: B_alive indicates whether Bob alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change B_alive into false if Bob is killed.
* Change C_alive into false if Charlie is killed.
*/
void Bob_shoots(bool& A_alive, bool& C_alive);
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change C_alive into false if Charlie is killed.
*/
void Charlie_shoots(bool& A_alive, bool& B_alive);
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
* B_alive indicates whether Bob is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change B_alive into false if Bob is killed.
*/
void Aaron_shoots2(bool& B_alive, bool& C_alive);
/* Strategy 2: Use call by reference
* Input: B_alive indicates whether Bob alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change B_alive into false if Bob is killed.
* Change C_alive into false if Charlie is killed.
*/

void strat1(void);
/* No input.
 * Return: Change global variables a_wins, b_wins, and c_wins based on who wins.
 * Uses Strategy 1 */
 
void strat2(void);
/* No input.
 * Return: Change global variables a_wins, b_wins, and c_wins based on who wins.
 * Uses Strategy 2 */

/*************** TEST CASES ****************/

void test_at_least_two_alive(void);
/* This is a test driver for at_least_two_alive() */

void test_Aaron_shoots1(void);
/* This is a test driver for Aaron_shoots1 */

void test_Bob_shoots(void);
/* This is a test driver for Bob_shoots */

void test_Charlie_shoots(void);
/* This is a test driver for Charlie_shoots */

void test_Aaron_shoots2(void);
/* This is a test driver for Aaron_shoots */




int main() {

   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(2);
   srand(time(0)); //Set random seed
   cout << "***** Welcome to Puzzlevania's Shooting Simulator *****\n\n";


   test_at_least_two_alive();
   cout << "Press any key to continue...";
   cin.ignore().get(); //Pause command for Linux terminal
         
   test_Aaron_shoots1();
   cout << "\nPress any key to continue...";
   cin.ignore().get(); //Pause command for Linux terminal
   
   test_Bob_shoots();
   cout << "\nPress any key to continue...";
   cin.ignore().get(); //Pause command for Linux terminal
   
   test_Charlie_shoots();
   cout << "\nPress any key to continue...";
   cin.ignore().get(); //Pause command for Linux terminal
   
   test_Aaron_shoots2();
   cout << "\nPress any key to continue...";
   cin.ignore().get(); //Pause command for Linux terminal
   
   cout << "\nReady to test strategy 1 (run 10000 times):\n";
   cout << "\nPress any key to continue...";
   cin.ignore().get(); //Pause command for Linux terminal
   cout << "...\n...\n...\n";
   
   // Testing Strategy 1
   
   int duelCount = 0;
   while (duelCount < NUMBER_OF_DUELS) {
      strat1();
      duelCount++;
   }
   
   double a_percentage = (double) a_wins / (double) NUMBER_OF_DUELS;
   double b_percentage = (double) b_wins / (double) NUMBER_OF_DUELS;
   double c_percentage = (double) c_wins/ (double) NUMBER_OF_DUELS;
   
   int a_wins_Strat1 = a_wins; //Save a_wins to compare to strat 2
   cout << "Aaron won " << a_wins << "/" << NUMBER_OF_DUELS << " duels or " 
       << a_percentage * 100 << "%\n";
   cout << "Bob won " << b_wins << "/" << NUMBER_OF_DUELS << " duels or "
       << b_percentage * 100 << "%\n";
   cout << "Charlie won " << c_wins << "/" << NUMBER_OF_DUELS << " duels or "
       << c_percentage * 100 << "%\n\n";
       
   cout << "Ready to test strategy 2 (run 10000 times):\n";
   cout << "\nPress any key to continue...";
   cin.ignore().get(); //Pause command for Linux terminal
   cout << "...\n...\n...\n";
	
   //reset duel counts and wins
   duelCount = 0;
   a_wins = 0;
   b_wins = 0;
   c_wins = 0;
  
  // Testing Strategy 2
  
   while (duelCount < NUMBER_OF_DUELS) {
      strat2();
      duelCount++;
   }
   
   a_percentage = (double) a_wins / (double) NUMBER_OF_DUELS;
   b_percentage = (double) b_wins / (double) NUMBER_OF_DUELS;
   c_percentage = (double) c_wins/ (double) NUMBER_OF_DUELS;
   cout << "Aaron won " << a_wins << "/" << NUMBER_OF_DUELS << " duels or " 
       << a_percentage * 100 << "%\n";
   cout << "Bob won " << b_wins << "/" << NUMBER_OF_DUELS << " duels or "
       << b_percentage * 100 << "%\n";
   cout << "Charlie won " << c_wins << "/" << NUMBER_OF_DUELS << " duels or "
       << c_percentage * 100 << "%\n";	
		 
	//Compare strategies
   if (a_wins > a_wins_Strat1) {
      cout << "Strategy 2 is better than strategy 1\n";
   }
   else if (a_wins < a_wins_Strat1) {
      cout << "Strategy 1 is better than strategy 2\n";
   }
   else {
      cout << "The strategies have the same outcomes\n";
   }
}

// FUNCTION DEFINITIONS
/* Implementation of at_least_two_alive() */

bool at_least_two_alive(bool a_alive, bool b_alive, bool c_alive) {

   if ((a_alive && b_alive) || (b_alive && c_alive) || (c_alive && a_alive)) {
      return true;
   }
   else {
      return false;
   }

}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
   int shoot_target_result;
   shoot_target_result = rand()%100;
   if (shoot_target_result <= 33) {
   	//Aim at the most accurate shooter
      if (C_alive) {
         C_alive = false;
      }
      else {
         B_alive = false;
      }
   }
}

void Bob_shoots(bool& A_alive, bool& C_alive) {
   int shoot_target_result;
   shoot_target_result = rand()%100;
   if (shoot_target_result <= 50) {
      if (C_alive) {
         C_alive = false;
      }
      else {
         A_alive = false;
      }
   }
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {

   if (B_alive) {
      B_alive = false;
   }
   else {
      A_alive = false;
   }
}

void Aaron_shoots2(bool& B_alive, bool& C_alive) {
   int shoot_target_result;
   if (!B_alive || !C_alive) {
      shoot_target_result = rand()%100;
      if (shoot_target_result <= 33) {
         if (C_alive) {
            C_alive = false;
         }
         else {
            B_alive = false;
         }
      }
   }
}

void strat1(void) {
// All start alive
   bool A_alive = true;
   bool B_alive = true;
   bool C_alive = true;

   while (at_least_two_alive(A_alive, B_alive, C_alive)) {
      if (A_alive) {
         Aaron_shoots1(A_alive, C_alive); 
      }
      if (B_alive) {
         Bob_shoots(A_alive, C_alive);
      }
      if (C_alive) {
         Charlie_shoots(A_alive, B_alive);
      }
   }

   if (A_alive) {
      a_wins++;
   }
   if (B_alive) {
      b_wins++;
   }
   else {
      c_wins++;
   }
}

void strat2(void) {
	//All start alive
   bool A_alive = true;
   bool B_alive = true;
   bool C_alive = true;
   while (at_least_two_alive(A_alive, B_alive, C_alive)) {
      if (A_alive) {
         Aaron_shoots2(B_alive, C_alive);
      }
      if (B_alive) {
         Bob_shoots(A_alive, C_alive);
      }
      if (C_alive) {
         Charlie_shoots(A_alive, B_alive);
      }
   }
	//Only one alive after loop, whoever alive is winner.
   if (A_alive) {
      a_wins++;
   }
   else if (B_alive) {
      b_wins++;
   }
   else {
      c_wins++;
   }
}
 
 
 /* Implementation of the test driver for at_least_two_alive() */

void test_at_least_two_alive(void) {
   
   cout << "Unit Testing 1: Function – at_least_two_alive()\n\n";
   
   cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
   assert(true == at_least_two_alive(true, true, true));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
   assert(true == at_least_two_alive(false, true, true));
   cout << "\tCase passed ...\n";
         
   cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
   assert(true == at_least_two_alive(true, false, true));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
   assert(true == at_least_two_alive(true, true, false));
   cout << "\tCase passed ...\n";
   
   cout<< "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
   assert(false == at_least_two_alive(false, false, true));
   cout << "\tCase passed...\n";
	
   cout<< "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
   assert(false == at_least_two_alive(false, true, false));
   cout << "\tCase passed...\n";
	
   cout<< "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(true, false, false));
   cout << "\tCase passed...\n";
	
   cout<< "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(false, false, false));
   cout << "\tCase passed...\n\n";


}

void test_Aaron_shoots1(void) {

   cout << "\nUnit Test 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n\n";
   bool Bob_alive;
   bool Charlie_alive;

   cout << "\tCase 1: Bob alive, Charlie alive\n";
   cout << "\t\tAaron shoots at Charlie\n";
   Bob_alive = true;
   Charlie_alive = true;
   Aaron_shoots1(Bob_alive, Charlie_alive);
   assert(true == Bob_alive);
   if (Charlie_alive) {
      cout << "\t\tAaron misses.\n";
   }
   else {
      cout << "\t\tCharlie is dead.\n";
   }

   cout << "\tCase 2: Bob dead, Charlie alive\n";
   cout << "\t\tAaron shoots at Charlie\n";
   Bob_alive = false;
   Charlie_alive = true;
   Aaron_shoots1(Bob_alive, Charlie_alive);
   assert(false == Bob_alive);
   if (Charlie_alive) {
      cout << "\ttAaron misses.\n";
   } 
   else {
      cout << "\t\tCharlie is dead.\n";
   }
   
   cout << "\tCase 3: Bob alive, Charlie dead\n";
   cout << "\t\tAaron shoots at Bob\n";
   Bob_alive = true; 
   Charlie_alive = false;
   Aaron_shoots1(Bob_alive, Charlie_alive);
   assert(false == Charlie_alive);
   if (Bob_alive) {
      cout << "\t\tAaron misses.\n";
   }
   else {
      cout << "\t\tBob is dead.\n";
   }
}

void test_Bob_shoots(void) {

   cout << "\nUnit Test 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
   bool A_alive;
   bool C_alive;

   cout << "\n\tCase 1: Aaron alive, Charlie alive\n";
   cout << "\t\tBob shoots at Charlie\n";
   A_alive = true;
   C_alive = true;
   Bob_shoots(A_alive, C_alive);
   assert(true == A_alive);
   if (C_alive) {
      cout << "\t\tBob misses.\n";
   }
   else {
      cout << "\t\tCharlie is dead.\n";
   }

   cout << "\tCase 2: Aaron dead, Charlie alive\n";
   cout << "\t\tBob shoots at Charlie\n";
   A_alive = false;
   C_alive = true;
   Bob_shoots(A_alive, C_alive);
   assert(false == A_alive);
   if (C_alive) {
      cout << "\t\tBob misses.\n";
   }
   else {
      cout << "\t\tCharlie is dead.\n";
   }
   
   cout << "\tCase 3: Aaron alive, Charlie dead\n";
   cout << "\t\tBob shoots at Charlie\n";
   A_alive = true;
   C_alive = false;
   Bob_shoots(A_alive, C_alive);
   assert(false == C_alive);
   if (A_alive) {
      cout << "\t\tBob misses.\n";
   }
   else {
      cout << "\t\tAaron is dead.\n";
   }
   
}

void test_Charlie_shoots(void) {
   
   cout << "\nUnit Test 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
   bool A_alive;
   bool B_alive;

   cout << "\tCase 1: Aaron alive, Bob alive\n";
   cout << "\t\tCharlie shoots at Bob\n";
   A_alive = true;
   B_alive = true;
   Charlie_shoots(A_alive, B_alive);
   assert(true == A_alive);
   assert(false == B_alive);
   cout << "\t\tBob is dead.\n";
   
   cout << "\tCase 2: Aaron dead, Bob alive\n";
   cout << "\t\tCharlie shoots at Bob\n";
   A_alive = false;
   B_alive = true;
   Bob_shoots(A_alive, B_alive);
   Charlie_shoots(A_alive, B_alive);
   assert(false == A_alive);
   assert(false == B_alive);
   cout << "\t\tBob is dead.\n";
   
   cout << "\tCase 3: Aaron alive, Bob dead\n";
   cout << "\t\tCharlie shoots at Aaron\n";
   A_alive = true;
   B_alive = false;
   Bob_shoots(A_alive, B_alive);
   Charlie_shoots(A_alive, B_alive);
   assert(false == A_alive);
   assert(false == B_alive);
   cout << "\t\tAaron is dead.\n";
   
}

void test_Aaron_shoots2(void) {

   cout << "\nUnit Test 5: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
   bool Bob_alive;
   bool Charlie_alive;

   cout << "\tCase 1: Bob alive, Charlie alive\n";
   cout << "\t\tAaron misses his first shot on purpose.\n";
   Bob_alive = true;
   Charlie_alive = true;
   Aaron_shoots2(Bob_alive, Charlie_alive);
   assert(true == Bob_alive);
   assert(true == Charlie_alive);
   cout << "\t\tBoth Bob and Charlie are still alive.\n";

   cout << "\tCase 2: Bob dead, Charlie alive\n";
   cout << "\t\tAaron shoots at Charlie\n";
   Bob_alive = false;
   Charlie_alive = true;
   Aaron_shoots1(Bob_alive, Charlie_alive);
   assert(false == Bob_alive);
   if (Charlie_alive) {
      cout << "\t\tAaron misses.\n";
   } 
   else {
      cout << "\t\tCharlie is dead.\n";
   }
   
   cout << "\tCase 3: Bob alive, Charlie dead\n";
   cout << "\t\tAaron shoots at Bob\n";
   Bob_alive = true; 
   Charlie_alive = false;
   Aaron_shoots1(Bob_alive, Charlie_alive);
   assert(false == Charlie_alive);
   if (Bob_alive) {
      cout << "\t\tAaron misses.\n";
   }
   else {
      cout << "\t\tBob is dead.\n";
   }
}
