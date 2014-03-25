#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include<math.h>
using namespace std;
#define MAXSIZE 40
 int Len=0;
 string name[MAXSIZE];
 int users[MAXSIZE]={0};
 float ItemArray[MAXSIZE][MAXSIZE];
void printArray(){
     int i,j;
     for(i=0;i<Len;i++){
       for(j=0;j<Len;j++)
        printf("%.2f ",ItemArray[i][j]);
       printf("\n");
     }
     printf("\n");
}
int initArray(){
 int j,i=0;
 string x;
 char line[1024]={0};
 ifstream bkin("books.txt",ios::in);
 while(bkin.getline(line,sizeof(line))){
    stringstream word(line);
    word >>x;
    word >>name[i];
    cout<<name[i]<<endl;
    i++;
 }
 Len = i;
 for(j=0;j<Len;j++)
   for(i=0;i<Len;i++){
    ItemArray[i][j]=0;       
 }
 cout<<"总共"<<i<<endl;

 return i;
}
int FillArray(){
  float items[MAXSIZE]={0.0};  
  char line[1024]={0},ch;
  int i,j,len=0,num[50]={0};
  FILE *fd= fopen("userinfo.txt","r");
  
  while(!feof(fd)){
    fscanf(fd,"%d%c",&num[len++],&ch);
    users[num[len-1]]++;
    
    if(ch=='\n'){
          
        for(i=0;i<len;i++)
          for(j=0;j<len;j++)
               ItemArray[num[i]][num[j]]+=1.0;    
     len=0;
   } 
  }
  
  for(i=0;i<Len;i++){
     ItemArray[i][i]=0;
     cout<<users[i]<<endl;
  }
  printArray();
  for(i=0;i<Len;i++)
      for(j=0;j<Len;j++){
          if(ItemArray[i][j]==0.0)
              continue;
          ItemArray[i][j]=ItemArray[i][j]/sqrt(1.0*users[i]*users[j]);
  
  }
 
  printArray();
  
}
typedef struct book{
 string name;
 float score;
}book_t;
bool  cmp( book_t a, book_t b )  
{  
    return  a.score > b.score;  
}  
int giveAd(){
  int i,id,itr=0;
  int Prefer[MAXSIZE]={0};
  vector<book_t> rlist;
  float score;

  for(i=0;i<Len;i++){
  cout<<"编号"<<i<<" "<<name[i]<<endl;
  }
  cout<<"请输入您喜欢的书籍,并评分"<<endl;
  cin>>id;
  cout<<"评分:";
  cin>>score;
  for(i=0;i<Len;i++){
      if(id==i)
        continue;
      if(ItemArray[id][i]!=0.0){
        book_t bk;
        bk.name = name[i];
        bk.score = ItemArray[id][i];
        rlist.push_back(bk);
        
  }
  }
  sort(rlist.begin(),rlist.end(),cmp);
  for(i=0;i<rlist.size();i++){
      cout<<rlist[i].name<<endl;
  }
  
}
int main(int argc, char *argv[])
{
 ifstream userin("userinfo.txt",ios::in);    
   initArray();
   FillArray();
   giveAd();

   system("PAUSE");
    return EXIT_SUCCESS;
}
