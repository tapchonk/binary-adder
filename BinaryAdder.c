/*
Testing and program design specification

The essential functionality of this program is that it converts a string input in the form of an array of characters in C and extracts the 0s and 1s in a certain order and then obtains the denary values
for our inputs. We can then add these outputs together in order to have a denary result for our final outcome. We can then convert this final denary value to two's complement by reconverting the denary value
back into the form of an 8-bit binary number. To convert our denary value to two's complement we apply the modulus function to our denary value, record the remainder value and then check if we have to invert that bit dependent on whether or not
our original denary value was negative or not. We repeat this process 8 times and construct another char array of length 8 which contains the two's complement value of our calulcation.

Error checklist: The program has been designed such that it has an escape for situations which could proceed in an error if the program were to keep on running.
Overflow is dealt with by checking if the denary result of our calculation is larger than or less than the maximum range of values we can represent with our two's complement 8 bit register.
Users trying to input values that are not equivalent to 1 or 0 will cause the program to exit. We do this by casting the char value of the variable to an int value and comparing its ASCII value to see if it's either 48 for 0 or 49 for 1.
If it is neither of these values then the program realises this and outputs the appropriate error message.
If the user also leaves blank inputs the program will cease to run.
One case of testing where the program will fail: if the user attempts to input more than 8 bits into the input register it will still accept theses inputs even if they exceed the size of our char array.

How was testing carried out:

I took a sample of 6 random 8 bit sign and magnitude values and inputted them into the program accordingly:
01101100 and 01110101 expected result: ERROR as this results in an overflow of the 8 bit register
10011100 and 01011010 expected result: 00111110
11110111 and 00110011 expected result: 10111100
I then used an online calculator to first convert the values to denary, added them and them converted the values to two's complement to see if the outputs matched the expected result.

Test 1: Program ceased operation.
Test 2: Program outputted 00111110.
Test 3: Program outputted 10111100.

The program passes all 3 tests, however further testing is required to ensure that the program runs smoothly in all scenarios.
*/
#include<stdio.h>   //Library for taking user inputs in a terminal window
#include<stdlib.h>  //Library to assist us in managing strings data types in the form of character arrays
#include<string.h>

int powerCalc(int x, int n) //method for calculating the a number to an nth power
{
  int i;
  int number = 1;
  for (i = 0;i < n;++i) //we use a for loop to multiply the number by itself n times
  {
    number *= x;
  }
  return number;  //return our power value
}

int signTest(char *number)  //method used to test whether or not our signed and magnitude input is a negative or positive value
{
  char *one = "1";
  char *zero = "0";
  int result = strcmp(number, one);   //compares the value inputted at the number pass variable to the char variable "one"
  int multiplier = 0;

  if(result < 0)  //we use the principle that the ASCII value of 0 is less than that of 1 to make simple comparisons between the char "0" and the char "1"
  {
    printf("Input is positive \n");
    multiplier = 1;
  }
  else
  {
    printf("Input is negative \n");
    multiplier = -1;
  }
  return multiplier;
}

int addResult(int *x, int *y) //method of passing two values to this function and adding them together
{
  int tempX = *x;
  int tempY = *y;
  int result = tempX + tempY;
  return result;
}

void convertToTwos(int *x, int isNegative)  //This method can convert a denary number to two's complement by applying the MOD function to find the remainder after applying MOD 2
{
  char twosArray[8];  //If the remainder is 1 then we will write 1 to the i'th position in our char array denoted by "twosArray"

  if(isNegative == 1) //otherwise , in the case where denary result is negative we must find its absolute magnitude to convert it to two's properly
  {
    *x = *x * -1;
  }

  for (int i = 7; i >= 0; i--)  //divides the number by 2 and extracts the remainder if there is one. We iterate through the char array backwards such that the MSB is on the LHS and the LSB is on the RHS
  {
    int remainder = *x % 2;
    char adder;
    char *pAdder;
    printf("%d \n", *x);
    pAdder = &adder;
    *x = (*x - remainder) / 2;  //depending on the value for remainder we either will write 0 or 1
    if(remainder == 1)
    {
      pAdder = "1";
      if(isNegative == 1) //however, if our denary result was originally negative then we have to invert our bits
      {
        pAdder = "0";
      }
      twosArray[i] = *pAdder;
    }
    else
    {
      pAdder = "0";
      if(isNegative == 1)
      {
        pAdder= "1";
      }
      twosArray[i] = *pAdder;
    }
    }
    printf("Result in two's complement:   %s \n", &twosArray);  //outputs our string/char array

  }

  int oneOrZeroTest(char *inputChar) //as a form of input validation we cast the char value to an int such that we can now find the exact ASCII value for our inputs
  {
    int invalidFound = 0; //Since we only want two inputs(0 and 1), we can just exhaust all the possible scenarios by ensuring that the user input is either one or the other
    for (int i = 0; i < 8; i++)
    {
      int i1 = *inputChar;
      if(i1 == 48 | i1 == 49)
      {
        invalidFound = 0;
      }
      else
      {
        invalidFound = 1; //otherwise, if the input is invalid, then we set the checking variable to "1" to alert the program to the fact that a non 1/0 input has been identified
      }
    }
    return invalidFound;
  }

int main()
{
  char binNumber1[9], binNumber2[9];  //declaring our char arrays of size 9 for 8 input bits and the last \0 bit

  char *one = "1";
  char *zero = "0";

  printf("Input the first binary number: \n");  //input our strings in this format of a char array
  scanf("%s", &binNumber1);

  printf("Input the second binary number: \n");
  scanf("%s", &binNumber2);

  int intTest = 0;

  for (int i = 0; i < 8; i++) //for every value in each of our char arrays we test to see if they are valid inputs by checking if their casted to int ASCII value matches that of 1 or 0
  {
    intTest = oneOrZeroTest(&binNumber1[i]);
    if(intTest == 1)
    {
      printf("Inputs can only be 1 or 0 and cannot be blank \n");
      return 0; //if an input made in error has been found then we exit the program
    }
    intTest = oneOrZeroTest(&binNumber2[i]);  //check the same with our second binary input
    if(intTest == 1)
    {
      printf("Inputs can only be 1 or 0 and cannot be blank \n");
      return 0;
    }
  }



  char number1 = binNumber1[0]; //in this case we check our MSB in this case to see if it's 1 or 0
  printf("Testing sign of input 1:");
  int multiplier1 = signTest(&number1); //this will determine whether or not our signed and magnitude value is positive or negative
  char number2 = binNumber2[0];
  printf("Testing sign of input 2:");
  int multiplier2 = signTest(&number2);

  int x1 = 0;
  int x2 = 0;
  for (int i = 7; i > 0; i--) //This for loop contains a function that allows us to convert the signed and magnitude 8 bit binary input to a denary value which we can add together
  {
    char arrayValue1 = binNumber1[i]; //How it functions is as follows
    int result1 = strcmp(&arrayValue1, one);  //for every value in each of our char arrays we check if the value is 0 or 1
    //printf("%d \n", result1);
    if(result1 > 0)
    {
      int addingValue1 = powerCalc(2, 7-i); //then, dependent on which bit we apply the check on then we add 2^n to our counter variable where n denotes the position in the char array where we compared the values
      x1 = x1 + addingValue1;
    }
    char arrayValue2 = binNumber2[i]; //We carry out the exact same operation on our second signed and magnitude input
    int result2 = strcmp(&arrayValue2, one);
    //printf("%d \n", result2);
    if(result2 > 0)
    {
      int addingValue2 = powerCalc(2, 7-i);
      x2 = x2 + addingValue2;
    }
  }
  x1 = x1 * multiplier1;  //we then multiply them by a value determined by the check where we looked to see if the MSB was 0 or 1
  x2 = x2 * multiplier2;  //if the MSB is 0 then we keep our denary output positive, otherwise we multiply it by -1 to make it negative

  printf("Value of input 1 in denary   %d \n", x1);
  printf("Value of input 2 in denary   %d \n", x2);  //output our denary result

  int denaryResult = addResult(&x1, &x2); //add our denary values together

  if (denaryResult > 127 | denaryResult < -128) //to take into account for cases where in the inputs may result in an overflow in our 8 bit register we compare it to see if it's greater or less than the largest representable value by our
  {                                       //8 bit register, in this case it can only represent values between -128 and 127
    printf("Value is too large to fit in an 8 bit two's complement register.");
    return 0; //exit the program if the value is too small or too large
  }

  printf("Denary value of result:  %d \n", denaryResult);  //output the denary result of our calculation

  int isNegative = 0;

  if (denaryResult < 0) //we have to remember whether or not our denary value was positive or negative before we create our final answer in two's complement
  {
    denaryResult++;
    isNegative = 1;
  }

  convertToTwos(&denaryResult, isNegative); //calls our method to convert to Two's



}
