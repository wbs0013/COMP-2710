// name: Blake Schilleci, wbs0013
// partner: Will Bianca, wcb0020
// filename: hw05.cpp
// due date: 10/05/2018
// collaboration: We did not use any external sources for this assignment.
// problem: write a program that is a trivia game. Either created by the user 
//          or the previously created game.

#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
using namespace std;



//Global variable points to track points
int totalPoints = 0;

//Structure for TriviaNode
//question and answer are strings that hold the question/answer, points
//is an integer that holds how many points awarded and link is a pointer
//to the next node.
struct TriviaNode {
   string question;
   string answer;
   int points;
};
//Trivia node pointer
typedef TriviaNode* TriviaNodePtr;

//Linked list structure for trivia nodes
struct TriviaList {
	
   public:
   
   TriviaList(){}
   
   TriviaList(string theQuestion, string theAnswer, int thePoints, TriviaList* theLink) {
   
      node.question = theQuestion; 
      node.answer = theAnswer; 
      node.points = thePoints; 
      link = theLink;
   
   }
   
   TriviaList* getLink() {
      return link;}
   
   string getQuestion() {
      return node.question;}
   
   string getAnswer() {
      return node.answer;}
   
   int getPoints() {
      return node.points;
   }
   
   void setQuestion(string theQuestion) 	{
      node.question = theQuestion;
   }
   
   void setAnswer(string theAnswer)	{
      node.answer = theAnswer;
   }
   
   void setPoints(int thePoints)	{
      node.points = thePoints;
   }
   
   void setLink (TriviaList* pointer)	{
      link = pointer;
   }
	
   private:
   
   TriviaNode node;
   TriviaList* link;
};
typedef TriviaList* TriviaListPtr;

//initList prototype
TriviaListPtr initList();

//addNode prototype
TriviaListPtr addNode(string theQuestion, string theAnswer, int thePoints, TriviaListPtr theLink);

//quizPlayer prototype
int quizPlayer(TriviaListPtr list, int numOfQuestions);

//getTrivia
//Adds to list using addNode().
TriviaListPtr getTrivia(TriviaListPtr head);


//Testing of initList()
void test_initList();

//Testing of addNode()
void test_addNode();

//Testing of quizPlayer()
void test_quizPlayer();

//Testing of getTrivia()
void test_getTrivia();

int main() {

//change #ifdef to #define in order to test, comment out other macro statements.
//keep the same macro statements to run product version.
	
   #ifdef UNIT_TESTING 
   test_quizPlayer(); 
   cout << "\n\nWould you like to perform more testing? (Yes/No): ";
   string response;
   getline(cin, response);
   while (response != "Yes" && response != "No") {
      cout << "Please enter valid input (Yes/No): ";
      getline(cin, response);
   }
   if (response == "Yes") {
      cout << "\nMore Testing:\n\n";
      test_initList(); 
      test_addNode(); 
      test_getTrivia(); 
      cout << "\nEnd of extra testing\n";
   }
	
   //Comment out #else out in order to test
   
	#else    
   TriviaListPtr head = NULL;
   cout << "*** Welcome to Blake and Will's trivia quiz game ***\n";
   cout << "Would you like to enter your own trivia? (Yes/No): ";
   string ans;
   getline(cin, ans);

   while (ans != "Yes" && ans != "No") {
      cout << "Please enter valid input (Yes/No): ";
      getline(cin, ans);
   }

   if (ans == "Yes") {
      string cont;
      do {
      
         head = getTrivia(head);
      
         cout << "Continue? (Yes/No): ";
         getline(cin, cont);
      
         while (cont != "Yes" && cont != "No") {
            cout << "Please enter valid input (Yes/No): ";
            getline(cin, cont);
         }
      }
      while (cont == "Yes");
   }
   
   else {
      head = initList();
   }
   cout << endl; 
   cout << "How many questions would you like to answer? ";
   int questions;
   cin >> questions;
   int test;
   test = quizPlayer(head, questions);

   while (test == 1) {
      cout << "Enter a valid number: ";
      cin >> questions;
      test = quizPlayer(head, questions);
   }

   cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
	
   //Comment out #endif in order to test.
   
  #endif
	
}

//****************DEFINITIONS**********************//

   //Definition of initList()
TriviaListPtr initList() {
   TriviaListPtr head;

   string q = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
   string a = "Wii Sports";
   int p = 20;
   head = new TriviaList(q, a, p, NULL);

   q = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
   a = "Bank of Italy";
   p = 50;
   head = new TriviaList(q, a, p, head);

   q = "How long was the shortest war on record? (Hint: how many minutes)";
   a = "38";
   p = 100;
   head = new TriviaList(q, a, p, head);
   return head;
}

//Definition of addNode()
TriviaListPtr addNode(string theQuestion, string theAnswer, int thePoints, TriviaListPtr theLink) {
   TriviaListPtr head = new TriviaList(theQuestion, theAnswer, thePoints, theLink);
   return head;
}

//Defintion of quizPlayer()
int quizPlayer(TriviaListPtr list, int numOfQuestions) {

   if (numOfQuestions <= 0) {
      cout << "Warning - The number of trivia to be asked must be equal to or larger than 1\n";
      return 1; 
   }
   
   else if (list == NULL) {
      cout << "Warning - an empty list is not a valid trivia list\n";
      return 1; 
   }
   else {
      TriviaListPtr head = list;
      TriviaListPtr next = head->getLink();
      int size = 1;
   
      while (next != NULL) {
         next = next->getLink();
         size++;
      }
      if (size < numOfQuestions) {
         cout << "Warning - there are only " << size << " trivia questions\n";
         return 1; 
      }
      else {
      
         next = head;
         string answer;
         int index = 0;
         do {
            cout << "Question: " << next->getQuestion() << endl;
            cout << "Answer: ";
            getline(cin, answer);
         
            if (answer == "") {
               getline(cin, answer);
            }
         
            if (answer == next->getAnswer()) {
               cout << "Your answer is correct. You receive " << next->getPoints() << " points.\n";
               totalPoints += next->getPoints();
            }
            
            else {
               cout << "Your answer is wrong. The correct answer is: " << next->getAnswer() << endl;
            }
            cout << "Your total points : " << totalPoints << "\n\n";
            next = next->getLink();
            index++;
         }
         
         while (next != NULL && index < numOfQuestions);
         return 0; 
      }
   }
}

//Definition for getTrivia
TriviaListPtr getTrivia(TriviaListPtr list) {
   TriviaListPtr head = list;
   string question;
   string answer;
   int p;

   cout << "Enter a question: ";
   getline(cin, question);
   cout << "Enter an answer: ";
   getline(cin, answer);
   cout << "Enter award points: ";
	//Check to be sure points is valid (an integer > 0) 
   while (!(cin >> p) || p <= 0) {
      cout << "Points must be a number greater than 0. Try again: ";
      cin.clear(); 
      cin.ignore(1000, '\n'); 
   }
   head = addNode(question, answer, p, head);
   cin.clear();
   cin.ignore(1000, '\n'); 
   return head;
}

//*******************TEST DRIVERS******************//

//Defintion of test driver for test_initList
void test_initList() {
   TriviaListPtr head = initList();
   cout << "Test for initList():\n";
   assert("How long was the shortest war on record? (Hint: how many minutes)" == head->getQuestion());
   assert("38" == head->getAnswer());
   assert(100 == head->getPoints());
   cout << "\tTrivia 1 matches\n";
   TriviaListPtr next = head->getLink();
   assert("What was Bank of America's original name? (Hint Bank of Italy or Bank of Germany)" == next->getQuestion());
   assert("Bank of Italy" == next->getAnswer());
   assert(50 == next->getPoints());
   cout << "\tTrivia 2 matches\n";
   next = next->getLink();
   assert("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)" == next->getQuestion());
   assert("Wii Sports" == next->getAnswer());
   assert(20 == next->getPoints());
   assert(NULL == next->getLink());
   cout << "\tTrivia 3 matches\n";
}

//Defintion of test driver for test_addNode
void test_addNode() {
   cout <<"Test for addNode()\n";

   TriviaListPtr head = NULL;
   head = addNode("test", "test", 5, head);
   assert("test" == head->getQuestion());
   assert("test" == head->getAnswer());
   assert(5 == head->getPoints());
   assert(NULL == head->getLink());
   cout << "\tTest 1: Empty/new list passed\n";

   head = addNode("test2", "test2", 20, head);
   assert("test2" == head->getQuestion());
   assert("test2" == head->getAnswer());
   assert(20 == head->getPoints());
   TriviaListPtr next = head->getLink();
   assert("test" == next->getQuestion());
   assert("test" == next->getAnswer());
   assert(5 == next->getPoints());
   assert(NULL == next->getLink());
   cout << "\tTest 2: Add to existing list passed\n";
}

//Definition of test driver for test_quizPlayer

void test_quizPlayer() {

   TriviaListPtr list = initList();
   int test;
   cout << "*** This is a debug version ***\n";
	

   cout << "Unit test case 1: Ask no questions. The program should give a warning message.\n";
   test = quizPlayer(list, 0);
	

   cout << "\nUnit Test Case 2.1: Ask 1 question, tester answers incorrect answer.\n";
   test = quizPlayer(list, 1);
   assert(0 == totalPoints);
   cout << "Case 2.1 Passed\n";
	

   cout << "\n Unit Test Case 2.2: Ask 1 question, tester answers correct answer.\n";
   test = quizPlayer(list, 1);
   assert(100 == totalPoints);
   cout << "Case 2.2 Passed\n";
	

   totalPoints = 0; 
   cout << "\n Unit Test Case 3.1: Ask 3 questions, give all incorrect answers.\n";
   test = quizPlayer(list, 3);
   assert(0 == totalPoints);
   cout << "Case 3.1 Passed\n";
	

   cout << "\n Unit Test Case 3.2: Ask 3 questions, give all correct answers.\n";
   test = quizPlayer(list, 3);
   assert(170 == totalPoints);
   cout << "Case 3.2 Passed \n";
	


   cout << "\nTest Case 4: Ask 5 questions. The program should give a warning\n";
   test = quizPlayer(list, 5);
	

   cout <<"\nTest Case 5: Use an empty trivia list. The program should give a warning\n";
   test = quizPlayer(NULL, 3);
	
   cout<<"*** End of Debug Version***";
}

//Test driver for getTrivia
void test_getTrivia() {
   cout << "Test for getTrivia. Please input the following when prompted\nQuestion: How old are you?\nAnswer: 21\nPoints: 100\n";
   TriviaListPtr head = NULL;
   head = getTrivia(head);
   assert("How old are you?" == head->getQuestion());
   assert("21" == head->getAnswer());
   assert(100 == head->getPoints());
   cout << "Test passed\n";
}