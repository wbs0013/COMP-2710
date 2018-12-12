/*
 * This program shows how to compare two strings.
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

//#define COMPARE_METHOD_1

int main( )
{
   string key;
   string answer;
   unsigned int score;
   unsigned int i;
  
   cout << "Enter a key:";
   getline(cin, key);

   cout << "Enter an answer:";
   getline(cin, answer);

#ifdef COMPARE_METHOD_1
   cout << "Use == opeartor to compare key and answer" << endl;

   if (key == answer) 
     cout << "Your answer is correct." << endl;
   else 
     cout << "Your answer is incorrect." << endl;
#else /* COMPARE_METHOD_2 */
   cout << "Use the compare member function to compare key and answer" << endl;

   if (key.compare(answer) == 0) 
      cout << "Your answer is correct." << endl;
   else 
      cout << "Your answer is incorrect." << endl;
#endif

   return 0;
}
