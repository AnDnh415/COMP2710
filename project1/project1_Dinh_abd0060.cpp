/*Filename: project1_Dinh_abd0060.cpp
 * Author: An Dinh (abd0060)
 * Description: COMP 2710 Project 1
 * Compile: g++ project1_Dinh_abd0060.cpp -o Project1.out
   * Run: ./Project1.out
   *
 * Program calculates the total amount of interest paid yearly
 * and the size of the debt after each month.
 * Outputs an amortization table based on user input.
 *
 * References: lectures in class and 
 * sample solution for similar problem from 
 * https://cplusplus.com/forum/general/14990/
 */

#include <iostream>
using namespace std;

int main() {
   // Currency formatting
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   
   // Variable initialization
   // Set variables -1 so it checks user inputs are positive numbers
   double loan = -1;
   double interest = -1;
   double monthly_payments = -1;
   int current_month = 0;
   double interest_total = 0;
   
   // Get loan and interest rate input
   // A loop ask for input until it is valid
   while (loan <= 0) {
      cout << "\nLoan Amount: ";
      cin >> loan;
   }
   while (interest <= -1) {
      cout << "Interest Rate (% per year): ";
      cin >> interest;
   }
   
   // Caculate interest per month
   double interest_rate_monthly = interest / 12;
   double interest_rate = interest_rate_monthly / 100;
   
   // Check for regular payment are larger than any monthly interest
   while (monthly_payments <= 0 || monthly_payments <= loan * interest_rate) {
      cout << "Monthly Payments: ";
      cin >> monthly_payments;
   }
   cout << endl;
   
   // Amortization table
   cout << "**********************************************************\n"
        << "\tAmortization Table\n"
        << "**********************************************************\n"
        << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
   
  // Loop to fill table
   while (loan > 0) {
      if (current_month == 0) {
         cout << current_month++ << "\t$" << loan;
         if (loan < 1000) {
            cout << "\t";
         }
         cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
      }
      else {
         // Calculate monthly interest and total interest before deducting
         double monthly_interest = loan * interest_rate;
         double principal = monthly_payments - monthly_interest;
         
         if (principal >= loan) {
            monthly_payments = loan + monthly_interest;
            principal = loan;
         }
         loan -= principal;
         interest_total += monthly_interest;
         
         // Display the information in the table
         cout << current_month++ << "\t$" << loan << "\t";
         if (loan < 1000) {
            cout << "\t";
         }
         cout << "\t$" << monthly_payments << "\t"
              << interest_rate_monthly << "\t"
              << "$" << monthly_interest << "\t"
              << "$" << principal << "\n";
      }
   }
   cout << "**********************************************************\n";
   cout << "\nIt takes " << --current_month 
        << " months to pay off the loan.\n"
        << "Total interest paid is: $" << interest_total;
   cout << endl << endl;
   return 0;
}