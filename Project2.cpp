// name: Blake Schilleci, wbs0013
// partner: Will Bianca, wcb0020
// filename: Project2.cpp
// due date: 12/07/2018
// collaboration: We did not use any external sources for this assignment.
// Project: A program to create a secure teller terminal system for a bank.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using std::cin; 

class Bank {
      public:
   void quit();   
   void login();
   void menu();
   string user;
   string admin;
   string password;
   string role;
   int index;
   string array[100];
   string users[100];
   string passwords[100];
   string roles[100];
      private:
   int option;
};

void Bank::quit() {
   cout << "Now exiting the Teller Terminal System" << endl;
   cout << "Thank you!";
   exit(0);
}

void Bank::login() {
   index = 0;
   
   ifstream infile("staff.txt");
   infile >> array[index];
   while (! infile.eof()) {
      index++;
      infile >> array[index];
   } 
   infile.close();
   
   for (int i = 0; i <= index; i++) {      
      string x = array[i];
      int pos = x.find("-");
      string u = x.substr(0, pos);
      users[i] = u;
      int pos2 = x.find("_");
      string p = x.substr(pos + 1, pos2 - (pos + 1));
      passwords[i] = p;
      string r = x.substr(pos2 + 1);
      roles[i] = r;
   }
   
   cout << "\t============================================================\n";
   cout << "\t|        Login to Access the Teller Terminal System        |\n";
   cout << "\t============================================================\n";
   cout << "User Name: ";
   cin >> user;
   cout << "Password: ";
   cin >> password;
   int j = 0;
   while (j <= index) {
      if (user == users[j] && password == passwords[j]) {
         role = roles[j];
         break;
      }
      else if  (j == index) {
         cout << "\nThe user name or password is incorrect. Try again!\n";
         login();
      }
      else {
         j++;
      }
   }                

}        
 
void Bank::menu() {
   cout << "\t============================================================\n";
   cout << "\t|       Welcome to the Auburn Branch of Tiger Bank!        |\n";
   cout << "\t============================================================\n";
   cout << "1) Login\n";
   cout << "2) Quit\n";
   cout << "\tPlease choose an option: ";
   cin >> option;
   if (option == 1) {
      login(); 
   } 
   else if (option == 2) {
      quit();
   }
   else {
      cout << "Please try again.\n";
      menu();
   }
} 

class Client {
      public:
   void clientMenu();   
   void addClient();
   void addAccount();
   void editClient();
   void manageAccount();
   void saveClient();
   void saveAccounts();
   void readClient();
   void readAccounts();
   int read_count = 0;
      private:
   int index;
   string array[100];
   string names[100];
   string addresses[100];
   string ssNumbers[100];
   string employers[100];
   string incomes[100];
   int accIndex;
   string accArray[100];
   string accNames[100];
   string accNumbers[100];
   string accTypes[100];
   string balances[100];   
   int client_op;      
   Bank bn;
};

void Client::clientMenu() {
   if (read_count == 0) { //Ensure that client info and account info are read once and at beginning of running program
      readClient();
      readAccounts();
   }
   read_count++;
   
   cout << "\t============================================================\n";
   cout << "\t|  Teller Terminal System - Client and Account Management  |\n";
   cout << "\t============================================================\n";   
   cout << "\n1) Add a client\n";
   cout << "2) Add an account\n";
   cout << "3) Edit Client Information\n";
   cout << "4) Manage an account\n";
   cout << "5) Save Client and Account Information\n";
   cout << "6) Exit\n";
   cout << "Please choose an option: ";
   cin >> client_op;
   
   if (client_op == 1) {
      addClient();
   }
   
   else if (client_op == 2) {
      addAccount();
   }
   
   else if (client_op == 3) {
      editClient();
   }
   
   else if (client_op == 4) {
      manageAccount();
   }
   
   else if (client_op == 5) {
      saveClient();
      saveAccounts();
   }
   
   else if (client_op == 6) {
      bn.quit();
   }
   else {
      cout << "Option must be a single number, 1 - 6.\n\n";
      clientMenu();
   }         
} 

void Client::addClient() {
   string new_name;
   string new_address;
   string new_ss;
   string new_employer;
   string new_income;
   
   cout << "A new client will be added: \n";
   cout << "Client name: ";
   std::cin.ignore();
   std::cin.sync();
   std::getline(cin, new_name);
   names[index] = new_name;
   
   cout << "Address: ";
   std::cin.sync();
   std::getline(cin, new_address);
   addresses[index] = new_address;
   
   cout << "Social security number: ";
   std::cin.sync();
   std::getline(cin, new_ss);
   ssNumbers[index] = new_ss;
   
   cout << "Employer: ";
   std::cin.sync();
   std::getline(cin, new_employer);
   employers[index] = new_employer;
   
   cout << "Annual income: ";
   std::cin.sync();
   std::getline(cin, new_income);
   incomes[index] = new_income;
   index++;
   
   cout << "A new client was added!\n";
   cout << "Press any key to continue...";
   cin.ignore().get();
   
   clientMenu();
} 

void Client::addAccount() {
   string acc_name;
   string acc_number;
   string acc_type;
   string acc_balance;
   int f;
   
   cout << "Choose a client: ";
   std::cin.ignore();
   std::cin.sync();
   std::getline(cin, acc_name);
   
   for (f = 0; f <= index; f++) {
      if (names[f] == acc_name) {
         accNames[accIndex] = acc_name;
         break;
      }   
      else if (f == index && names[f] != acc_name) {
         cout << "Error - The client is not in the system.\n";
         cout << "1) Add Account\n";
         cout << "2) Return to client menu\n";
         cout << "Please choose an option: ";
         int add_op;
         cin >> add_op;
         if (add_op == 1) {
            addAccount();
         }
         else {
            clientMenu();
         }      
      } 
   }
   
   cout << "A new account will be created for " << acc_name << " ...\n";
   cout << "Account Number: ";
   std::cin.sync();
   std::getline(cin, acc_number); 
   accNumbers[accIndex] = acc_number;
   
   cout << "Account Type: ";
   std::cin.sync();
   std::getline(cin, acc_type);
   accTypes[accIndex] = acc_type;
   
   cout << "Balance: ";
   std::cin.sync();
   std::getline(cin, acc_balance);
   balances[accIndex] = acc_balance;
   accIndex++;

   cout << "A new account was created for " << acc_name << "!\n";
   cout << "Press any key to continue... ";
   cin.ignore().get();
   clientMenu();
}   

void Client::editClient() {
   string edit_name;
   string edit_add;
   string edit_ss;
   string edit_emp;
   string edit_inc;
   int edit_op;
   int find;
   
   cout << "Choose a client: ";
   std::cin.ignore();
   std::cin.sync();
   std::getline(cin, edit_name); 
   
   for (find = 0; find <= index; find++) {
      if (names[find] == edit_name) {
         break;
      }   
      else if (find == index && names[find] != edit_name) {
         cout << "Error - The client is not in the system.\n";
         editClient();
      } 
   } 
   
   cout << "Client " << edit_name << "'s information will be updated ...\n";
   cout << "1) Confirm\n";
   cout << "2) Cancel\n";
   cout << "Please choose an option: ";
   cin >> edit_op;
   
   if (edit_op == 1) {
      cout << "Address: ";
      std::cin.ignore();
      std::cin.sync();
      std::getline(cin, edit_add);
      addresses[find] = edit_add; 
      
      cout << "Social Security number: ";
      std::cin.sync();
      std::getline(cin, edit_ss);
      ssNumbers[find] = edit_ss;
      
      cout << "Employer: ";
      std::cin.sync();
      std::getline(cin, edit_emp);
      employers[find] = edit_emp;
      
      cout << "Annual Income: ";
      std::cin.sync();
      std::getline(cin, edit_inc);
      incomes[find] = edit_inc;
      
      cout << "Client " << edit_name << "'s information was updated!\n";
      cout << "Don't forget to save client info from the client menu!\n";
      cout << "Press any key to continue...";
      cin.ignore().get();
      
      clientMenu();
   }
   
   else {
      clientMenu();
   }
} 

void Client::manageAccount() {
   string man_number;
   int man_option; 
   int man_op;
   int bal_op;
   
   cout << "Which account will be managed? ";
   cin >> man_number;
   for (int g = 0; g <= accIndex; g++) {
      if (accNumbers[g] == man_number) {
         bal_op = g;
         break;
      }   
      else if (g == accIndex && accNumbers[g] != man_number) {
         cout << "Error - Account " << man_number << " is not in the system!\n";
         cout << "1) Manage an account\n";
         cout << "2) Cancel\n";
         cout << "Please choose an option: ";
         cin >> man_option;
         if (man_option == 1) {
            manageAccount();
         }
         else {
            clientMenu();
         }      
      } 
   }
   
   int int_bal;
   string s_bal = balances[bal_op];
   istringstream(s_bal) >> int_bal; 
   
   cout << "Manage account " << man_number << " for " << accNames[bal_op] << "\n";
   cout << "1) Deposit\n";
   cout << "2) Withdraw\n";
   cout << "3) Cancel\n";
   cout << "Please choose an option: ";
   cin >> man_op;
   
   if (man_op == 1) {
      int dep;
      cout << "Deposit Amount: ";
      cin >> dep;
      int_bal += dep;
      cout << "Balance of account " << man_number << " is: " << int_bal << "\n";;
      string s_dep; 
      s_dep += std::to_string(int_bal);
      balances[bal_op] = s_dep;
      cout << "Returning to client menu. Don't forget to save!\n";
      cout << "Press any key to continue...";
      cin.ignore().get();
      clientMenu();
   } 
   
   else if (man_op == 2) {
      int wit;
      cout << "Withdraw Amount: ";
      cin >> wit;
      if (wit > int_bal) {
         cout << "Your withdrawl cannot be more then your balance, which is " << int_bal << "\n";
         cout << "Please try again!\n";
         manageAccount();
      }    
      int_bal -= wit;
      cout << "Balance of account " << man_number << " is: " << int_bal << "\n";
      string s_wit;
      s_wit += std::to_string(int_bal);
      balances[bal_op] = s_wit;
      cout << "Returning to client menu. Don't forget to save!\n";
      cout << "Press any key to continue...";
      cin.ignore().get();
      clientMenu();
   }    
   
}               

void Client::saveClient() {
   remove("client-info.txt");
   ofstream outfile("client-info.txt");
   
   for (int b = 0; b <= index; b++) {
      if (b == index) {
         break;
      }   
      outfile << names[b] << "-" << addresses[b] << "_" << ssNumbers[b] << "=" << employers[b] << "+" << incomes[b];
      if (b < index) {
         outfile << "\n";
      }   
   }   
   outfile.close();
   
   readClient();
}

void Client::saveAccounts() {
   remove("account-info.txt");
   ofstream outstream("account-info.txt");
   
   for (int c = 0; c <= accIndex; c++) {
      if (c == accIndex) {
         break;
      }   
      outstream << accNames[c] << "-" << accNumbers[c] << "_" << accTypes[c] << "=" << balances[c];
      if (c < accIndex) {
         outstream << "\n";
      }
   }
   outstream.close(); 
   
   readAccounts();     
   
   cout << "Client information has been saved in the client-info file; account \n";
   cout << "information has been saved in the account-info file!\n";
   cout << "Press any key to continue...";
   cin.ignore().get();
   
   clientMenu();
}

void Client::readClient() {
   index = 0;
   
   ifstream infile("client-info.txt");
   string content;
   while (std::getline(infile, content)) {   
      array[index] = content;
      index++;
   }   
   infile.close();
   
   for (int i = 0; i <= index; i++) {      
      string x = array[i];
      int pos = x.find("-");
      string n = x.substr(0, pos);
      names[i] = n;
      int pos2 = x.find("_");
      string add = x.substr(pos + 1, pos2 - (pos + 1));
      addresses[i] = add;
      int pos3 = x.find("=");
      string ss = x.substr(pos2 + 1, pos3 - (pos2 + 1));
      ssNumbers[i] = ss;
      int pos4 = x.find("+");
      string emp = x.substr(pos3 + 1, pos4 - (pos3 + 1));
      employers[i] = emp;
      string inc = x.substr(pos4 + 1);
      incomes[i] = inc;
   }
}   

void Client::readAccounts() {  
   accIndex = 0;
   
   ifstream instream("account-info.txt");
   string accContent;
   while (std::getline(instream, accContent)) {  
      accArray[accIndex] = accContent;
      accIndex++;
   }   
   instream.close();
   
   for (int j = 0; j <= accIndex; j++) {
      string acc = accArray[j];
      int posn = acc.find("-");
      string na = acc.substr(0, posn);
      accNames[j] = na;
      int posn2 = acc.find("_");
      string nmbr = acc.substr(posn + 1, posn2 - (posn + 1));
      accNumbers[j] = nmbr;
      int posn3 = acc.find("=");
      string type = acc.substr(posn2 + 1, posn3 - (posn2 + 1));
      accTypes[j] = type;
      string bal = acc.substr(posn3 + 1);
      balances[j] = bal;
   }
}                  

class Admin {
      public:
   void admin_menu();
   void changePassword();
   void addStaff();
   void displayStaff();
   void deleteStaff();
   void manage();
   string admin_user;
   string admin_pass;
      private:
   void save();
   void readFile();
   int admin_op;
   int index;
   string array[100];
   string users[100];
   string passwords[100];
   string roles[100];
   Bank bn;
   Client cln;
};

void Admin::admin_menu() {
   cout << "\t============================================================\n";
   cout << "\t|      Teller Terminal System - System Administration      |\n";
   cout << "\t============================================================\n";
   cout << "\n1) Client and Account Management\n";
   cout << "2) Add a branch staff member\n";
   cout << "3) Delete a branch staff member\n";
   cout << "4) Display branch staff\n";
   cout << "5) Change password\n";
   cout << "6) Exit\n";
   cout << "Please choose an option: ";
   cin >> admin_op;
   
   if (admin_op == 1) {
      cln.clientMenu();
   }
   
   if (admin_op == 2) {
      addStaff();
   }
   
   if (admin_op == 3) {
      deleteStaff();
   }
   
   if (admin_op == 4) {
      displayStaff();
   }
   
   if (admin_op == 5) {
      changePassword();
   }
   
   if (admin_op == 6) {
      bn.quit();
   }
}      

void Admin::changePassword() {
   readFile();

   string new_pass; 
   cout << "Enter your user name: ";
   cin >> admin_user;
   cout << "Enter your old password: ";
   cin >> admin_pass;
   cout << "\n";
   
   cout << "New Password: ";
   cin >> new_pass;
   if (new_pass == admin_pass) {
      cout << "\nError - Your new password must be different from the old one!\n";
      changePassword();
   }
   else {
      for (int k = 0; k <= index; k++) {
         if (users[k] == admin_user) {
            passwords[k] = new_pass;
            cout << "Password was changed!\n";
            save();
            admin_menu();
         }
      }
   }           
}       

void Admin::addStaff() {
   readFile();

   string newUser;
   string newPass;
   index++;
   
   cout << "Adding a new branch staff member...\n";
   cout << "User Name: ";
   cin >> newUser;
   users[index] = newUser;
   
   cout << "Password: ";
   cin >> newPass;
   passwords[index] = newPass;
   
   roles[index] = "BranchStaff";
   
   array[index] = newUser + "-" + newPass + "_BranchStaff";
   cout << "Branch member added. Returning to menu.\n\n";
   
   save();
   
   admin_menu();
} 

void Admin::displayStaff() {
   readFile();
   
   cout << "There are " << index + 1 << " users in the system.\n";
   
   for (int i = 0; i <= index; i++) {
      cout << i + 1 << ". User Name: ";
      cout << users[i] << "\t";
      if (roles[i] == "BranchStaff") {
         cout << "Role: Branch Staff\n";
      }
      else {
         cout << "Role: System Administrator\n";
      }      
   }

   cout << "Press any key to continue...";
   cin.ignore().get();
   admin_menu();
}

void Admin::deleteStaff() {
   readFile();

   string del_user;
   int del_option;
   cout << "Delete a user - User Name: ";
   cin >> del_user;
   cout << "1) Confirm\n";
   cout << "2) Cancel\n";
   cout << "Please choose an option: ";
   cin >> del_option;
   if (del_option == 1) {
      for (int a = 0; a <= index; a++) {
         if (users[a] == del_user) {
            while (a < index) {
               users[a] = users[a+1];
               a++;
            }
            cout << "User " << del_user << " was deleted!\n";
            cout << "Press any key to continue...";
            cin.ignore().get();
            index--;
            save();
            admin_menu();
         }
         else if (a == index) {
            cout << "Warning - User " << del_user << " is not in the system. No user is deleted!\n\n";
            deleteStaff();
         }
      }
   }              
   else if (del_option == 2) {
      admin_menu();
   }
   else {
      cout << "Option must be either a 1 or a 2.\n\n";
      deleteStaff();
   }
}      
      

void Admin::save() {
   remove("staff.txt");
   ofstream outfile("staff.txt");
   
   for (int x = 0; x <= index; x++) {
      outfile << users[x] << "-" << passwords[x] << "_" << roles[x];
      if (x < index) {
         outfile << "\n";
      }   
   }   
   outfile.close();
} 

void Admin::readFile() {
   index = 0;
   
   ifstream infile("staff.txt");
   infile >> array[index];
   while (! infile.eof()) {
      index++;
      infile >> array[index];
   } 
   infile.close();
   
   for (int i = 0; i <= index; i++) {      
      string x = array[i];
      int pos = x.find("-");
      string u = x.substr(0, pos);
      users[i] = u;
      int pos2 = x.find("_");
      string p = x.substr(pos + 1, pos2 - (pos + 1));
      passwords[i] = p;
      string r = x.substr(pos2 + 1);
      roles[i] = r;
   }
}            

class Staff {
      public:
   void staff_menu();
   void changePassword();
   void manage();
   void save();
   string staff_user;
   string staff_pass;
      private:
   void readFile();
   int staff_op;
   int index;
   string array[100];
   string users[100];
   string passwords[100];
   string roles[100];
   Bank bn;
   Client cln;
};

void Staff::staff_menu() {
   cout << "\t============================================================\n";
   cout << "\t|           Teller Terminal System - Branch Staff          |\n";
   cout << "\t============================================================\n";
   cout << "\n1) Client and Account Management\n";
   cout << "2) Change password\n";
   cout << "3) Exit\n";
   cout << "Please choose an option: ";
   cin >> staff_op;
   
   if (staff_op == 1) {
      cln.clientMenu();
   }
   
   if (staff_op == 2) {
      changePassword();
   }
   
   if (staff_op == 3) {
      bn.quit();
   }
}    

void Staff::changePassword() { 
   readFile();

   string new_pass; 
   cout << "Enter your user name: ";
   cin >> staff_user;
   cout << "Enter your old password: ";
   cin >> staff_pass;
   cout << "\n";
   
   cout << "New Password: ";
   cin >> new_pass;
   if (new_pass == staff_pass) {
      cout << "\nError - Your new password must be different from the old one!\n";
      changePassword();
   }
   else {
      for (int k = 0; k <= index; k++) {
         if (users[k] == staff_user) {
            passwords[k] = new_pass;
            cout << "Password was changed!\n";
            save();
            staff_menu();
         }
      }
   }           
}

void Staff::save() {
   remove("staff.txt");
   ofstream outfile("staff.txt");
   
   for (int x = 0; x <= index; x++) {
      outfile << users[x] << "-" << passwords[x] << "_" << roles[x];
      if (x < index) {
         outfile << "\n";
      }   
   }   
   outfile.close();
} 

void Staff::readFile() {
   index = 0;
   
   ifstream infile("staff.txt");
   infile >> array[index];
   while (! infile.eof()) {
      index++;
      infile >> array[index];
   } 
   infile.close();
   
   for (int i = 0; i <= index; i++) {      
      string x = array[i];
      int pos = x.find("-");
      string u = x.substr(0, pos);
      users[i] = u;
      int pos2 = x.find("_");
      string p = x.substr(pos + 1, pos2 - (pos + 1));
      passwords[i] = p;
      string r = x.substr(pos2 + 1);
      roles[i] = r;
   }
}    

int main() {
   Bank bn;
   Admin adm;
   Staff stf;
   Client cln;
   
   bn.menu();
   if (bn.role == "SystemAdministrator") {
      adm.admin_menu();
   }
   if (bn.role == "BranchStaff") {
      stf.staff_menu();
   }         
   
   return 0;
}