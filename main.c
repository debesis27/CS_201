#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int fibonacciArray[] = {377, 233, 144, 89, 55, 34, 21, 13, 8, 5, 3, 2, 1, 1};

int BinaryToDecimal(int* arr);
void DecimalToBinary(int num, int* binaryArray);
int DecimalToFibToDecimal(int num);

int main()
{
    //--------------------------------------------------------------
    //Start of Encryption
    int size = 0;
    char inputArray[26];
    char a;
    int* THEarray = malloc(size*sizeof(int));

    char encryptArray[26];
    for(int i = 0; i < 26; i++)
    {
        encryptArray[i] = 'A' + i;
    }

    for(int i = 0; a != '\n'; i++)
    {
        scanf("%c", &a);
        inputArray[i%26] = a;
        size++;
        
        inputArray[i%26] = inputArray[i%26] ^ encryptArray[i%26];
        THEarray = realloc(THEarray, size*sizeof(int));
        THEarray[i] = inputArray[i%26];

        int binaryArray[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for(int j = 0; j < 14; j++)
        {
            if(THEarray[i] >= fibonacciArray[j])
            {
                binaryArray[j]++;
                THEarray[i] -= fibonacciArray[j];
            }
        }
        
        THEarray[i] = BinaryToDecimal(binaryArray);
    }

    printf("Encrypted Text: ");
    for(int i = 0; i < size - 1; i++)                  
    {
        printf("%d ", THEarray[i]);
    }

    //End of Encryption
    //--------------------------------------------------------------
    //Start of Decryption

    int decFib[size - 1];
    char outputArray[size - 1];
    
    for(int i = 0; i < size - 1; i++)
    {
        decFib[i] = THEarray[i];
    }

    for(int i = 0; i < size - 1; i++)
    {
        decFib[i] = DecimalToFibToDecimal(decFib[i]);
    }

    for(int i = 0; i < size - 1; i++)
    {
        decFib[i] = decFib[i] ^ encryptArray[i%26];
    }

    for(int i = 0; i < size - 1; i++)
    {
        outputArray[i] = decFib[i];
    }

    printf("\n\nDecrypted Text: ");
    for(int i = 0; i < size - 1; i++)
    {
        printf("%c", outputArray[i]);
    }
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

    for(int i = 0; i < 14; i++)
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
