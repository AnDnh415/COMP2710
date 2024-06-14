/*Filename: project3_Dinh_abd0060.cpp
 * Author: An Dinh (abd0060)
 * Description: COMP 2710 Project 3
 * Compile: g++ project2_Dinh_abd0060.cpp -o Project3.out
 * Run: ./Project3.out
 *
 * References:  project 3 instruction pdf
 * https://www.geeksforgeeks.org/merge-sort/
 * https://pages.cs.wisc.edu/~hasti/cs368/CppTutorial/NOTES/IO.html#:~:text=To%20read%20from%20a%20file,you%20can%20read%20or%20write.&text=Note%20that%20to%20use%20files,iostream%20is%20not%20good%20enough).
 */
 #include <fstream>
 #include <iostream>
using namespace std;
 
const int MAX_SIZE = 100;

 // input: (1) Array storing data retrieved from the file
 //        (2) input file stream object
 // output: size of array
int read_file(int input_array[], ifstream& inStream) {
   int index = 0;
   inStream >> input_array[index];
   while (!inStream.eof()) {
      index++;
      inStream >> input_array[index];
   }
   return index;
}

// merging input datas method
void merge(int array[], int l, int m, int r) {
   // first subarray is array[begin...mid]
   // second subarray is array[mid...end]
   int sub_array1 = m - l + 1;
   int sub_array2 = r - m;
   
   //create temp arrays
   int* left_array = new int[sub_array1];
   int* right_array = new int[sub_array2];
   
   // copy data to temp arrays
   for (int i = 0; i < sub_array1; i++) {
      left_array[i] = array[l + i];
   }
   for (int j = 0; j < sub_array2; j++) {
      right_array[j] = array[m + 1 + j];
   }
   
   int index_sub1 = 0, index_sub2 = 0, index_merge = l;
   // merge the temp arrays back into array[left...right]
   while (index_sub1 < sub_array1 && index_sub2 < sub_array2) {
      if (left_array[index_sub1] <= right_array[index_sub2]) {
         array[index_merge] = left_array[index_sub1];
         index_sub1++;
      }
      else {
         array[index_merge] = right_array[index_sub2];
         index_sub2++;
      }
      index_merge++;
   }
   
   // copy the remaining elements of left[] if there any
   while (index_sub1 < sub_array1) {
      array[index_merge] = left_array[index_sub1];
      index_sub1++;
      index_merge++;
   }
   // copy the remaining elements of right[] if there any
   while (index_sub2 < sub_array2) {
      array[index_merge] = right_array[index_sub2];
      index_sub2++;
      index_merge++;
   }
   delete[] left_array;
   delete[] right_array;
}

// merging and sorting method
void merge_sort(int array[], int l, int r) {
   if (l < r) {
      int m = l + (r - l) / 2;
      
      merge_sort(array, l, m);
      merge_sort(array, m + 1, r);
      
      merge(array, l, m, r);
   }
}

 // output array size
int sort(int array1[], int array1_size, int array2[], int array2_size, int output_array[]) {
   int output_array_size = array1_size + array2_size;
   
   //add elements in array1 to output array
   for (int i = 0; i < array1_size; i++) {
      output_array[i] = array1[i];
   }
   // add elements in array 2 to output array after adding array1's
   for (int i = 0; i < array2_size; i++) {
      output_array[i + array1_size] = array2[i];
   }
   
   merge_sort(output_array, 0, output_array_size - 1);
   return output_array_size;
}

// write output file
void writefile(int output_array[], int output_array_size) {
   ofstream outstream;
   string output_filename;
   cout << "Enter the output file name: ";
   cin >> output_filename;
   
   outstream.open((char*)output_filename.c_str());
   for(int i = 0; i < output_array_size; i++) {
      outstream << output_array[i] << "\n";
   }
   outstream.close();
   
   cout << "*** Please check the new file - " << output_filename << " ***\n";
}

int main() {
   int iArray1[MAX_SIZE];
   int iArray1_size;
   int iArray2[MAX_SIZE];
   int iArray2_size;
   
   cout << endl << "*** Welcome to An's sorting program ***\n";
   
   ifstream instream;
   string filename1;
   bool valid_file1 = false;
   while (!valid_file1) {
      cout << "Enter the first input file name: ";
      cin >> filename1;
      
      // pass the file name as an array of chars to open()
      // instream.open(filename);
      instream.open((char*)filename1.c_str());
      valid_file1 = instream.good();
      if (!valid_file1) {
         cout << "Input file opening failed.\n" << endl;
      }
   }
   
   iArray1_size = read_file(iArray1, instream);
   instream.close();
   
   cout << "The list of " << iArray1_size << " numbers in file "
      << filename1 << " is: \n";
   for (int i = 0; i < iArray1_size; i++) {
      cout << iArray1[i] << "\n";
   }
   cout << endl;
   
   string filename2;
   bool valid_file2 = false;
   while (!valid_file2) {
      cout << "Enter the second input file name: ";
      cin >> filename2;
      
      instream.open((char*)filename2.c_str());
      valid_file2 = instream.good();
      if (!valid_file2) {
         cout << "Input file opening failed.\n" << endl;
      }
   }
   
   iArray2_size = read_file(iArray2, instream);
   instream.close();
   
   cout << "The list of " << iArray2_size << " numbers in file "
      << filename2 << " is: \n";
   for (int i = 0; i < iArray2_size; i++) {
      cout << iArray2[i] << "\n";
   }
   cout << endl;
   
   int output_array[MAX_SIZE];
   int output_array_size = sort(iArray1, iArray1_size, iArray2, iArray2_size, output_array);
   
   cout << "The sorted list of " << output_array_size << " numbers is: ";
   for (int i = 0; i < output_array_size; i++) {
      cout << output_array[i] << " ";
   }
   cout << endl;
   
   writefile(output_array, output_array_size);
   cout << "*** Goodbye. ***" << endl;
   return 0;
}