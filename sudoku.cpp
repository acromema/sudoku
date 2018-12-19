#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <istream>
#include <algorithm>
#include <cmath>
#include <time.h>
using namespace std;

string g_row[9] = {     //sudoku template start with 4(1120161721 (2+1)mod9+1 = 4)
    "456789123",       
    "123456789",
    "789123456",
    "345678912",
    "678912345",
    "912345678",
    "234567891",
    "567891234",
    "891234567" };

char g_output[200000000];       //output temp
char g_input[200000000];        //input temp
int unsolvedSudoku[10][10];     //save each unsolved sudoku
int rowMark[10][10];            //row numbers' status
int colMark[10][10];            //column numbers' status
int blockMark[10][10];          //block numbers' status
int row[10], col[10], block[10];//how many numbers in each unit
int blank[100][3];              //save the location and status of blanks in sudoku 
int blankCounter = 0;           //count number of blanks

inline void Write();
inline int BlockNum(int r,int c);       //calculate block location
inline void Swap(int * a, int * b);
inline void SetMark(int r, int c, int n, bool flag);
void Reset();
bool DFS(int deep);

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
        cout << "== Invalid Path ==" << endl;
        cout << "Check your file path!" << endl;
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

                if(unsolvedSudoku[r][c] == 0)   //count and save blanks
                {
                    blank[blankCounter][0] = r;
                    blank[blankCounter][1] = c;
                    blankCounter++;
                }
                else                            //save the filled numbers' status
                {
                    SetMark(r, c, unsolvedSudoku[r][c], 1);
                    row[r]++;
                    col[c]++;
                    block[BlockNum(r, c)]++;
                }
            }
        }

        for(int i = 0; i < blankCounter; i++)
        {
            int r = blank[blankCounter][0], c = blank[blankCounter][1];
            blank[blankCounter][2] = row[r] + col[c] + block[BlockNum(r, c)];
        }

        for(int i = 0; i < blankCounter; i++)   //sort
        {
            int m = i;
            for(int j = i; j < blankCounter-1; j++)
            {
                
                if(blank[m][2] < blank[j+1][2])
                    m = j+1;
            }
            Swap(blank[i],blank[m]);
        }

        if(DFS(0))
        {
            for(int r = 1; r < 10; r++)
            {
                for(int c = 1; c < 10; c++)
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

        for (int i = 0; i < 2 && n; i++)    //Swap rows of transformed sudoku and save in temp array
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
    
    if (argc != 3)                  //check number of arguments
    {
        cout << "== Invalid Arguments ==" << endl;
        cout << "If the file path contains spaces:"<< endl;
        cout << "1.Use backslash before spaces as escape character" << endl;
        cout << "2.Quotes the path with double quotation mark" << endl;
        return 0;
    }

    if (strcmp(argv[1],"-c") && strcmp(argv[1],"-s")) //check command type
    {
        cout << "== Invalid Command ==" << endl;
        cout << "This applicaiton only supports create(-c) and solve(-s) functions!" << endl;
        return 0;
    }

    switch(argv[1][1])                          
    {
        case 'c':                
        {
            int num = atoi(argv[2]);                
            if (num <= 0 || strlen(argv[2]) != int(log10(num))+1 || num >1000000)//check range and letter
            {
                cout << "== Invalid Input ==" << endl;
                cout << "Make sure the number is in the range of 1-1,000,000!" << endl;
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
    cout << "Used time = " << double(finish-start)/CLOCKS_PER_SEC << "s" << endl;
    
    return 0;
}

/**
 * Other functions
 */

inline int BlockNum(int r,int c)
{
    return ((r-1)/3)*3+((c-1)/3);
}

inline void SetMark(int r, int c, int n, bool flag)
{
    rowMark[r][n] = flag;
    colMark[c][n] = flag;
    blockMark[BlockNum(r, c)][n] = flag;
}

inline void Swap(int * a, int * b)
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

void Reset()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            rowMark[i][j]=0;
            colMark[i][j]=0;
            blockMark[i][j]=0;
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

bool DFS(int deep)
{
    if(deep==blankCounter)                          //done
    {
        return true;
    }

    int r = blank[deep][0], c = blank[deep][1];
    for(int i = 1; i < 10; i++)
    {
        if(!rowMark[r][i] && !colMark[c][i] && !blockMark[BlockNum(r, c)][i]) 
        {
            unsolvedSudoku[r][c]=i;
            SetMark(r, c, unsolvedSudoku[r][c], 1); //fill
            if(DFS(deep+1))return true;
            SetMark(r, c, unsolvedSudoku[r][c], 0); //unfill
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