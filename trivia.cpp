/*
 * COMP2710: Homework 5
 * This program shows how to implement an array of structures.
 * The source code demonstrates a problem of mixing getline with cin (see Lines 44-51).
 * 
 * Compile the code: g++ trivia.cpp -o trivia
 * Run: ./trivia
 *
 * Dr. Xiao Qin <xqin@auburn.edu>
 *
 * Samuel Ginn College of Engineering
 * Auburn University, AL 36849-5347 
 * http://www.eng.auburn.edu/~xqin/
 *
 */ 
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
using namespace std;

#define NUM_TRIVIA 2

struct trivia {
   string question;
   string answer;
   int award;
};

int printTrivia (const trivia triviaAry[], int size, int trivia_index);

int main ()
{
   string mystr;
   trivia triviaArray[NUM_TRIVIA];
   int i;

   for (i=0; i<NUM_TRIVIA; i++)
   {
      cout << "Enter Question: ";
      getline (cin,triviaArray[i].question);
      cout << "Enter Answer: ";
      getline (cin,triviaArray[i].answer);
      cout << "Enter award: ";
   // problem of mixing getline with cin.
   //    cin >> triviaArray[i].award;
   // Solution 1: see the following two lines
   //    getline (cin,mystr);
   //    stringstream(mystr) >> triviaArray[i].award;
   // Solution 2: see the following two lines
      cin >> triviaArray[i].award;
      cin.ignore(1000, '\n');
   }

   cout << "\nYou have entered these quizzes:\n";
   for (i=0; i<NUM_TRIVIA; i++)
      assert(printTrivia (triviaArray, NUM_TRIVIA, i)==0);
   return 0;
}

int printTrivia (const trivia triviaAry[], int size, int trivia_index)
{
   if (size > NUM_TRIVIA || trivia_index >= size) 
      return 1; //fail

   cout << "Trivia " << trivia_index << "\n";
   cout << "Question: " << triviaAry[trivia_index].question << "\n";
   cout << "Answer: " << triviaAry[trivia_index].answer << "\n";
   cout << "Award: " << triviaAry[trivia_index].award << "\n";
   return 0; //success
}
