#include <stdio.h>
#include <stdlib.h>

int INF = 1000000;

struct node
{
  int vertex;
  int weight;
  struct node* left;
  struct node* right;
};

struct node1
{
  int vertex;
  int weight;
  struct node1* next;
};

struct graph
{
  int V;
  int parent;
  struct node1* adjList;
};


void input(struct graph G[],int nV)
{
  int i;
  for(i=0;i<nV;i++)
  {
    G[i].V=i;
    G[i].adjList = NULL;
    G[i].parent = -1;
    printf("Enter elements adjacent to vertex %d (-1 to stop)\n",G[i].V);
    int v,w;
    while(1)
    {
      scanf("%d,%d",&v,&w);
      if(v==-1||w<0)
      {
        break;
      }
      struct node1* temp = (struct node1* )malloc(sizeof(struct node1));
      temp->vertex = v;
      temp->weight = w;
      temp->next = G[i].adjList;
      G[i].adjList = temp;
    }
  }
}

void display(struct graph G[],int nV)
{
  int i;
  printf("Parent \t Vertex \t Adjacency list\n");
  for(i=0;i<nV;i++)
  {
    printf("%6d \t %6d \t ",G[i].parent,G[i].V);
    struct node1* iterator = G[i].adjList;
    while(iterator!=NULL)
    {
      printf("(%d,%d)",iterator->vertex,iterator->weight);
      iterator = iterator->next;
    }
    printf("\n");
  }
}





// PRIORITY QUEUE

/*
int search_edge_and_update(struct node** root,struct node* temp)
{
  if(*root==NULL)
  {
    return 0;
  }
  if((*root)->vertex1==temp->vertex1 && (*root)->vertex2==temp->vertex2)
  {
    (*root)->weight = temp->weight;
    return 1;
  }
  return search_edge_and_update(&(*root)->left,temp) + search_edge_and_update(&(*root)->right,temp);
}
*/

void insert(struct node* temp,struct node ** root)
{
  if(*root==NULL)
  {
    *root = temp;
    return;
  }
  if(temp->weight<(*root)->weight)
  {
    insert(temp,&(*root)->left);
  }
  else
  {
    insert(temp,&(*root)->right);
  }
}

void insert_into_priority(struct node** root,int vertex,int weight)
{
  struct node* temp = (struct node*)malloc(sizeof(struct node));
  temp->left = NULL;
  temp->right = NULL;
  temp->vertex = vertex;
  temp->weight = weight;
  insert(temp,root);
}

struct node* pop(struct node** root)
{
  struct node* poped = NULL;
  if((*root)->left==NULL)
  {
    poped = *root;
    *root=(*root)->right;
  }
  else
  {
    struct node* iterator = *root;
    while((iterator->left)->left!=NULL)
    {
      iterator = iterator->left;
    }
    poped = iterator->left;
    iterator->left = (iterator->left)->right;
  }
  return poped;
}

void inorder(struct node* root)
{
  if(root==NULL)
  {
    return;
  }
  inorder(root->left);
  printf("( %d , %d ) -> ",root->vertex,root->weight);
  inorder(root->right);
}

// PRIORITY QUEUE
void print(int distance[],int nV)
{
  for(int i=0;i<nV;i++)
  {
    if(distance[i]==INF)
    {
      printf("INF ,");
    }
    else
    {
      printf("%d ,",distance[i]);
    }
  }
  printf("\n");
}

void dijkstra(int distance[],struct graph G[],int nV,int start)
{
  struct node* root = NULL;
  distance[start] = 0;
  insert_into_priority(&root,start,distance[start]);
  while(root!=NULL)
  {
    struct node* temp = pop(&root);
    if(temp->weight>distance[temp->vertex])
    {
      continue;
    }
    struct node1* iterator = G[temp->vertex].adjList;
    while(iterator!=NULL)
    {
      if(distance[iterator->vertex]>distance[temp->vertex]+iterator->weight)
      {
        G[iterator->vertex].parent = temp->vertex;
        distance[iterator->vertex]=distance[temp->vertex]+iterator->weight;
        insert_into_priority(&root,iterator->vertex,distance[iterator->vertex]);
      }
      iterator = iterator->next;
    }
  }
}


void displayList(struct node1* head)
{
  printf("START -> ");
  while(head!=NULL)
  {
    printf("%d -> ",head->vertex);
    head=head->next;
  }
  printf("END\n\n");
}


void path(struct graph G[],int nV,int start,int end)
{
  if(G[end].parent==-1)
  {
    printf("\n\n NO PATH EXISTS !!");
    return;
  }
  int i=end;
  struct node1* head = NULL;
  printf("\n        SHORTEST PATH FROM %d TO %d : \n",start,end);
  while(i!=-1)
  {
    struct node1* temp = (struct node1*)malloc(sizeof(struct node1));
    temp->vertex = i;
    temp->next = head;
    head = temp;
    i = G[i].parent;
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
  printf("\n        ADJACENCY LIST (BEFORE DIJKSTRA) \n");
  display(G,nV);
  // INPUT START AND END VERTEX
  printf("\nEnter start vertex : ");
  scanf("%d",&start);
  printf("\nEnter end vertex : ");
  scanf("%d",&end);
  // DIJKSTRA
  int distance[nV];
  for(int i=0;i<nV;i++)
  {
    distance[i]=INF;
  }
  printf("\n DISTANCES (BEFORE DIJKSTRA) : \n");
  print(distance,nV);
  dijkstra(distance,G,nV,start);
  printf("\n DISTANCES (AFTER DIJKSTRA): \n");
  print(distance,nV);
  // DISPLAYING ADJACENCY LIST AFTER BFS
  printf("\n        ADJACENCY LIST (AFTER DIJKSTRA) \n");
  display(G,nV);
  path(G,nV,start,end);
  return 0;
}