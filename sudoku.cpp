#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <cmath>
#include <time.h>
using namespace std;
string row[9] = {
    "456789123",       //suduko template start with 4(1120161721 (2+1)mod9+1 = 4)
    "123456789",
    "789123456",
    "345678912",
    "678912345",
    "912345678",
    "234567891",
    "567891234",
    "891234567" };

/**
 * create assigned amount of suduko and wirte into .txt file
 * @Author   Cole_Ma
 * @param    n       [amount of suduko]
 */
void createSuduko(int & n)
{
    ofstream fout;                        //I/O operate
    fout.open("suduko.txt",ios::app);    //write into .txt file (in append mode)
    int arr[] = {4,1,2,3,5,6,7,8,9};    //default transform order
    int order[] = {0,1,2,3,4,5,6,7,8};    //default write order
    int trans[9];                        //transform table
    int new_row[9][9];                    //save transformed row
    do
    {
        for (int i = 0; i < 9; ++i)        //make transform table
            trans[row[0][i] - 49] = arr[i];
        
        for (int i = 0; i < 9; ++i)        //transform 9 rows of suduko and save in new_row
            for (int j = 0; j < 9; ++j)
                new_row[i][j] = trans[row[i][j] - 49];

        for (int i = 0; i < 2 && n; i++)
        {
            for (int j = 0; j < 6 && n; j++)
            {
                for (int k = 0;k < 6 && n; k++)
                {
                    for (int m = 0; m < 9; ++m)
                    {
                        for (int n = 0; n < 8; ++n)
                            fout << new_row[order[m]][n] << ' ';
                        fout << new_row[order[m]][8];
                        if (m != 8)
                            fout << endl;
                    }
                    if (--n)
                        fout << endl << endl;
                    else
                    {
                        fout.close();
                        return;
                    }
                    
                    next_permutation(order+6,order+9);
                }
                next_permutation(order+3,order+6);
            }
            next_permutation(order+1,order+3);
        }
    }
    while(next_permutation(arr+1,arr+9));    //change the transform order
    fout.close();
    return;
}

int main(int argc, char *argv[])
{
//    char option;
//    option = getopt(argc,argv,"c:s:");
//    if (option != -1)                //get option successfully
//        switch(option)
//    {
//        case 'c':                //create suduko
//            int num = atoi(optarg);
//            if (num == 0 || strlen(optarg) != int(log10(num))+1)
//            {
//                printf("Invalid input\n");
//                return 0;
//            }
//            else
//            {
//                remove("suduko.txt");
//                createSuduko(num);
//            }
//            break;
//    }
//
    clock_t start,finish;　　　//定义clock_t变量
    start = clock();  　　　//开始时间

    int num;
    cin >> num;
    remove("suduko.txt");
    createSuduko(num);
    
    
    finish = clock();   //结束时间
    cout<<"time = "<<double(finish-start)/CLOCKS_PER_SEC<<"s"<<endl;
    
    return 0;
}
