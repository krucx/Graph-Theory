/*
8 ---  10 -> 9
5 ---  1->4->6
3 --- 2->1
1 --- 4
4 --- 8->7
6 --- 11->10
2 --- 4
7 --- 9
13 --- 
12 --- 
10 --- 13 -> 12
9 --- 12
11 --- 10


3->2->5->6->11->1->4->7->8->9->10->12->13->

bfs -> queues
dfs -> stacks
*/

#include <iostream>
using namespace std;

struct node
{
  int data;
  struct node* next;
};

void push(struct node** head,int data)
{
  struct node* temp = (struct node*)malloc(sizeof(struct node));
  temp->data  = data;
  temp->next = *head;
  *head = temp;
}

void pop(struct node** head)
{
  struct node* temp = *head;
  (*head) = temp->next;
  free(temp);
}

bool isEmpty(struct node** head)
{
  return *head==NULL;
}

void display(struct node** head)
{
  struct node* temp = *head;
  while(temp!=NULL)
  {
    cout<<temp->data<<"->";
    temp=temp->next;
  }
  cout<<endl;
}

int index(int arr[],int n,int data)
{
  for(int i=0;i<n;i++)
  {
    if(arr[i]==data)
    {
      return i;
    }
  }
  return 0;
}

void dfs(struct node* adjList[],bool visited[],int i,struct node** stack,int v,int vertices[])
{
  struct node* temp = adjList[i];
  while(temp!=NULL)
  {
    if(!visited[index(vertices,v,temp->data)])
    {
      dfs(adjList,visited,index(vertices,v,temp->data),stack,v,vertices);
    }
    temp=temp->next;
  }
  visited[i]=true;
  push(stack,vertices[i]);
  return;
}

void topsort(struct node* adjList[],int v,int vertices[])
{
  bool visited[v];
  struct node* stack=NULL;
  for(int i=0;i<v;i++)
  {
    visited[i]=false;
  }
  for(int i=0;i<v;i++)
  {
    if(visited[i]==false)
    {
      dfs(adjList,visited,i,&stack,v,vertices);
    }
  }
  display(&stack);
}

int main() {
  int v;
  cout<<"Enter number of vertices";
  cin>>v;
  struct node* adjList[v];
  int vertices[v];
  for(int i=0;i<v;i++)
  {
    adjList[i]=NULL;
    cout<<"Enter Vertice "<<(i+1)<<endl;
    cin>>vertices[i];
  }
  for(int i=0;i<v;i++)
  {
    int k,data;
    cout<<"Enter Number of Neighbours of "<<vertices[i];
    cin>>k;
    for(int j=0;j<k;j++)
    {
      cout<<"Enter Neighbour "<<(j+1)<<" of "<<vertices[i];
      cin>>data;
      push(&adjList[i], data);
    }
  }

  topsort(adjList,v,vertices);
}

/*

dfs(visited,adjlist,v)
{
for i in adjlist[v]:
  if not visited[i]:
    visited[i] = true
    dfs(visited,adjlist,i)
return	
}

dfsmain(adjlist,vertices)
{
visited[]=false
for i in vertices:
  if not visited[i]:
    visited[i]=true
    dfs(visited,adjlist,i)
}
*/