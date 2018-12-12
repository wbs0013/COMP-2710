#include <iostream>
using namespace std;
class Doctor{
private:
   string name;
   int numPatients;
   string* patientList;
public:
   Doctor();
   string getName();
   void setName(string n);
   int getNumPatients();
   string* getPatientList();
   void input();
   void display();
   void reset();
   Doctor& operator = (const Doctor &d);
   ~Doctor();
};

Doctor::Doctor(){
   name = "";
   numPatients = 0;
   patientList = nullptr;
}
string Doctor::getName(){
   return name;
}
void Doctor::setName(string n){
   name = n;
}
int Doctor::getNumPatients(){
   return numPatients;
}
string* Doctor::getPatientList(){
   return patientList;
}
void Doctor::input(){
   cout << "Enter doctor's name: ";
   cin >> name;
   cout << "How many patients? ";
   cin >> numPatients;
   patientList = new string[numPatients];
   for(int i = 1; i <= numPatients; i++)
   {
      cout << "Name of patient " << i << "? ";
      cin >> patientList[i-1];
   }
}
void Doctor::display(){
   cout << "Doctor: " << name << endl;
   cout << "List of patients:" << endl;
   for(int i = 0; i < numPatients; i++)
      cout << patientList[i] << endl;
   cout << "---------------" << endl;
}
void Doctor::reset(){
   numPatients = 0;
   if(patientList != nullptr)
   {
      delete []patientList;
      patientList = nullptr;
   }
}
Doctor& Doctor::operator = (const Doctor &d){
   if(this != &d){
      reset();
      name = d.name;
      numPatients = d.numPatients;
      if(numPatients != 0){
         patientList = new string[numPatients];
         for(int i = 0; i < numPatients; i++)
            patientList[i] = d.patientList[i];
      }
   }
   return *this;
}

Doctor::~Doctor(){
   if(patientList != nullptr)
      delete []patientList;
}
int main(){
   Doctor d1, d2;
   d1.input();
   cout << endl << "Displaying d1" << endl;
   d1.display();
   cout << "Assigning d1 to d2" << endl;
   d2 = d1;
   cout << "Resetting d1" << endl;
   d1.reset();
   cout << endl << "Displaying d1" << endl;
   d1.display();
   cout << endl << "Displaying d2" << endl;
   d2.display();
}