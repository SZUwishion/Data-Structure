#include <iostream>
#include<cstring>
using namespace std;
int Next[1000005];
string T,M;
void getNext()
{
    int i=1,j=0;
    while(i<T.length())
    {
        if(j==0||T[i-1]==T[j-1])
        {
            i++;
            j++;
            if   (T[i-1]!=T[j-1]) Next[i] = j;
            else Next[i]= Next[j];
        }
        else j=Next[j];
    }
}
int main(int, char**){
    cin>>M>>T;
    bool flag;
    int lenT=T.length();
    getNext();
    int i=1,j=1;
    while(i<=M.length())
    {
        if(j==0||M[i-1]==T[j-1])
        {
            i++;
            j++;
        }
        else
        {
            j=Next[j];
        }
        if(j>T.length())
        {
            flag=1;
            break;
        }
    }
    if(flag==1) cout<<"YES";
    else cout<<"NO";
    return 0;
}
