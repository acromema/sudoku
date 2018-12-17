#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <unistd.h>
using namespace std;

string g_row[9] = {
    "456789123",       //sudoku template start with 4(1120161721 (2+1)mod9+1 = 4)
    "123456789",
    "789123456",
    "345678912",
    "678912345",
    "912345678",
    "234567891",
    "567891234",
    "891234567" };

char g_output[200000000];
char g_input[200000000];

void Write()
{
    remove("sudoku.txt");
    ofstream WriteFile("sudoku.txt");
    WriteFile << g_output;
}

/**
 * create assigned amount of sudoku and wirte into .txt file
 * @Author   Cole_Ma
 * @param    n       [amount of sudoku]
 */
void Createsudoku(int & n)
{
    int arr[] = {4,1,2,3,5,6,7,8,9};    //default transform order
    int order[] = {0,1,2,3,4,5,6,7,8};    //default write order
    int trans[9];                        //transform table
    int newRow[9][9];                    //save transformed rows
    int tempPointer = 0;
    do
    {
        for (int i = 0; i < 9; ++i)        //make transform table
            trans[g_row[0][i] - 49] = arr[i];
        
        for (int i = 0; i < 9; ++i)        //transform 9 rows of sudoku and save in newRow
            for (int j = 0; j < 9; ++j)
                newRow[i][j] = trans[g_row[i][j] - 49];

        for (int i = 0; i < 2 && n; i++)    //swap rows of transformed sudoku and save in temp array
        {
            for (int j = 0; j < 6 && n; j++)
            {
                for (int k = 0;k < 6 && n; k++)
                {
                    for (int m = 0; m < 9; ++m)
                    {
                        for (int n = 0; n < 9; ++n)
                        {
                            g_output[tempPointer++] = newRow[order[m]][n] +'0';
                            if (n == 8)
                                g_output[tempPointer++] = '\n';
                            else 
                                g_output[tempPointer++] = ' ';
                        }
                    }
                    if (--n)
                        g_output[tempPointer++] = '\n';
                    else
                        return;
                    next_permutation(order+6,order+9);
                }
                next_permutation(order+3,order+6);
            }
            next_permutation(order+1,order+3);
        }
    }
    while(next_permutation(arr+1,arr+9));    //change the transform order
    return;
}

int main(int argc, char *argv[])
{
    clock_t start,finish;
    start = clock();
    
    // char option;
    // option = getopt(argc,argv,"c:s:");
    // if (option != -1)                //get option successfully
    //     switch(option)
    //     {
    //         case 'c':                //create sudoku
    //             int num = atoi(optarg);
    //             if (num == 0 || strlen(optarg) != int(log10(num))+1)
    //             {
    //                 printf("Invalid input\n");
    //                 return 0;
    //             }
    //             else
    //                 CreateSudoku(num);
    //                 Write();
    //             break;
    //         case 's':
    //             string path = optarg;
    //             ifstream ReadFile(path);
    //             if (!ReadFile.is_open())
    //             {
    //                 cout << "Can't open file, check the path";
    //             }
    //             else 
    //                 SolvedSudoku();


    //     }
    int num;
    cin >> num;
    Createsudoku(num);
    Write();
    finish = clock();
    cout<<"time = "<<double(finish-start)/CLOCKS_PER_SEC<<"s"<<endl;
    
    return 0;
}