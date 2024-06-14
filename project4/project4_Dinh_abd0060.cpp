/*Filename: project4_Dinh_abd0060.cpp
 * Author: An Dinh (abd0060)
 * Description: COMP 2710 Project 4
 * Compile: g++ project4_Dinh_abd0060.cpp -o Project4.out
 * Run: ./Project4.out
 *
 * References:  project 4 instruction pdf, lecture chapter 5,
 * https://www.geeksforgeeks.org/cpp-program-for-inserting-a-node-in-a-linked-list/
 * https://www.geeksforgeeks.org/cpp-pointers/
 * https://eng.libretexts.org/Courses/Delta_College/C___Programming_I_(McClanahan)/
 * 11%3A_C_Input_and_Output/11.02%3A_C_Input-_getline()#:~:text=in%20C%2B%2B-,getline%20(string)%20in%20C%2B%2B,the%20delimiting%20character%20is%20encountered.
 */
 #include <iostream>
 #include <string>
 #include <assert.h>
using namespace std;
int total = 0;
int quiz_length = 0;

struct TriviaNode {
   string question;
   string answer;
   int point;
   TriviaNode *next;
   
   public:
   TriviaNode (string q, string a, int p, TriviaNode *n) {
      question = q;
      answer = a;
      point = p;
      next = n;
   }
};
 
 // default questions for testing
TriviaNode* default_trivia_questions() {
   string question_in = "How long was the shortest war on record? (Hint: how many minutes)";
   string answer_in = "38";
   int point_in = 100;
   TriviaNode* t1_pointer = new TriviaNode(question_in, answer_in, point_in, NULL);
   
   question_in = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
   answer_in = "Bank of Italy";
   point_in = 50;
   TriviaNode* t2_pointer = new TriviaNode(question_in, answer_in, point_in, NULL);
   
   question_in = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?";
   answer_in = "Wii Sports";
   point_in = 20;
   TriviaNode* t3_pointer = new TriviaNode(question_in, answer_in, point_in, NULL);
   
   // link the nodes as a list and set the quiz length
   t1_pointer -> next = t2_pointer;
   t2_pointer -> next = t3_pointer;
   quiz_length = 3;
   return t1_pointer;
}

// create new TriviaNode and add the new node to the end of linked list quiz
void add_questions(TriviaNode &linked_list) {
   TriviaNode* new_node = new TriviaNode("", "", -1, NULL);
   TriviaNode* current_node = &linked_list;
   
   cout << "Enter a question: ";
   getline(cin, new_node -> question);
   cout << "Enter an answer: ";
   getline(cin, new_node -> answer);
   cout << "Enter award points: ";
   // check input point condition
   while (new_node -> point <= 0) {
      if (!(cin >> new_node -> point)) {
         cout << "Please enter positive integer.\n Enter award points: ";
         cin.clear();
         cin.ignore();
      }
      else if (new_node -> point <= 0) {
         cout << "Please enter positive integer.\n Enter award points: ";
      }
   }
   // if the linked list is empty, create new node
   if (quiz_length == 0) {
      linked_list = *new TriviaNode(new_node -> question, new_node -> answer, new_node -> point, NULL);
      quiz_length++;
      return;
   }
   
   // link the node after adding the new node to the end of the list
   while (current_node -> next != NULL) {
      current_node = current_node -> next;
   }
   current_node -> next = new_node;
   quiz_length++;
}

//ask questions from the list; if correct, user gets the point
void ask_question(TriviaNode* trivia_list_ptr, int question_number) {
   TriviaNode* current_node_ptr = trivia_list_ptr;
   string user_input;
   
   if (trivia_list_ptr == NULL || quiz_length == 0) {
      return;
   }
   // empty quiz case
   else if (question_number < 1) {
      cout << "\nWarning - the number of trivia to be asked must equal to or be larger than 1.";
      return;
   }
   //exceed the list case
   else if (quiz_length < question_number) {
      cout << "\nWarning - there is only " << quiz_length << " trivia available in the list.\n";
      return;
   }
   else {
      int i = 0;
      while (i < question_number) {
         cout << "\nQuestion: " << current_node_ptr -> question;
         cout << "\nAnswer: ";
         getline(cin, user_input);
         if (user_input.compare(current_node_ptr -> answer) == 0) {
            cout << "Your answer is correct. You receive " << current_node_ptr -> point << " points.";
            total += current_node_ptr -> point;
         }
         else {
            cout << "Your answer is wrong. The correct answer is: " << current_node_ptr -> answer;
         }
         cout << "\nYour total points: " << total << endl;
         i++;
         current_node_ptr = current_node_ptr -> next;
      }
      return;
   }
}
#define UNIT_TESTING
#ifdef UNIT_TESTING
int main() {
   TriviaNode* default_trivia_list = default_trivia_questions();
   cout << "*** This is a debugging version ***" 
      << "\nUnit Test Case 1: Ask no question. The program should give a warning message.";
   ask_question(default_trivia_list, 0);
   cout << "\nCase 1 Passed\n";
   
   cout << "\nUnit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.";
   ask_question(default_trivia_list, 1);
   assert(total == 0);
   cout << "\nCase 2.1 passed\n";
   
   cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.";
   ask_question(default_trivia_list, 1);
   assert(total == 100);
   cout << "\nCase 2.2 passed\n";
   total = 0;
   
   cout << "\nUnit Test Case 3.1: Ask all the questions of the last trivia in the linked list. The tester enters all wrong answers";
   ask_question(default_trivia_list, 3);
   assert(total == 0);
   cout << "\nCase 3.1 passed\n";
   
   cout << "\nUnit Test Case 3.2: Ask all the questions of the last trivia in the linked list. The tester enters all correct answers";
   ask_question(default_trivia_list, 3);
   assert(total == 170);
   cout << "\nCase 3.2 passed\n";
   
   cout << "\nUnit Test Case 4: Ask 5 questions in the linked list.";
   ask_question(default_trivia_list, 5);
   cout << "\nCase 4 passed\n";
   
   cout << "\n*** End of the Debugging Version ***\n";
   return 0;
}
#else
int main() {
   bool user_continue = true;
   string user_input = "";
   TriviaNode* quiz_list = new TriviaNode("", "", -1, NULL); // instantiate a blank node
   cout << "*** Welcome to An's trivia quiz game ***\n";
   do {
      add_questions(*quiz_list);
      cout << "Continue? (Yes/No): ";
      cin >> user_input;
     
      while (true) {
         if (user_input == "no" || user_input == "No" || user_input == "NO") {
            user_continue = false;
            cin.clear();
            cin.ignore();
            break;
         }
         else if (user_input == "yes" || user_input == "Yes" || user_input == "YES") {
            cin.clear();
            cin.ignore();
            break;
         }
         else {
            cout << "Please enter \"Yes\" or \"No\": ";
            cin >> user_input;
            continue;
         }
      }
   } while (user_continue == true);
   
   ask_question(quiz_list, quiz_length);
   cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
   return 0;
}
#endif