#include <iostream>
#include <stdlib.h>
using namespace std;

int n;
struct node* head=NULL,*tail=NULL;

struct node
{
  int data;
  struct node* next;
};

int dequeue()
{
  int data;
  struct node* temp=head;
  head=head->next;
  data = temp->data;
  free(temp);
  if(head==NULL)
  {
    tail=NULL;  
  }
  return data;
}

int enqueue(int data)
{
  struct node* temp = (struct node*)malloc(sizeof(struct node));
  temp->data = data;
  temp->next = NULL;
  if(tail==NULL)
  {
    head = temp;
    tail = temp;
  }
  else
  {
    tail->next=temp;
    tail=tail->next;
  }
  return 0;
}

bool isNotEmpty()
{
  return !(head==NULL);
}

void display()
{
  struct node* temp=head;
  while(temp!=NULL)
  {
    cout<<temp->data<<" ";
    temp=temp->next;
  }
  cout<<endl;
}

int bfs(int S,int E,int grid[n][n])
{
  enqueue(S);
  bool visited[n*n];
  int previous[n*n];
  for(int i=0;i<n*n;i++)
  {
    visited[i]=false;
    previous[i]=-1;
  }
  visited[S]=true;
  while(isNotEmpty()&&visited[E]==false)
  {
    int s;
    s=dequeue();
    if(s%n+1<=n-1&&grid[s/n][s%n+1]==0&&visited[s+1]==false)
    {
      enqueue(s+1);
      visited[s+1]=true;
      previous[s+1]=s;
    }
    if(s%n-1>=0&&grid[s/n][s%n-1]==0&&visited[s-1]==false)
    {
      enqueue(s-1);
      visited[s-1]=true;
      previous[s-1]=s;
    }
    if(s/n+1<=n-1&&grid[s/n+1][s%n]==0&&visited[s+n]==false)
    {
      enqueue(s+n);
      visited[s+n]=true;
      previous[s+n]=s;
    }
    if(s/n-1>=0&&grid[s/n-1][s%n]==0&&visited[s-n]==false)
    {
      enqueue(s-n);
      visited[s-n]=true;
      previous[s-n]=s;
    }
  }
  for(int i=E;i!=-1;i=previous[i])
  {
    grid[i/n][i%n] = 2;
  }
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      cout<<grid[i][j]<<" ";
    }
    cout<<endl;
  }
  return 0;
}
int main() {
  cout<<"Enter the dimension of Grid";
  cin>>n;
  int grid[n][n];
  int S=0,E=0;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      char ch;
      cin>>ch;
      if(ch=='S')
      {
        S=i*n+j;
        grid[i][j]=0;
      }
      else if(ch=='E')
      {
        E=i*n+j;
        grid[i][j]=0;
      }
      else if(ch=='#')
      {
        grid[i][j]=1;
      }
      else
      {
        grid[i][j]=0;
      }
    }
  }
  //bfs(S,E,grid);
  enqueue(S);
  bool visited[n*n];
  int previous[n*n];
  for(int i=0;i<n*n;i++)
  {
    visited[i]=false;
    previous[i]=-1;
  }
  visited[S]=true;
  int count=0;
  while(isNotEmpty()&&visited[E]==false)
  {
    int s;
    s=dequeue();
    if(s%n+1<=n-1&&grid[s/n][s%n+1]==0&&visited[s+1]==false)
    {
      enqueue(s+1);
      visited[s+1]=true;
      previous[s+1]=s;
    }
    if(s%n-1>=0&&grid[s/n][s%n-1]==0&&visited[s-1]==false)
    {
      enqueue(s-1);
      visited[s-1]=true;
      previous[s-1]=s;
    }
    if(s/n+1<=n-1&&grid[s/n+1][s%n]==0&&visited[s+n]==false)
    {
      enqueue(s+n);
      visited[s+n]=true;
      previous[s+n]=s;
    }
    if(s/n-1>=0&&grid[s/n-1][s%n]==0&&visited[s-n]==false)
    {
      enqueue(s-n);
      visited[s-n]=true;
      previous[s-n]=s;
    }
    
  }
  
  for(int i=E;i!=-1;i=previous[i])
  {
    grid[i/n][i%n] = 2;
    count++;
  }
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      cout<<grid[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"Count "<<count<<endl;
  return 0;
}

/*
5
S _ _ _ _
_ # # _ _
_ # E _ _
_ # _ _ _
_ # _ _ _
*/