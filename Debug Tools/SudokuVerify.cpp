#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;
int main(){
    int total = 1;
    int i,n,a[10][10],j,k;
    string filePath;
    cout << "Please enter the path: ";
    getline(cin, filePath);
    ifstream ReadFile(filePath);
    if (!ReadFile.is_open())
    {
       cout << "Invalid path" << endl;
       return 0;
    }
    while(!ReadFile.eof())
    {
        int e = 1;
        for(i = 1; i <= 9; i++)
        {
            for( j = 1; j <= 9; j++)
            {
                ReadFile >> a[i][j];
            }
        }
        if(k != n)
            getchar();
        for(i =1 ;i<=9;i++){
            int b[10]={0};
                b[0]=1;
            for(j=1;j<=9;j++){
                if(b[a[i][j]]==0)
                    b[a[i][j]]=1;
                else{
                    printf("Wrong\n");
                    e=0;
                    return 0;
                }
            }
            if(e==0)
                break;
        }
        if(e==0)
            continue;
        for(j=1;j<=9;j++){
            int b[10]={0};
                b[0]=1;
            for(i=1;i<=9;i++){
                if(b[a[i][j]]==0)
                    b[a[i][j]]=1;
                else{
                    printf("Wrong\n");
                    e=0;
                    return 0;
                }
            }
            if(e==0)
                break;
        }
        if(e==0)
            continue;
        for(i=2;i<=8;i=i+3){
            for(j=2;j<=8;j=j+3){
                int b[10]={0};
                b[0]=1;
                if(b[a[i][j]]==0)
                    b[a[i][j]]=1;
                else
                    e=0;
                if(b[a[i-1][j-1]]==0)
                    b[a[i-1][j-1]]=1;
                else
                    e=0;
                if(b[a[i][j-1]]==0)
                    b[a[i][j-1]]=1;
                else
                    e=0;
                if(b[a[i-1][j]]==0)
                    b[a[i-1][j]]=1;
                else
                    e=0;
                if(b[a[i+1][j]]==0)
                    b[a[i+1][j]]=1;
                else
                    e=0;
                if(b[a[i][j+1]]==0)
                    b[a[i][j+1]]=1;
                else
                    e=0;
                if(b[a[i+1][j+1]]==0)
                    b[a[i+1][j+1]]=1;
                else
                    e=0;
                if(b[a[i-1][j+1]]==0)
                    b[a[i-1][j+1]]=1;
                else
                    e=0;
                if(b[a[i+1][j-1]]==0)
                    b[a[i+1][j-1]]=1;
                else
                    e=0;
                if(e==0)
                    break;
            }
            if(e==0)
            break;
        }

        
        if(e == 0)
        {
            total = 0;
            cout << "Wrong" << endl;
            return 0;
        }
        
    }
    if (total==0)
    {
        cout << "Wrong answer found!"<<endl;
    }
    else 
    {
        cout << "Correct answer"<< endl;
    }
    return 0;
}