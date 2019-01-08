// Program is Copyright 2016 Tony Trinh
// Program will take a message from the user and then encrypt using RSA method
// It will save the message and make a public key and a private key in 2 different text files
// Program will also be able to decrypt the message


#include <iostream>
#include <math.h> // for using math functions
#include <stdio.h> // for random number generation
#include <stdlib.h> // for random number generation
#include <time.h> // for getting a time seed for random number generation
#include <iomanip> // for precision of numbers
#include <vector> // for using vectors
#include <string> // for using specific string properties
#include <fstream> // for writing files and reading files
#include <ttmath/ttmath.h> // big num library for carrying large numbers

typedef ttmath::Int<TTMATH_BITS(384)> Int; // allows the big number variable Int which holds up to 100 digits

using namespace std;

bool isPrime (int num); // declaration of the isPrime function to check if a number is prime or not
int phi (int n , int p , int q); // phi calculator to calculate phi of 2 prime numbers
void encrypt(); // encryption function
void decrypt(); // decryption function

int main()
{
    int reply; // reply variable that will hold the user's reply to the 3 options
    cout << "Welcome to Tony's RSA encryption emporium!" << endl; // welcomes user into the program
    cout << endl;

    // following lines explains the options for the program to the user
    cout << "Press 1 to encrypt a message!" << endl;
    cout << "Press 2 to decrypt a message!" << endl;
    cout << "Press 3 to exit the program." << endl;
    cin >> reply; // gets the user's reply
    cin.clear(); // clears out the cin to use getline later
    cin.ignore(100,'\n');

    while (reply != 3)
    {

        if (reply == 1 )
        {
            // if the reply is 1 then it goes into the encryption option
            encrypt();
            // after the encryption is complete the user will see the options again
            cout << "Press 1 to encrypt a message!" << endl;
            cout << "Press 2 to decrypt a message!" << endl;
            cout << "Press 3 to exit the program." << endl;

        }
        else if (reply == 2)
        {
            // if the reply is 2 then it goes into the decryption option
            decrypt();
            // after the decryption is complete the user will see the options again
            cout << "Press 1 to encrypt a message!" << endl;
            cout << "Press 2 to decrypt a message!" << endl;
            cout << "Press 3 to exit the program." << endl;

        }
        else if (reply == 3)
        {
            // if the reply is 3 then it exits the program
            return -1;

        }
        else // if the user inputs an option that is not part of the 3 options
        {
            cout << "That's not a valid answer" << endl; // prints out an error message
            cout << "Please provide a valid input" << endl; // asks user for another input
        }

        cin >> reply; // keeps on asking the user till the user enters 3
        cin.clear(); // clears out the cin
        cin.ignore(100,'\n');
    }
    return 0;
}

void encrypt() // encryption function
{
    srand (time(NULL)); // starts the random number time seed
    string message; // string variable string that holds the user's message that they want to encrypt
    int p; // 1st prime number variable
    int q; // 2nd prime number variable
    int e; // e variable that is co prime to the phi of the product of p and q
    int n; // n that holds the product of p and q
    int d; // d is the private key exponent and makes it so that d*e mod phi(n) = 1
    int phitotal; // phi holds the phi of n which can be found with phi total = (p - 1 ) (q - 1)
    int num; // random num variable that gets passed down to p and q , just a middleman variable for random numbers
    vector <double> encryptedMessage; // vector that holds the encrypted message
    cout << "Give me a message and I will encrypt it!" << endl; // asks user for enter in a message
    getline (cin, message); // gets message from user
    cout << "Your message in ascii value is " << endl;

    int i = 0; // counter variable loop to get 1 prime number
    while(i != 1) // loop to keep on looping for random numbers until the number is a prime
    {
        num = rand () % 1000 + 100; // gets a random number from 100 to 1000
        if(isPrime(num)) // if the random number when checked by the bool function is prime
        {
            p = num; // sets p variable as the random prime number
            i++; // adds 1 to the i variable to end the loop
        }
    }
    // following is a 2nd loop that is equivalent to the 1st loop and is used to get the second prime number
    while(i != 2) // loop to keep on looping for random numbers until the number is a prime
    {
        num = rand () % 1000 + 100; // gets a random number from 100 to 1000
        if(isPrime(num)) // if the random number when checked by the bool function is prime
        {
            q = num; // sets q variable as the random prime number
            i++; // adds another 1 to the i variable to end this loop
        }
    }

    // find the product of the 2 prime numbers  and call it n
    cout << p << endl;
    cout << q << endl;
    cout << "The Value of N is" << endl;
    n = p * q; // calculates the product of the 2 prime numbers
    cout << n << endl;

    // then calculate the phi of n , this is done using (phi)(n) = (p-1)(q-1)
    phitotal = phi(n , p , q); // calls in the phi function to find the phi of n
    cout << "Phi of N is" << endl;
    cout << phitotal << endl;

    e = 7; // e is a constant is in this case is 17
    // find d so that d*e mod phitotal = 1
    // extended euclidean algorithm to solve for the value of d
    int eea[2][2];
    eea[0][0] = phitotal;
    eea[0][1] = phitotal;
    eea[1][0] = e;
    eea[1][1] = 1;
    int multiple;
    int newnum1;
    int newnum2;
    // euclidean extended algorithm
    while (eea[1][0]!= 1) // loop keeps on happening until the eea[1][0] becomes 1 and then the program has found d
    {
        multiple = floor(eea[0][0]/eea[1][0]); // multiple is how many times the eea[1][0] can fit inside eea[0][0]
        newnum1 = eea[0][0] - (multiple * eea[1][0]); // newnum1 is the eea[0][0] subtracted by the product of multiple and eea[1][0]
        newnum2 = eea[0][1] - (multiple * eea[1][1]); // newnum2 is the eea[0][1] subtracted by the product of multiple and eea[1][1]
        eea[0][0] = eea[1][0]; // assigns the eea[0][0] as eea[1][0]
        eea[0][1] = eea[1][1]; // assigns the eea[0][1] as eea[1][1]
        eea[1][0] = newnum1; // assigns the eea[1][0] as the new variable newnum1
        eea[1][1] = newnum2; // assigns the eea[1][1] as the new variable newnum2
        while (eea[1][1] < 0) // if eea[1][1] is a negative we do modular arithmetic here
        {
            eea[1][1] = newnum2 + phitotal; // adds on the phitotal to newnum2 and assigns that to eea[1][1]
        }
    }
    d = eea[1][1]; // assigns the eea[1][1] which is the number after completing the extended euclidean algorithm

    cout << "The remainder of e*d mod n is " << endl;
    cout << (e*d)%n << endl;


    cout << "The private key is d and n " << endl;
    cout << d << " and " << n << endl;

    cout << "The public key is e and n " << endl;
    cout << e << " and " << n << endl;


    cout << "Creating private key file" << endl; // tells the user that the private key file is being created
    cout << "Give me a name for the private key file" << endl; // asks user for a name for the private ket file
    string privateKeyName; // variable to hold the name of the private key file
    cin >> privateKeyName; // gets the name of the private key file

    // creates the private key file
    ofstream privateKey;
    string pKey;
    pKey=  pKey + privateKeyName + ".txt";
    privateKey.open (pKey.c_str(),ios_base::out|ios_base::app);

    // puts the d variable and n variable in the file
    privateKey << d << endl;
    privateKey << n << endl;
    // closes the private key file
    privateKey.close();


    cout << "Creating public key file" << endl; // tells the user that the public key file is being created
    cout << "Give me a name for the public key file" << endl; // asks user for a name for the public key file
    string publicKeyName; // variable to hold the name of the public key file
    cin >> publicKeyName; // gets the name of the public key file


    // creates the public key file
    ofstream publicKey;
    string pubKey;
    pubKey= pubKey + publicKeyName + ".txt";
    publicKey.open (pubKey.c_str(),ios_base::out|ios_base::app);


    // puts the e variable and n variable in the file
    publicKey << e << endl;
    publicKey << n << endl;
    // closes the public key file
    publicKey.close();


    // generation of numbers for encryption is complete
    // now the actual encryption of the user's message can be done
    cout << "Now to encrypt your message" << endl;
    // using big num integers now
    Int c , remainder; // declaration of big num int variables
    int asciiConverter = 0; // this variable is a middle man variable to bring the ascii value of the current character to the big num variable c
    int encryptedAscii = 0; // this variable is also a middle man variable to bring the encrypted value to be used in a vector

    for (int i = 0 ; i <= message.length()-1 ; i++)// for loop up to the size of the user's message
    {
        asciiConverter = (int)message[i]; // sends the current ascii value of the user's character into the asciiConverter variable
        c = asciiConverter; // assigns the c the current ascii value of the current character in the user's message
        c.Pow(e); // assigns c to the power of e
        c.Div(n,&remainder); // gets the remainder of c mod n and assigns the remainder to the remainder big num variable
        cout << c << endl;
        cout << remainder << endl;
        remainder.ToInt(encryptedAscii); // converts the remainder big num variable to an int variable encryptedAscii
        cout << encryptedAscii << "hi " << endl;


        encryptedMessage.push_back(encryptedAscii); // puts the encryptedAscii value into the encryptedMessage vector to be written in a text file later

    }


    cout << "Creating your encrypted message txt file" << endl; // tells the user that the encrypted message file is being created
    cout << "Give me a name for your encrypted message file" << endl;// asks user for a name for the encrypted message file
    string encryptedName; // variable to hold the name of the encrypted message file
    cin >> encryptedName; // gets the name of the encrypted message file

    // creates the encrypted message file
    ofstream encryptedFile;
    string encryptedMessageFile;
    encryptedMessageFile= encryptedMessageFile + encryptedName+ ".txt";
    encryptedFile.open (encryptedMessageFile.c_str(),ios_base::out|ios_base::app);

    // for loop that loops to the size of the user's encrypted message vector
    for (int i = 0 ; i <= encryptedMessage.size()-1 ; i++ )
    {
        encryptedFile << encryptedMessage[i] << endl; // puts the current encrypted character into the text file
    }
    encryptedFile.close(); // closes the encrypted message file after the text file is finished being written

}

void decrypt() // function for decryption
{
    string decryptFile; // variable to hold the decrypt file which is the private key file
    string encryptedMessageName; // variable to get the name of the encrypted message file
    ifstream privateKeyFin; // read in variable for the private key
    ifstream encryptedMessFin; // read in variable for the encrypted message file
    string decryptLines; // variable holds the lines of the decrypt file
    string encryptedLines; // variable holds the lines of the encrypted message file
    vector <string> decryptNumbers; // vector that holds the d and n numbers from the private key file
    vector <string> encryptedMess; // vector that holds the encrypted numbers from the encrypted message file
    cout << "Give me the name of your private key file" << endl; // asks user for the name of the private key file
    getline (cin,decryptFile); // gets the name of the private key file
    privateKeyFin.open(decryptFile.c_str(),ios_base::in); // opens the file

    do
    {
        getline(privateKeyFin,decryptLines); // gets the line of the text file
        cout << decryptLines << endl;
        decryptNumbers.push_back(decryptLines); // puts the line into the array
    } while(privateKeyFin.good());

    privateKeyFin.close(); // closes the file
    int d = decryptLines[0];
    int n = decryptLines[1];

    cout << "Now give me the name of your encrypted message file" << endl; // asks user for the name of encrypted message file
    getline (cin , encryptedMessageName); // gets the name of the encrypted message file

    encryptedMessFin.open(encryptedMessageName.c_str(),ios_base::in); // opens the file

    do
    {
        getline(encryptedMessFin,encryptedLines); // gets the line of the text file
        cout << encryptedLines << endl;
        encryptedMess.push_back(encryptedLines); // puts the line into the array
    } while(encryptedMessFin.good());

    encryptedMessFin.close(); // closes the file

    cout << "Now to decrypt your message!" << endl;
    Int m , remainder2; // declaration of big num integers that can hold 100 digits
    int asciiConverter2; // middle man variable to carry over the number from the array to the big num integers


    for (int i = 0 ; i <= encryptedMess.size()-1 ; i++) // for loop that loops up to the entirety of the encrypted message
    {
        cout << encryptedMess[i] << endl;
        asciiConverter2 = stoi(encryptedMess[i]);
        m = asciiConverter2; // brings over the current number in the encrypted message to the big num integer m
        m.Pow(d); // raises the m value to the private key number d
        m.Div(n, &remainder2); // takes the previous number and then finds the modulus from n
        cout << m << "the big number" << endl;
        cout << remainder2 << "the deciphered message " << endl;

    }

}

bool isPrime (int num) // function itself that determines if a number of prime or not
{
    bool isPrime=true; // sets the bool as true at the beginning
    for (int x=2 ; x <= sqrt(num) ; x++) // loop that checks numbers up to the sqrt of the number that is being tested if it is prime or not
    {
        if (num%x==0) // if the number is factorable
        {
            isPrime = false; // sets the bool Isprime as false and breaks the loop
            break;
        }
    }
    return isPrime; // returns true or false on whether if the number is prime or not
}

int phi (int n, int p, int q) // function that takes in the n variable , and the 2 prime numbers p and q
{
    int total; // total is the phi total
    total = (p -1 )*(q - 1); // calculates the phi total
    return total; // returns the total which the phitotal variable will hold
}
