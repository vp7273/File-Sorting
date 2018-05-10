//	CS	1337.003	Project	1	<vxp171430>	<Varika Pinnam>

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

void swap(double &element1, double &element2);

int main()
{
   string filename;
   ifstream matrixfile;
   char userselection; //variable outside do while loop to be accessed at end

   do {
      cout << "Enter the file name: ";
      cin >> filename;


      int rows, columns;

      matrixfile.open(filename);

      while (!matrixfile)
      {
         cout << "The file did not open." << endl;
         cout << "Enter the file name: ";
         cin >> filename;
         matrixfile.open(filename);
      }


      matrixfile >> rows; //first number in the file

     while (rows > 20)//ask user for different file
      {

        cout << "The file contains an invalid number of rows greater than 20" << endl;
         matrixfile.close();
         cout << "Enter the file name: ";
         cin >> filename;
         matrixfile.open(filename);
         matrixfile >> rows;

      }


      matrixfile >> columns; //second number in the file


     while  (columns > 20)
      {

         cout << "The file contains an invalid number of columns greater than 20" << endl;
         matrixfile.close();
         cout << "Enter the file name: ";
         cin >> filename;
         matrixfile.open(filename);
         matrixfile >> columns;

      }

      //initializing array with elements from file out of order

      //dynamic allocation because array size is not constant;it's file specified
      double *arr = new double[rows*columns];

      int count = 0;//keep track of elements taken from file

      for (int row = 0; row < rows; ++row)
      {
         for (int column = 0; column < columns; ++column)
         {

            if (matrixfile >> arr[row * columns + column])
               count++;
         }

      }

      int sizeofmatrix = rows*columns;
      //processes program but message to user that some elements are missing
      if (count < sizeofmatrix)
      {
         cout << "The file contained only " << count << " elements.";
         cout << " It did not fill the specified array of size ";
         cout << rows << "x" << columns << endl;
      }

      //selection sort
      int start, maxindex;
      double maxvalue;
      for (int row = 0; row < rows; ++row)
      {
         for (start = 0; start < columns - 1; start++)
         {
            maxindex = start;
            maxvalue = arr[row * columns + start];
            for (int index = start + 1; index < columns; ++index)
            {
               if (arr[row * columns + index] > maxvalue)
               {
                  maxvalue = arr[row * columns + index];
                  maxindex = index;
               }
            }
            swap(arr[row*columns + maxindex], arr[row*columns + start]);
            maxvalue = arr[row*columns + maxindex];
         }
      }

      //horizontal additive symmetry
      //logic is to add sums only as long as they continue
      //to be symmetrical for runtime efficiency; otherwise no point

      int row1st = 0;
      int row2nd = rows - 1;
      bool test;//sums match or not truth variable


      double sum1 = 0;
      double sum2 = 0;
      for (int column = 0; column < columns; ++column)
      {

         sum1 += arr[row1st * columns + column];


         sum2 += arr[row2nd * columns + column];
      }


      if (sum1 != sum2)
         test = false;
      else if (sum1 == sum2)
         test = true;

      int numberrows = rows;
      //new variable created so that number of rows is stored for later and not decremented permanently
      rows -= 2;// 2 rows used up
      bool HA;//horizontal additive symmetry truth variable

      if (test == false)
      {
         HA = false;
      }


      while (test == true)
      {
         row1st++;//progress through rows from top of array
         row2nd--;//progress through rows from bottom of array
         //row1st and row2nd are incremented or decremented
         //in a way to maintain symmetrical comparison
         rows -= 2;
         if (rows < 0)
         {
            HA = true;
            break;

         }

         for (int column = 0; column < columns; ++column)
         {

            sum1 += arr[row1st * columns + column];


            sum2 += arr[row2nd * columns + column];
         }


         if (sum1 != sum2)
            test = false;
         else if (sum1 == sum2)
            test = true;



         if (test == false)
         {
            HA = false;

         }


      }


      if (HA == false)
         cout << "no horizontal additive symmetry" << endl;
      else if (HA == true)
         cout << "horizontal additive symmetry" << endl;


      //outputting sorted array
      //numberrows variable used here to access original number of rows from file
      //than decremented value used for summing purposes
      for (int row = 0; row < numberrows; ++row)

      {
         for (int column = 0; column < columns; ++column)
            cout << setw(6) << arr[row * columns + column] << " ";

         cout << endl;
      }

      matrixfile.close();

      cout << endl;
      cout << "Would you like to process another file? Enter Y or y to " << endl;
      cout << "process another file: ";
      cin >> userselection;


   } while (userselection == 'y' || userselection == 'Y');

   system("PAUSE");

   return (0);
}

void swap(double &element1, double &element2)
{
   double temp;
   temp = element1;
   element1 = element2;
   element2 = temp;
}

