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
int unsolvedSudoku[10][10];   //save each unsolved sudoku
int rowmark[10][10];    //save row numbers' status
int colmark[10][10];    //save column numbers' status
int blockmark[10][10];  //save block numbers' status
int row[10],col[10],block[10];//save how many numbers in each unit
int blank[100][3];      //save the blanks in sudoku 
int blankCounter = 0;   //count amount of blanks


inline int getblocknum(int r,int c)
{
    return ((r-1)/3)*3+((c-1)/3);
}

void setmark(int r, int c, int n, bool flag)
{
    rowmark[r][n]=flag;
    colmark[c][n]=flag;
    blockmark[getblocknum(r, c)][n]=flag;
}

void swap(int * a, int * b)
{
    int temp[3];
    temp[0] = a[0];
    temp[1] = a[1];
    temp[2] = a[2];

    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];

    b[0] = temp[0];
    b[1] = temp[1];
    b[2] = temp[2];
    return;
}

bool dfs(int deep)
{
    if(deep==blankCounter)
    {
        return true;
    }

    int r = blank[deep][0], c = blank[deep][1];
    for(int i = 1; i < 10; i++)
    {
        if(!rowmark[r][i] && !colmark[c][i] && !blockmark[getblocknum(r, c)][i])
        {
            unsolvedSudoku[r][c]=i;
            setmark(r, c, unsolvedSudoku[r][c], 1);
            if(dfs(deep+1))return true;
            setmark(r, c, unsolvedSudoku[r][c], 0);
            unsolvedSudoku[r][c]=0;
        }
    }
    return false;
}

void Write()
{
    remove("sudoku.txt");
    ofstream WriteFile("sudoku.txt");
    WriteFile << g_output;
}

void Reset()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            rowmark[i][j]=0;
            colmark[i][j]=0;
            blockmark[i][j]=0;
            unsolvedSudoku[i][j]=0;
        }
        row[i]=0;
        col[i]=0;
        block[i]=0;
    }
    blankCounter = 0;
    for (int i = 0; i < 100; ++i)
    {
        blank[i][0] = 0;
        blank[i][1] = 0;
        blank[i][2] = 0;
    }
    return;
}

/**
 * solve sudoku in assigned .txt file
 * @Author   Cole_Ma
 * @DateTime 2018-12-17
 * @param    path       [path of .txt file]
 */
void SolveSudoku(string path)
{
    ifstream ReadFile(path);
    if (!ReadFile.is_open())
    {
        cout << "Can't open file, check the path!" << endl;
        return;
    }
    int counter = 0;
    while(!ReadFile.eof())
    {
        ReadFile >> g_input[counter++];
    }
    ReadFile.close();
    int iPointer = 0;
    int oPointer = 0;

    while(g_input[iPointer])
    {
        for(int r = 1; r < 10; r++)
        {
            for(int c = 1; c < 10; c++)
            {
                unsolvedSudoku[r][c] = g_input[iPointer++] - 48;

                if(unsolvedSudoku[r][c] == 0)
                {
                    blank[blankCounter][0] = r;
                    blank[blankCounter][1] = c;
                    blankCounter++;
                }
                else
                {
                    setmark(r, c, unsolvedSudoku[r][c], 1);
                    row[r]++;
                    col[c]++;
                    block[getblocknum(r, c)]++;
                }
            }
        }

        for(int i = 0; i < blankCounter; i++)
        {
            int r = blank[blankCounter][0], c = blank[blankCounter][1];
            blank[blankCounter][2] = row[r] + col[c] + block[getblocknum(r, c)];
        }

        for(int i = 0; i < blankCounter; i++)
        {
            int m = i;
            for(int j = i; j < blankCounter-1; j++)
            {
                
                if(blank[m][2] < blank[j+1][2])
                    m = j+1;
            }
            swap(blank[i],blank[m]);
        }

        if(dfs(0))
        {
            for(int r = 1; r < 10; r++)//from 1 to 9
            {
                for(int c = 1; c < 10; c++)//from 1 to 9
                {
                    g_output[oPointer++] = unsolvedSudoku[r][c] + '0';
                    if (c == 9)
                        g_output[oPointer++] = '\n';
                    else 
                        g_output[oPointer++] = ' ';
                }
            }
            g_output[oPointer++] = '\n';
        }
        Reset();
    }
    Write();
}




/**
 * create assigned amount of sudoku and wirte into .txt file
 * @Author   Cole_Ma
 * @param    n       [amount of sudoku]
 */
void CreateSudoku(int & n)
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
    
    if (argc != 3)
    {
        cout << "Invalid arguments!";
        return 0;
    }

    if (strcmp(argv[1],"-c") && strcmp(argv[1],"-s"))
    {
        cout << "Invalid command!" << endl;
        return 0;
    }
    switch(argv[1][1])
    {
        case 'c':                
        {
            int num = atoi(argv[2]);
            if (num <= 0 || strlen(argv[2]) != int(log10(num))+1 || num >1000000)
            {
                cout << "Invalid input" << endl;
                return 0;
            }
            else
            {
                CreateSudoku(num);
                Write();
            }
            break;
        }
        case 's':
        {
            SolveSudoku(argv[2]);
            break;
        }
    }

    finish = clock();
    cout<<"time = "<<double(finish-start)/CLOCKS_PER_SEC<<"s"<<endl;
    
    return 0;
}