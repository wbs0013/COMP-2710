/*
 * COMP2710: Homework 5
 * This program shows how to get strings and non-string data from keyboards.
 * (see Lines 74-90).
 * 
 * Note: The source code has three versions, namely, BUG1 (see Line 35), BUG2 (see Line 36), 
 * and WORKING (see Line 37). The WORKING version is enabled in the source code.
 *
 * Compile the code: g++ input_string_int.cpp -o input_string_int
 * Run: ./input_string_int
 *
 * Dr. Xiao Qin <xqin@auburn.edu>
 *
 * Samuel Ginn College of Engineering
 * Auburn University, AL 36849-5347 
 * http://www.eng.auburn.edu/~xqin/
 *
 */ 

/*
 * 
 *
 * Xiao Qin <xqin@auburn.edu>
 *
 * Samuel Ginn College of Engineering
 * Auburn University, AL 36849-5347 
 * http://www.eng.auburn.edu/~xqin/
 *
 */ 
#include <climits>
#include <iostream>
#include <string>

using namespace std;
//#define BUG1
//#define BUG2
#define WORKING

int main( )
{
   string question;
   string answer;
   unsigned int score;
   unsigned int i;
 
#ifdef BUG1    
    cout << "Enter a question:";
    cin >> question;

    cout << "Enter an answer:";
    cin >> answer;

    cout << "Enter award points:";
    cin >> score;
    
    cout << "Question: " << question << endl;
    cout << "Answer: " << answer << endl;
    cout << "Score: " << score << endl;
#endif

#ifdef BUG2
  for (i = 0; i < 3; i++) {
    cout << "Enter a question:";
    getline(cin, question);

    cout << "Enter an answer:";
    getline(cin, answer);

    cout << "Enter award points:";
    cin >> score;
    cout << "Question: " << question << endl;
    cout << "Answer: " << answer << endl;
    cout << "Score: " << score << endl;
  }
#endif

#ifdef WORKING 
   for (i = 0; i < 3; i++) {
      cout << "Enter a question:";
      getline(cin, question);
   
      cout << "Enter an answer:";
      getline(cin, answer);
   
      cout << "Enter award points:";
      cin >> score;
      cin.clear();
      cin.ignore(INT_MAX, '\n'); 
      cout << "Question: " << question << endl;
      cout << "Answer: " << answer << endl;
      cout << "Score: " << score << endl;
   }
#endif
   return 0;
}
