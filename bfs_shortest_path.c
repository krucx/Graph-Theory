#include <stdio.h>
#include<stdlib.h>

struct node
{
  int v;
  struct node* next; 
};

struct graph
{
  int V;
  int parent;
  struct node* adjList;
};


// QUEUE OPERATIONS:
int dequeue(struct node** qhead,struct node** qtail)
{
  int v;
  struct node* temp = *qhead;
  *qhead = (*qhead)->next;
  v = temp->v;
  free(temp);
  if(*qhead==NULL)
  {
    *qtail = NULL;
  }
  return v;
}

void enqueue(struct node** qhead,struct node** qtail,int v)
{
  struct node* temp = (struct node*)malloc(sizeof(struct node));
  temp->v = v;
  temp->next = NULL;
  if(*qtail==NULL)
  {
    *qhead = temp;
    *qtail = temp;
  }
  else
  {
    (*qtail)->next=temp;
    (*qtail)=(*qtail)->next;
  }
}

// INPUT AS ADJACENCY LIST
void input(struct graph G[],int nV)
{
  int i;
  for(i=0;i<nV;i++)
  {
    printf("Enter vertex %d : ",i+1);
    scanf("%d",&(G[i].V));
    G[i].adjList = NULL;
    G[i].parent = -1;
    printf("Enter elements adjacent to vertex %d (-1 to stop)\n",G[i].V);
    int v;
    while(1)
    {
      scanf("%d",&v);
      if(v==-1)
      {
        break;
      }
      struct node* temp = (struct node*)malloc(sizeof(struct node));
      temp->v = v;
      temp->next = G[i].adjList;
      G[i].adjList = temp;
    }
  }
}

// DISPLAY ADJACENCY LIST
void display(struct graph G[],int nV)
{
  int i;
  printf("Parent \t Vertex \t Adjacency list\n");
  for(i=0;i<nV;i++)
  {
    printf("%6d \t %6d \t ",G[i].parent,G[i].V);
    struct node* iterator = G[i].adjList;
    while(iterator!=NULL)
    {
      printf("%d, ",iterator->v);
      iterator = iterator->next;
    }
    printf("\n");
  }
}

// DISPLAY LINKED LIST
void displayList(struct node* head)
{
  printf("START -> ");
  while(head!=NULL)
  {
    printf("%d -> ",head->v);
    head=head->next;
  }
  printf("END\n\n");
}

// RETURNS INDEX OF VERTEX IN GRAPH
int indexOf(struct graph G[],int nV,int V)
{
  int i;
  for(i=0;i<nV;i++)
  {
    if(G[i].V==V)
    {
      return i;
    }
  }
  return 0;
}

// BFS TO FIND SHORTEST PATH FROM START TO END
void bfs(struct graph G[],int nV,int start,int end)
{
  struct node* qhead = NULL;
  struct node* qtail = NULL;
  enqueue(&qhead,&qtail,start);
  int s,i;
  while(qhead!=NULL)
  {
    s = dequeue(&qhead,&qtail);
    i = indexOf(G,nV,s);
    struct node* iterator = G[i].adjList;
    while(iterator!=NULL)
    {
      if(G[indexOf(G,nV,iterator->v)].parent==-1&&iterator->v!=start)
      {
        enqueue(&qhead,&qtail,iterator->v);
        G[indexOf(G,nV,iterator->v)].parent = s;
      }
      if(iterator->v==end)
      {
        return;
      }
      iterator = iterator->next;
    }
  }
}

// PRINTS PATH BY FOLLOWING PARENTS STARTING FROM END VERTEX
void path(struct graph G[],int nV,int start,int end)
{
  if(G[indexOf(G,nV,end)].parent==-1)
  {
    printf("\n\n NO PATH EXISTS !!");
    return;
  }
  int i=end;
  struct node* head = NULL;
  printf("\n        SHORTEST PATH FROM %d TO %d : \n",start,end);
  while(i!=-1)
  {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->v = i;
    temp->next = head;
    head = temp;
    i = G[indexOf(G,nV,i)].parent;
  }
  displayList(head);
  printf("\n");
}

int main(void) 
{
  int nV,start,end;
  printf("Enter number of vertices : ");
  scanf("%d",&nV);
  struct graph G[nV];
  // INPUT INTO ADJACENCY LIST
  input(G,nV);
  // DISPLAYING ADJACENCY LIST BEFORE BFS
  printf("\n        ADJACENCY LIST (BEFORE BFS) \n");
  display(G,nV);
  // INPUT START AND END VERTEX
  printf("\nEnter start vertex : ");
  scanf("%d",&start);
  printf("Enter end vertex : ");
  scanf("%d",&end);
  // BFS
  bfs(G,nV,start,end);
  // DISPLAYING ADJACENCY LIST AFTER BFS
  printf("\n        ADJACENCY LIST (AFTER BFS) \n");
  display(G,nV);
  // SHORTEST PATH FROM START TO END
  path(G,nV,start,end);
  return 0;
}