 // name: Blake Schilleci, wbs0013
// partner: Will Bianca, wcb0020
// filename: Project1.cpp
// due date: 11/08/2018
// collaboration: We did not use any external sources for this assignment.
// Project: Design a text-based game for the user to manuever and become victorious.
//
// NOTE: Used StackOverflow for "ifexists" function to check if a file exists.



#include <cstdlib>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

const int GOAL = 20;


class HighScores {
      public:
   int Score(int& money, int& intelligence, int& timer);
   void newHighScore(int inputScore, string inputName);
   void printHighScores();
   void askName(string& name);
   string getName();
   int final_score;
   string name;
      private:
   bool ifexists(const std::string& name);   
   int numberOfScores;
   ifstream inStream;
   ofstream outStream;
};

int HighScores::Score(int& money, int& intelligence, int& timer) {
   final_score = money * intelligence * timer;
   if (final_score < 0) {
      final_score = final_score * -1;
   }   
   return final_score;
}

void HighScores::newHighScore(int inputScore, string inputName) {
   const int MAX_SIZE = 10;   
   int intArray[MAX_SIZE];
   string stringArray[MAX_SIZE];
   string hsArray[MAX_SIZE];
   int intIndex, stringIndex, hsIndex;
   
   if (ifexists("output.txt")) {
      ifstream infile("output.txt");
      infile >> hsArray[hsIndex];
      while (! infile.eof()) {
         hsIndex++;
         infile >> hsArray[hsIndex];
      } 
      infile.close();
      
      intIndex = 0;
      stringIndex = 0;
      for (int i = 0; i < hsIndex; i++) {      
         string x = hsArray[i];
         int pos = x.find("-");
         string num = x.substr(0, pos);
         int numb;
         istringstream(num) >> numb;
         intArray[intIndex] = numb;
         intIndex++;
         string nombre = x.substr(pos + 1);
         stringArray[stringIndex] = nombre;
         stringIndex++;;
      }
      
      int i, j, iKey;
      string sKey;
      for (j = 1; j < hsIndex; j++) {
         iKey = intArray[j];
         sKey = stringArray[j];
         for (i = j - 1; (i >= 0) && (intArray[i] < iKey); i--) {
            intArray[i + 1] = intArray[i];
            stringArray[i + 1] = stringArray[i];
         }
         intArray[i + 1] = iKey;
         stringArray[i + 1] = sKey;
      }
      
      if (hsIndex > 0) {
         string a;
         a += std::to_string(inputScore);
         a += "-";
         a += name; 
         if (inputScore > intArray[9] && hsIndex == 10) {
            hsArray[9] = a;
         }
         else if (hsIndex < 10) {
            hsArray[hsIndex] = a;
            hsIndex++;
         } 
         else {
            return;
         }
         intIndex = 0;
         stringIndex = 0;
         for (int i = 0; i < hsIndex; i++) {      
            string x = hsArray[i];
            int pos = x.find("-");
            string num = x.substr(0, pos);
            int numb;
            istringstream(num) >> numb;
            intArray[intIndex] = numb;
            intIndex++;
            string nombre = x.substr(pos + 1);
            stringArray[stringIndex] = nombre;
            stringIndex++;;
         }
         
         i = 0;
         j = 0;
         iKey = 0;
         sKey = "";
         for (j = 1; j < hsIndex; j++) {
            iKey = intArray[j];
            sKey = stringArray[j];
            for (i = j - 1; (i >= 0) && (intArray[i] < iKey); i--) {
               intArray[i + 1] = intArray[i];
               stringArray[i + 1] = stringArray[i];
            }
            intArray[i + 1] = iKey;
            stringArray[i + 1] = sKey;
         }  
         
         for (int k = 0; k < hsIndex; k++) {
            string final;
            int number = intArray[k];
            final = std::to_string(number);
            string finalName = stringArray[k];
            final += "-";
            final += finalName;
            hsArray[k] = final;
         } 
      
         remove("output.txt");
         ofstream outfile("output.txt");
         for (int x = 0; x < hsIndex; x++) {
            outfile << hsArray[x] << endl;
         }
         outfile.close();    
      
      } 
   }   
   
   else {
      string a;
      a = std::to_string(inputScore);
      a += "-";
      a += name;
      ofstream outfile("output.txt");
      outfile << a << endl;
      outfile.close(); 
   }       

} 

void HighScores::printHighScores() {
   if (!ifexists("output.txt")) {
      cout << "There are no high scores yet";
      return;
   }   
   ifstream infile("output.txt");
   string array[10];
   int index = 0;
   infile >> array[index];
   while (! infile.eof()) {
      index++;
      infile >> array[index];
   } 
   infile.close();
   
   cout << "Top " << index << " High Scores\n";
   
   for (int i = 0; i < index; i++) {
      cout << i + 1 << ". \t" << array[i] << endl;
   }
      
}

inline bool HighScores::ifexists(const std::string& name) {
   ifstream f(name.c_str());
   return f.good();
}

void HighScores::askName(string& name) {
   cout << "Please enter your name: ";
   cin >> name;
} 

string HighScores::getName() {
   return name;
}     

class Puzzle {
      public:
   void Puzzles(int& money, int& intelligence, int& timer, int& position);
   int pcount;
   int money;
   int intelligence;
   int timer;
   int position;
};

void Puzzle::Puzzles(int& money, int& intelligence, int& timer, int& position) {

   int pcount = rand()%70;
   if (pcount <= 10) {
      cout << "PUZZLE: How many oreos is a reccomended serving amount?";
      cout << "\n\n\tA) 0";
      cout << "\n\tB) 10";
      cout << "\n\tC) 2";
      cout << "\n\tD) 5";
      cout << "\n\nEnter your answer (Use Capital Letters): ";
      std::string answer1 = "";
      cin >> answer1;
      if (answer1 == "C") {
         cout << "\n\nCongratulations! Move one step forward, gain one intelligence, gain one money\n\n";  
         position++;
         money++;
         intelligence++;
      }
      else {
         cout << "\n\nThe correct answer was C. Do not move forward, lose one intelligence and one money.\n\n";
         money--;
         intelligence--;
      }
      pcount += 10;
   } 
   
   else if (pcount <= 20 && pcount > 10) {
      cout << "PUZZLE: How many parsecs did it take for the Millenium Falcon to do the Kessel Run?";
      cout << "\n\n\tA) 16";
      cout << "\n\tB) 50";
      cout << "\n\tC) 1";
      cout << "\n\tD) 12";
      cout << "\n\nEnter your answer (Use Capital Letters): ";
      std::string answer2 = "";
      cin >> answer2;
      if (answer2 == "D") {
         cout << "\n\nCongratulations! Move one step forward, gain one intelligence, gain one money\n\n";  
         position++;
         money++;
         intelligence++;
      }
      else {
         cout << "\n\nThe correct answer was D. Do not move forward, lose one intelligence and one money.\n\n";
         money--;
         intelligence--;
      }
      pcount += 10;
   }
   
   else if (pcount > 20 && pcount <= 30) {
      cout << "PUZZLE: Before Mt. Everest was discovered, what was the highest mountain in the world?";
      cout << "\n\n\tA) Mt. Rushmore";
      cout << "\n\tB) Mt. Everest";
      cout << "\n\tC) Mt. St. Helen";
      cout << "\n\tD) Mt. Kilamanjaro";
      cout << "\n\nEnter your answer (Use Capital Letters): ";
      std::string answer3 = "";
      cin >> answer3;
      if (answer3 == "B") {
         cout << "\n\nCongratulations! Move one step forward, gain one intelligence, gain one money\n\n";  
         position++;
         money++;
         intelligence++;
      }
      else {
         cout << "\n\nThe correct answer was B. Do not move forward, lose one intelligence and one money.\n\n";
         money--;
         intelligence--;
      }
      pcount += 10;
   }
   
   else if (pcount <= 40 && pcount > 30) {
      cout << "PUZZLE: How many players play on a field in Ultimate Frisbee?";
      cout << "\n\n\tA) 10";
      cout << "\n\tB) 20";
      cout << "\n\tC) 14";
      cout << "\n\tD) 9";
      cout << "\n\nEnter your answer (Use Capital Letters): ";
      std::string answer4 = "";
      cin >> answer4;
      if (answer4 == "C") {
         cout << "\n\nCongratulations! Move one step forward, gain one intelligence, gain one money\n\n";  
         position++;
         money++;
         intelligence++;
      }
      else {
         cout << "\n\nThe correct answer was C. Do not move forward, lose one intelligence and one money.\n\n";
         money--;
         intelligence--;
      } 
      pcount += 10;
   }
   
   else if (pcount > 40 && pcount <= 50) {
      cout << "PUZZLE: How many letters are in the alphabet if you divide it by 2 and add 3?\n";
      cout << "\n\n\tA) 16";
      cout << "\n\tB) What?";
      cout << "\n\tC) This is a dumb question";
      cout << "\n\tD) Ok?";
      cout << "\n\nEnter your answer (Use Capital Letters): ";
      std::string answer5 = "";
      cin >> answer5;
      if (answer5 == "A") {
         cout << "\n\nCongratulations! Move one step forward, gain one intelligence, gain one money\n\n";  
         position++;
         money++;
         intelligence++;
      }
      else {
         cout << "\n\nThe correct answer was A. Do not move forward, lose one intelligence and one money.\n\n";
         money--;
         intelligence--;
      }
      pcount += 10;
   }
   
   else if (pcount > 50 && pcount <= 60) {
      cout << "PUZZLE: Who's gonna win the football game?";
      cout << "\n\n\tA) Not sure...";
      cout << "\n\tB)  AUBURN'S GONNA WIN THE FOOTBALL GAME!";
      cout << "\n\tC) Jack Sparrow";
      cout << "\n\tD) Optimus Prime";
      cout << "\n\nEnter your answer (Use Capital Letters): ";
      std::string answer6 = "";
      cin >> answer6;
      if (answer6 == "B") {
         cout << "\n\nCongratulations! Move one step forward, gain one intelligence, gain one money\n\n";  
         position++;
         money++;
         intelligence++;
      }
      else {
         cout << "\n\nWAR EAGLE! The correct answer was B. Do not move forward, lose one intelligence and one money.\n\n";
         money--;
         intelligence--;
      }
      pcount += 10;
   }
   
   else if (pcount > 60 && pcount < 70) {
      cout << "PUZZLE: There are 30 cows, 28 chickens, how many didn't?";
      cout << "\n\n\tA) 2";
      cout << "\n\tB) 28";
      cout << "\n\tC) 30";
      cout << "\n\tD) 10";
      cout << "\n\nEnter your answer (Use Capital Letters): ";
      std::string answer7 = "";
      cin >> answer7;
      if (answer7 == "D") {
         cout << "\n\nCongratulations! Move one step forward, gain one intelligence, gain one money\n\n";  
         position++;
         money++;
         intelligence++;
      }
      else {
         cout << "\n\nThe correct answer was D. Do not move forward, lose one intelligence and one money.\n\n";
         money--;
         intelligence--;
      }
      pcount += 10;
   }
   
}               


class Encounter {
      public:
   int End();   
   void Mugging(int& money);
   void Lecture(int& intelligence, int& timer);
   void FindMoney(int& money, int& timer);
   void StudyGuide(int& intelligence);
   void Random(int& money, int& intelligence, int& timer);
   int money;
   int intelligence;
   int timer;
      private:
   HighScores hs;
};

int Encounter::End() {
   cout << "\nYOU LOSE\n";
   exit(0);
}

void Encounter::Mugging(int& money) {
   srand(time(0));
   int lost = (rand()%2) + 3;
   money = money - lost;
   if (money <= 0) {
      cout << "\nYour money has reached zero. You have died.\n\n";
      End();
   }
   cout << "\nOH NO! Someone just robbed you in Shelby Center. You lose $" << lost << ".00\n\n"; 
} 

void Encounter::Lecture(int& intelligence, int& timer) {
   srand(time(0));
   int lost = (rand()%2) + 3;
   intelligence = intelligence - lost;
   timer = timer - 3; 
   if (intelligence <= 0) {
      cout << "\nYour intelligence has reached zero. Congratulations.\n\n";
      End();
   } 
   if (timer <= 0) {
      cout << "\nYou have run out of time. You have died.\n\n";
      End();
   }  
   cout << "\nYou must listen to a Discrete Structures lecture. You lose " << lost << " intelligence and lose 3 seconds.\n\n";      
}   

void Encounter::FindMoney(int& money, int& timer) {
   srand(time(0));
   int gain = (rand()%4) + 3;
   money = money + gain;
   timer = timer - 3;
   if (timer <= 0) {
      cout << "\nYou have run out of time. You have died.\n\n";  
      End();
   } 
   cout << "\nCoins are all over the hallway, and you want lunch, and you're broke... So, you get $" << gain << ".00 but lose 3 seconds\n\n";
   if (money > 30) {
      money = 30;
   }
} 

void Encounter::StudyGuide(int& intelligence) {
   srand(time(0));
   int gain = (rand()%4) + 3;
   intelligence = intelligence + gain;
   cout << "\nYour professor posted a study guide with answers for an upcoming exam. Gain " << gain << " intelligence\n\n";  
   if (intelligence > 30) {
      intelligence = 30;
   }   
}   

void Encounter::Random(int& money, int& intelligence, int& timer) {
   srand(time(0));
   int lossM = (rand()%3) + 4;
   money = money - lossM;
   int lossI = (rand()%3) + 4;
   intelligence = intelligence - lossI;
   timer = timer - 3;
   if (money <= 0) {
      cout << "\nYour money has reached zero. You have died.\n\n";
      End();
   }
   if (intelligence <= 0) {
      cout << "\nYour intelligence has reached zero. You have died.\n\n"; 
      End();
   }
   if (timer <= 0) {
      cout << "\nYou have run out of time. You have died.\n\n";
      End();
   }      
   cout << "Just for kicks and giggles, you lose $" << lossM << ".00 and " << lossI << " intelligence and lose 3 seconds.\n\n";
}

class System {
      public:
   void Play(int& money, int& intelligence, int& timer, int& position);
   void ReadTechPapers(int& intelligence, int& timer);
   void Search(int& money, int& timer);
   int money;
   int intelligence; 
   int timer;
   int final_score;
   int position;
   int play_option;
      private:
   void Move(int& money, int& intelligence, int& timer, int& position); 
   void ViewCharacter(int money, int intelligence, int timer, int position);
   Encounter enc;
   HighScores hs;
   Puzzle puzzle;
};

void System::Play(int& money, int& intelligence, int& timer, int& position)  {
   srand(time(0));
   money = (rand()%10) + 20;
   intelligence = (rand()%10) + 20;
   timer = (rand()%20) + 20;
   position = 0;
   
   cout << "\nEntering the game...\n\n";
   
   while (position < GOAL) {   
      cout << "Your Character Stats:\n\n";
      cout << "You are " << GOAL - position << " steps away from the goal.\n";
      cout << "Money: $" << money << ".00\n";
      cout << "Intelligence: " << intelligence << "\n";
      cout << "Time: " << timer << "\n\n";
      
      cout << "\t1) Move Forward (Could face an encounter or a puzzle)\n";
      cout << "\t2) Read technical papers (gain intelligence, lose time)\n";
      cout << "\t3) Search for loose change (gain money, lose time)\n";
      cout << "\t4) View character stats\n";
      cout << "\t5) Quit\n";
      
      cout << "\n\tPlease choose an option: ";
      cin >> play_option;
      
      if (play_option == 1) {
         Move(money, intelligence, timer, position);
      }
      else if (play_option == 2) {
         ReadTechPapers(intelligence, timer);
      }
      else if (play_option == 3) {
         Search(money, timer);
      }
      else if (play_option == 4) {
         ViewCharacter(money, intelligence, timer, position);
      }
      else if (play_option == 5) {
         cout << "\nYOU LOSE\n";
         cout << "Your final score is " << hs.Score(money, intelligence, timer) << "\n";
         cout << "Since you quit, your score will not be added to the High Score list\n\n";
         exit(0);
      }
      
      else {
         cout << "\n\nYou must type either 1, 2, 3, 4, or 5. Please try again.\n";
         cout << "Due to your ignorance(or fat thumbs), you will restart the game with zero money.";
         Play(money, intelligence, timer, money);
      }            
   }
   
   if (position == GOAL) {
      cout << "Congratulations! You win!\n";
      cout << "Your score is " << hs.Score(money, intelligence, timer);
      final_score = hs.Score(money, intelligence, timer);
      string name = hs.getName();
      hs.newHighScore(final_score, name);
      exit(0);  
   }   
}                      

void System::ReadTechPapers(int& intelligence, int& timer) {
   srand(time(0));
   int gain = rand()%10;
   intelligence = intelligence + gain;
   if (intelligence > 30) {
      intelligence = 30;
   }
   timer = timer - 3;
   if (timer <= 0) {
      cout << "\nYou have run out of time. You have died.\n\n";
      enc.End();
   }
   cout << "\nYou have gained " << gain << " intelligence, but lose 3 seconds.\n\n";
}      
  
void System::Search(int& money, int& timer) {
   srand(time(0));
   int gain = rand()%10;  
   money = money + gain;
   if (money > 30) {
      money = 30;
   }
   timer = timer - 3;
   if (timer <= 0) {
      cout << "\nYou have run out of time. You have died.\n\n";
      enc.End();
   }
   cout << "\nYou have gained $" << gain << ".00, but lose 3 seconds. You have gained money.\n\n";
}

void System::ViewCharacter(int money, int intelligence, int timer, int position) {
   cout << "Your Character Stats:\n\n";
   cout << "You are " << GOAL - position << " steps away from the goal.\n";
   cout << "Money: $" << money << ".00\n";
   cout << "Intelligence: " << intelligence << "\n";
   cout << "Time: " << timer << "\n\n";
}

void System::Move(int& money, int& intelligence, int& timer, int& position) {
   srand(time(0));
   int RNG = rand()%100;
   //Nothing
   if (RNG < 25) {
      position++;
      cout << "\nYou move one step closer without any issue\n\n";
   }
   //Puzzle
   else if (RNG >= 25 && RNG < 50) {
      puzzle.Puzzles(money, intelligence, timer, position);
   }
   //EngineeringFee
   else if (RNG >= 50 && RNG < 60) {
      enc.Mugging(money);
      position++;
   } 
   //MidTerm
   else if (RNG >= 60 && RNG < 70) {
      enc.Lecture(intelligence, timer);
      position++;
   }
   //BookReturn
   else if (RNG >= 70 && RNG < 80) {
      enc.FindMoney(money, timer);
      position++;
   }
   //StudyGuide
   else if (RNG >= 80 && RNG < 90) {
      enc.StudyGuide(intelligence);
      position++;
   }
   //Vocareum
   else if (RNG >= 90 && RNG < 100) {
      enc.Random(money, intelligence, timer);
      position++;
   }
}

class Menu {
      public: 
   void MainMenu();
   int option;
   int money;
   int intelligence;
   int timer;
   int position;
   string name;
      private:
   HighScores hs;   
   System sys;   
};

void Menu::MainMenu() {   
   cout << "\n1) Start a New Game of Surviving Shelby!\n"; 
   cout << "2) View top 10 High Scores\n";
   cout << "3) Quit\n";
   
   cout << "\n\tPlease choose an option: ";
   cin >> option;
   
   if (option == 1) {
      sys.Play(money, intelligence, timer, position); 
   }
   else if (option == 2) {
      cout << "Top 10 High Scores:\n";
      hs.printHighScores();
      cout << "\n\nBeginning game again...\n\n";
      MainMenu();
   }
   else if (option == 3) {
      cout << "\nQuitting game...";
      exit(0);
   } 
   else {
      cout << "You must type either 1, 2, or 3. Please try again.\n";
      MainMenu();
   }
}     

class Testing {
      public:
   void test_All();
      private:   
   HighScores hs;
   Puzzle pz;
   Encounter enc;
   System sys;
   Menu mn;
   int money;
   int intelligence;
   int timer;
   int expected;
   int actual;
   int score;
   string name;
   ofstream outStream;
};

void Testing::test_All() {
   remove("Project1_test.txt");   
   outStream.open("Project1_test.txt");
   outStream << "Unit Test Case 1: Class - HighScores; Function - Score(int& money, int& intelligence, int& timer)\n\n";
   
   outStream << "\tCase 1.1: Score() - Max Values\n";
   money = 30;
   intelligence = 30;
   timer = 40;
   expected = 36000;
   actual = hs.Score(money, intelligence, timer);
   assert(expected == actual);
   outStream << "\t\tCase 1.1: Passed\n------------------\n\n";
   
   outStream << "\tCase 1.2: Score() Median Values\n";
   money = 15;
   intelligence = 15;
   timer = 20;
   expected = 4500;
   actual = hs.Score(money, intelligence, timer);
   assert(expected == actual);
   outStream << "\t\tCase 1.2: Passed\n------------------\n\n";
   
   outStream << "\tCase 1.3: Score() Min Values\n";
   money = 0;
   intelligence = 0;
   timer = 0;
   expected = 0;
   actual = hs.Score(money, intelligence, timer);
   assert(expected == actual);
   outStream << "\t\tCase 1.3: Passed\n------------------\n\n\n\n";
   
   
   outStream << "Unit Test Case 2: Class - HighScores; Function - newHighScore(int inputScore, string inputName)\n\n"; 
   outStream << "Case 2.1: newHighScore()\n";
   name = "AJ";
   score = 2100;
   hs.newHighScore(score, name);
   outStream << "\t\tCase 2.1: Passed\n------------------\n\n\n\n";
   

   std::streambuf *oldbuf = std::cout.rdbuf();
   std::cout.rdbuf(outStream.rdbuf());


   
   outStream << "Unit Test Case 3: Class - Encounter; Function - Mugging(int& money)\n\n";
   outStream << "\tCase 3.1: Mugging() - Max value";
   money = 30;
   enc.Mugging(money);
   assert(money);
   outStream << "\t\tCase 3.1: Passed\n------------------\n\n";
   
   outStream << "\tCase 3.2: Mugging() - Median value";
   money = 15;
   enc.Mugging(money);
   assert(money);
   outStream << "\t\tCase 3.2: Passed\n------------------\n\n\n\n";
   

   
   outStream << "Unit Test Case 4: Class - Encounter; Function - Lecture(int& intelligence, int& timer)\n\n";
   outStream << "\tCase 4.1: Lecture() - Max values";
   intelligence = 30;
   timer = 40;
   enc.Lecture(intelligence, timer);
   assert(intelligence);
   assert(timer);
   outStream << "\t\tCase 4.1: Passed\n------------------\n\n";
   
   outStream << "\tCase 4.2: Lecture() - Median values";
   intelligence = 15;
   timer = 20;
   enc.Lecture(intelligence, timer);
   assert(intelligence);
   assert(timer);
   outStream << "\t\tCase 4.2: Passed\n------------------\n\n\n\n";
   

   
   outStream << "Unit Test Case 5: Class - Encounter; Function - FindMoney(int& money, int& timer)\n\n";
   outStream << "\tCase 5.1: FindMoney() - Max values";
   money = 30;
   timer = 40;
   enc.FindMoney(money, timer);
   assert(money);
   assert(timer);
   outStream << "\t\tCase 5.1: Passed\n------------------\n\n";
   
   outStream << "\tCase 5.2: FindMoney() - Median values";
   money = 15;
   timer = 20;
   enc.FindMoney(money, timer);
   assert(money);
   assert(timer);
   outStream << "\t\tCase 5.2: Passed\n------------------\n\n";
   
   outStream << "\tCase 5.3: FindMoney() - Min values";
   money = 1;
   timer = 4;
   enc.FindMoney(money, timer);
   assert(money);
   assert(timer);
   outStream << "\t\tCase 5.3: Passed\n------------------\n\n\n\n";
   

   
   outStream << "Unit Test Case 6: Class - Encounter; Function - StudyGuide(int& intelligence)\n\n";
   outStream << "\tCase 6.1: StudyGuide() - Max value";
   intelligence = 30;
   enc.StudyGuide(intelligence);
   assert(intelligence);
   outStream << "\t\tCase 6.1: Passed\n------------------\n\n";
   
   outStream << "\tCase 6.2: StudyGuide() - Median value";
   intelligence = 15;
   enc.StudyGuide(intelligence);
   assert(intelligence);
   outStream << "\t\tCase 6.2: Passed\n------------------\n\n";
   
   outStream << "\tCase 6.3: StudyGuide() - Min value";
   intelligence = 1;
   enc.StudyGuide(intelligence);
   assert(intelligence);
   outStream << "\t\tCase 6.3: Passed\n------------------\n\n\n\n";
   

   
   outStream << "Unit Test Case 7: Class - Encounter; Function - Random(int& money, int& intelligence, int& timer)\n\n";
   outStream << "\tCase 7.1: Random() - Max values";
   money = 30;
   intelligence = 30;
   timer = 40;
   enc.Random(money, intelligence, timer);
   assert(money);
   assert(intelligence);
   assert(timer);
   outStream << "\t\tCase 7.1: Passed\n------------------\n\n";
   
   outStream << "\tCase 7.2: Random() - Median values";
   money = 15;
   intelligence = 15;
   timer = 20;
   enc.Random(money, intelligence, timer);
   assert(money);
   assert(intelligence);
   assert(timer);
   outStream << "\t\tCase 7.2: Passed\n------------------\n\n\n\n";
   

   
   outStream << "Unit Test Case 8: Class - System; Function - ReadTechPapers(int& intelligence, int& timer)\n\n";
   outStream << "\tCase 8.1: ReadTechPapers() - Max values";
   intelligence = 30;
   timer = 40;
   sys.ReadTechPapers(intelligence, timer);
   assert(intelligence);
   assert(timer);
   outStream << "\t\tCase 8.1: Passed\n------------------\n\n";
   
   outStream << "\tCase 8.2: ReadTechPapers() - Median values";
   intelligence = 15;
   timer = 20;
   sys.ReadTechPapers(intelligence, timer);
   assert(intelligence);
   assert(timer);
   outStream << "\t\tCase 8.2: Passed\n------------------\n\n";
   
   outStream << "\tCase 8.3: ReadTechPapers() - Min values";
   intelligence = 1;
   timer = 4;
   sys.ReadTechPapers(intelligence, timer);
   assert(intelligence);
   assert(timer);
   outStream << "\t\tCase 8.3: Passed\n------------------\n\n\n\n";
   

   
   outStream << "Unit Test Case 9: Class - System; Function - Search(int& money, int& timer)\n\n";
   outStream << "\tCase 9.1: Search() - Max values";
   money = 30;
   timer = 40;
   sys.Search(money, timer);
   assert(money);
   assert(timer);
   outStream << "\t\tCase 9.1: Passed\n------------------\n\n";
   
   outStream << "\tCase 9.2: Search() - Median values";
   money = 15;
   timer = 20;
   sys.Search(money, timer);
   assert(money);
   assert(timer);
   outStream << "\t\tCase 9.2: Passed\n------------------\n\n";
   
   outStream << "\tCase 9.3: Search() - Min values";
   money = 1;
   timer = 4;
   sys.Search(money, timer);
   assert(money);
   assert(timer);
   outStream << "\t\tCase 9.3: Passed\n------------------\n\n\n\n";
   
   outStream << "Testing is complete...";
   
   std::cout.rdbuf(oldbuf);
   outStream.close();
}

int main() {

   cout << "****************WELCOME TO RACE AGAINST TIME****************";
   cout << "\n\n*********A game by Will Bianca and Blake Schilleci**********\n\n";
   Testing ts;
   HighScores hs;
   Menu menu;
   string name;
   
   //Run ts.test_All() to run test cases and print Project1_test.txt
   //ts.test_All();
   
   
   //*******************Comment out hs.askName(name) and menu.MainMenu() in order to test*********
   hs.askName(name);
   menu.MainMenu();

   return 0;
}