/*Filename: project2_Dinh_abd0060.cpp
 * Author: An Dinh (abd0060)
 * Description: COMP 2710 Project 2
 * Compile: g++ project2_Dinh_abd0060.cpp -o Project2.out
 * Run: ./Project2.out
 *
 * References:  project 2 instruction pdf
 * https://www.techieclues.com/blogs/converting-int-to-double-in-cpp
 */
# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>
using namespace std;
// prototypes
/* Functions */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void press_key(void);

/* Test drivers */
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

/* constant variables */
const int total_runs = 10000;
const double Aaron_hit_rate = 33, Bob_hit_rate = 50;
int Aaron_win1 = 0, Bob_win = 0, Charlie_win = 0, Aaron_win2 = 0;
bool Aaron_alive = true, Bob_alive = true, Charlie_alive = true;

int main() {
   cout << "*** Welcome to An's Duel Simulator ***\n";
   srand(time(0));
   test_at_least_two_alive();
   press_key();
   test_Aaron_shoots1();
   press_key();
   test_Bob_shoots();
   press_key();
   test_Charlie_shoots();
   press_key();
   test_Aaron_shoots2();
   press_key();
      
      // Strategy 1
   cout << "Ready to test strategy 1 (run 10000 times):\n";
   press_key();
   for (int i = 0; i < total_runs; i++) {
      Aaron_alive = true;
      Bob_alive = true;
      Charlie_alive = true;
      
      while (at_least_two_alive(Aaron_alive, Bob_alive, Charlie_alive)) {
         if (Aaron_alive) {
            Aaron_shoots1(Bob_alive, Charlie_alive);
         }
         if (Bob_alive) {
            Bob_shoots(Aaron_alive, Charlie_alive);
         }
         if (Charlie_alive) {
            Charlie_shoots(Aaron_alive, Bob_alive);
         }
      }
      if (Aaron_alive) {
         Aaron_win1++;
      }
      if (Bob_alive) {
         Bob_win++;
      }
      if (Charlie_alive) {
         Charlie_win++;
      }
   }  
   cout << "Aaron won " << Aaron_win1 << "/10000 duels or " 
         << static_cast<double>(Aaron_win1)/total_runs * 100 << "%\n"
         << "Bob won " << Bob_win << "/10000 duels or "
         << static_cast<double>(Bob_win)/total_runs * 100 << "%\n"
         << "Charlie won " << Charlie_win << "/10000 duels or "
         << static_cast<double>(Charlie_win)/total_runs * 100 << "%\n"
         << endl;
         
      // Strategy 2
   cout << "Ready to test strategy 2 (run 10000 times):\n";
   Bob_win = 0; // reset the win
   Charlie_win = 0;
   press_key();
   
   for (int i = 0; i < total_runs; i++) {
      Aaron_alive = true;
      Bob_alive = true;
      Charlie_alive = true;
      while (at_least_two_alive(Aaron_alive, Bob_alive, Charlie_alive)) {
         if (Aaron_alive) {
            Aaron_shoots2(Bob_alive, Charlie_alive);
         }
         if (Bob_alive) {
            Bob_shoots(Aaron_alive, Charlie_alive);
         }
         if (Charlie_alive) {
            Charlie_shoots(Aaron_alive, Bob_alive);
         }
      }
      if (Aaron_alive) {
         Aaron_win2++;
      }
      if (Bob_alive) {
         Bob_win++;
      }
      if (Charlie_alive) {
         Charlie_win++;
      }
   
   }
   cout << "Aaron won " << Aaron_win2 << "/10000 duels or " 
         << static_cast<double>(Aaron_win2)/total_runs * 100 << "%\n"
         << "Bob won " << Bob_win << "/10000 duels or "
         << static_cast<double>(Bob_win)/total_runs * 100 << "%\n"
         << "Charlie won " << Charlie_win << "/10000 duels or "
         << static_cast<double>(Charlie_win)/total_runs * 100 << "%\n"
         << endl;

      // Comparison between strategy 1 and strategy 2
   if (Aaron_win1 > Aaron_win2) {
      cout << "Strategy 1 is better than strategy 2.\n";
   }
   else {
      cout << "Strategy 2 is better than strategy 1.\n";
   }
   return 0;
}

// Implementation
/* Implementation of methods */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
   return ((A_alive && B_alive) || (B_alive && C_alive) || (A_alive && C_alive));
}
// Aaron's turn, check for Bob and Charlie status
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
   int shoot_result = rand() % 100;
   
   if (shoot_result <= Aaron_hit_rate) {
      if (C_alive) {
         C_alive = false;
      }
      else {
         B_alive = false;
      }
   }
}
// Bob's turn, check for Aaron and Charlie status
void Bob_shoots(bool& A_alive, bool& C_alive) {
   int shoot_result = rand() % 100;
   
   if (shoot_result <= Bob_hit_rate) {
      if (C_alive) {
         C_alive = false;
      }
      else {
         A_alive = false;
      }
   }
}
// Charlie's turn, check for Aaron and Bob status
void Charlie_shoots(bool& A_alive, bool& B_alive) {
   if (B_alive) {
      B_alive = false;
   }
   else {
      A_alive = false;
   }
}
// Aaron's turn and intentionally miss first shot
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
   int shoot_result = rand() % 100;
   // check if Aaron misses his shot
   if (!B_alive || !C_alive) {
      if (shoot_result <= Aaron_hit_rate) {
         if (C_alive) {
            C_alive = false;
         }
         else {
            B_alive = false;
         }
      }
   }
}
// Pause command
void press_key(void){
   cout << "Press any key to continue...";
   cin.ignore().get();
}

/* Implementation of the test drivers, following user interface */
void test_at_least_two_alive(void) {
   cout << "Unit Testing 1: Function - at_least_two_alive()\n";
   
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
   
   cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
   assert(false == at_least_two_alive(false, false, true));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
   assert(false == at_least_two_alive(false, true, false));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(true, false, false));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(false, false, false));
   cout << "\tCase passed ...\n";
}
void test_Aaron_shoots1(void) {
   cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
   
   cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
   bool Bob_alive = true, Charlie_alive = true;
   Aaron_shoots1(Bob_alive, Charlie_alive);
   assert(true == Bob_alive);
  
   cout << "\tCase 2: Bob dead, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
   Bob_alive = false, Charlie_alive = true;
   Aaron_shoots1(Bob_alive, Charlie_alive);
   assert(false == Bob_alive);

   cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";
   Bob_alive = true; Charlie_alive = false;
   Aaron_shoots1(Bob_alive, Charlie_alive);
   assert(false == Charlie_alive);
}
void test_Bob_shoots(void) {
   cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
   
   cout << "\tCase 1: Aaron alive, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";
   bool Aaron_alive = true, Charlie_alive = true;
   Bob_shoots(Aaron_alive, Charlie_alive);
   assert(true == Aaron_alive);
   
   cout << "\tCase 2: Aaron dead, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";
   Aaron_alive = false, Charlie_alive = true;
   Bob_shoots(Aaron_alive, Charlie_alive);
   assert(false == Aaron_alive);
   
   cout << "\tCase 3: Aaron alive, Charlie dead\n"
         << "\t\tBob is shooting at Aaron\n";
   Aaron_alive = true, Charlie_alive = false;
   Bob_shoots(Aaron_alive, Charlie_alive);
   assert(false == Charlie_alive);
}
void test_Charlie_shoots(void) {
   cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
   
   cout << "\tCase 1: Aaron alive, Bob alive\n"
         << "\t\tCharlie is shooting at Bob\n";
   bool Aaron_alive = true, Bob_alive = true;
   Charlie_shoots(Aaron_alive, Bob_alive);
   assert(false == Bob_alive && true == Aaron_alive);
   
   cout << "\tCase 2: Aaron dead, Bob alive\n"
         << "\t\tCharlie is shooting at Bob\n";
   Aaron_alive = false, Bob_alive = true;
   Charlie_shoots(Aaron_alive, Bob_alive);
   assert(false == Bob_alive && false == Aaron_alive);
   
   cout << "\tCase 3: Aaron alive, Bob dead\n"
         << "\t\tCharlie is shooting at Aaron\n";
   Aaron_alive = true, Bob_alive = false;
   Charlie_shoots(Aaron_alive, Bob_alive);
   assert(false == Bob_alive);
}
void test_Aaron_shoots2(void) {
   cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
   
   cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron intentionally misses his first shot\n"
         << "\t\tBoth Bob and Charlie are alive.\n";
   Aaron_shoots2(Bob_alive, Charlie_alive);
   assert(Bob_alive == true && Charlie_alive == true);
   
   cout << "\tCase 2: Bob dead, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
   bool Bob_alive = false, Charlie_alive = true;
   Aaron_shoots2(Bob_alive, Charlie_alive);
   assert(false == Bob_alive);
   
   cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";
   Bob_alive = true, Charlie_alive = false;
   Aaron_shoots2(Bob_alive, Charlie_alive);
   assert(false == Charlie_alive);
}
