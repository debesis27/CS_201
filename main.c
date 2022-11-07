#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int fibonacciArray[] = {377, 233, 144, 89, 55, 34, 21, 13, 8, 5, 3, 2, 1, 1};           //array containing first 14 fibonacci numbers

int BinaryToDecimal(int* arr);                              //function to convert binary number to its decimal form
void DecimalToBinary(int num, int* binaryArray);            //function to convert decimal number in binary form
int DecimalToFibToDecimal(int num);                         //function to represent a decimal number in its fibonacci format

int main()
{
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    //Start of Encryption
    int size = 0;                                           //size of input text
    char inputArray[26];                                    //circular queue that takes user text as input
    char a;                                                 //to take in one character at a time as input
    int* encrpytedArray = malloc(size*sizeof(int));         //Array containing the final encrypted text

    char keywordArray[26];                                  //Array containing the keywords

    for(int i = 0; i < 26; i++)
    {
        keywordArray[i] = 'A' + i;                         
    }

    for(int i = 0; a != '\n'; i++)                         //The loop continues until the enter key is pressed
    {
        scanf("%c", &a);
        inputArray[i%26] = a;
        size++;
        
        inputArray[i%26] = inputArray[i%26] ^ keywordArray[i%26];       //Xoring the input string (ASCII) with the keywords
        encrpytedArray = realloc(encrpytedArray, size*sizeof(int));     //Realloctaing space for encrypted array
        encrpytedArray[i] = inputArray[i%26];

        int binaryArray[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //Array to represent the binary form of the ASCII 

        for(int j = 0; j < 14; j++)                        //converting the decimal numbers into Fibonacci format to be sent as binary numbers
        {
            if(encrpytedArray[i] >= fibonacciArray[j])
            {
                binaryArray[j]++;
                encrpytedArray[i] -= fibonacciArray[j];
            }
        }
        
        encrpytedArray[i] = BinaryToDecimal(binaryArray);   //converting the binary form into decimal format
    }

    printf("Encrypted Text: ");
    for(int i = 0; i < size - 1; i++)                       //printing the encrypted text                
    {
        printf("%d ", encrpytedArray[i]); 
    }

    //End of Encryption
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    //Start of Decryption

    int decryptionArray[size - 1];                                              //Array for the decryption process
    char outputArray[size - 1];                                                 //Decrypted array
    
    for(int i = 0; i < size - 1; i++)                                           //Copying the encrypted text into the decryption array                                   
    {
        decryptionArray[i] = encrpytedArray[i];
    }

    for(int i = 0; i < size - 1; i++)                                           //Converting the recieved encrypted text to fibonacci format and then to decimal form
    {
        decryptionArray[i] = DecimalToFibToDecimal(decryptionArray[i]);     
    }

    for(int i = 0; i < size - 1; i++)                                           //Xoring with the keyword array
    {
        decryptionArray[i] = decryptionArray[i] ^ keywordArray[i%26];
    }

    for(int i = 0; i < size - 1; i++)                                           //Converting the ASCII code into its corresponding character 
    {
        outputArray[i] = decryptionArray[i];
    }

    printf("\n\nDecrypted Text: ");
    for(int i = 0; i < size - 1; i++)                                           //Printing the decrypted text
    {
        printf("%c", outputArray[i]);
    }

    //End of Decryption
    //-----------------------------------------------------------------------------------------------------------------------------------------------
}

int BinaryToDecimal(int *arr)
{
    int ans = 0;
    for (int i = 0; i < 14; i++)
    {
        ans += arr[i] * pow(2,13 - i);
    }

    return ans;
}

void DecimalToBinary(int num, int* binaryArray)
{
    int binaryNum[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int i = 0;
    while (num > 0) 
    {
        binaryNum[i] = num % 2;
        num = num / 2;
        i++;
    }

    for(int i = 0; i < 14; i++)                             //Reversing the array to represent the binary number in its standard form
    {
        binaryArray[i] = binaryNum[13 - i];
    }
}

int DecimalToFibToDecimal(int num)
{
    int binaryArray[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    DecimalToBinary(num, binaryArray);

    int ans = 0;
    for(int i = 0; i < 14; i++)
    {
        ans += fibonacciArray[i]*binaryArray[i];
    }
    
    int temp = binaryArray[12];
    binaryArray[12] = binaryArray[13];
    binaryArray[13] = temp;

    return ans;   
}
