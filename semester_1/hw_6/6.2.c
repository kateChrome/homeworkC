#include <stdio.h>
#include <stdbool.h>
#include <math.h>

const int sizeOfBinaryNumber = 32;

void arrayInitialization(int *array, int sizeOfArray);
void decimalToBinary(int *binaryNumber, int decimalNumber);
void printBinaryNumber(int binaryNumber[]);
void sumOfBinaryNumbers(int *binaryNumber1, int *binaryNumber2, int *binarySum);
int binaryToDecimal(int *binaryNumber);

int main()
{
  int decimalFirstNumber = 0;
  int decimalSecondNumber = 0;
  printf("Enter the numbers: ");
  scanf("%d %d", &decimalFirstNumber, &decimalSecondNumber);

  int binaryFirstNumber[sizeOfBinaryNumber];
  int binarySecondNumber[sizeOfBinaryNumber];
  int binarySumOfNumbers[sizeOfBinaryNumber];
  arrayInitialization(binaryFirstNumber, sizeOfBinaryNumber);
  arrayInitialization(binarySecondNumber, sizeOfBinaryNumber);
  arrayInitialization(binarySumOfNumbers, sizeOfBinaryNumber);

  decimalToBinary(binaryFirstNumber, decimalFirstNumber);
  decimalToBinary(binarySecondNumber, decimalSecondNumber);

  sumOfBinaryNumbers(binaryFirstNumber, binarySecondNumber, binarySumOfNumbers);
  int decimalSumNumbers = binaryToDecimal(binarySumOfNumbers);

  printf("First input number in binary form: ");
  printBinaryNumber(binaryFirstNumber);
  printf("Second input number in binary form: ");
  printBinaryNumber(binarySecondNumber);
  printf("Sum of input numbers in binary form: ");
  printBinaryNumber(binarySumOfNumbers);
  printf("Sum of input numbers in decimal form: ");
  printf("%d\n", decimalSumNumbers);

  return 0;
}

void arrayInitialization(int *array, int sizeOfArray)
{
  for (int i = 0; i < sizeOfArray; i++)
  {
    array[i] = 0;
  }
}

void decimalToBinary(int *binaryNumber, int decimalNumber)
{
  for (int i = 0; i < sizeOfBinaryNumber; i++)
  {
    binaryNumber[i] = decimalNumber >> i & 1;
  }
}

void printBinaryNumber(int binaryNumber[])
{
  int placeOfLastOne = 0;
  for (int i = sizeOfBinaryNumber - 1; i >= 1; i--)
  {
    if (binaryNumber[i] == 1)
    {
      placeOfLastOne = i;
      break;
    }
  }
  for (int i = placeOfLastOne; i >= 0; i--)
  {
    printf("%d", binaryNumber[i]);
  }
  printf("\n");
}

void sumOfBinaryNumbers(int *binaryNumber1, int *binaryNumber2, int *binarySum)
{
  int backupDigit = 0;
  int currentSum = 0;

  for (int i = 0; i < sizeOfBinaryNumber; i++)
  {
    currentSum = binaryNumber1[i] + binaryNumber2[i] + backupDigit;
    binarySum[i] = currentSum % 2;
    backupDigit = currentSum / 2;
  }
}

int binaryToDecimal(int *binaryNumber)
{
  int decimalNumber = 0;


  if (binaryNumber[sizeOfBinaryNumber - 1] == 0)
  {
      for (int i = sizeOfBinaryNumber - 1; i >= 0; i--)
      {
          decimalNumber += binaryNumber[i] * pow(2, i);
      }
  }
  else
  {
      for (int i = sizeOfBinaryNumber - 1; i >= 0; i--)
      {
          decimalNumber += !binaryNumber[i] * pow(2, i);
      }
      decimalNumber++;
      decimalNumber *= -1;
  }

  return decimalNumber;
}
