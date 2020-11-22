#include <stdio.h>
#include <stdlib.h>

int INF = 1000000;

struct node
{
  int vertex;
  int weight;
  struct node *next;
};

struct graph
{
  int V;
  int parent;
  struct node *adjList;
};

void input(struct graph G[], int nV)
{
  int i;
  for (i = 0; i < nV; i++)
  {
    G[i].V = i;
    G[i].adjList = NULL;
    G[i].parent = -1;
    printf("Enter elements adjacent to vertex %d (-1 to stop)\n", G[i].V);
    int v, w;
    while (1)
    {
      scanf("%d,%d", &v, &w);
      if (v == -1)
      {
        break;
      }
      struct node *temp = (struct node *)malloc(sizeof(struct node));
      temp->vertex = v;
      temp->weight = w;
      temp->next = G[i].adjList;
      G[i].adjList = temp;
    }
  }
}

void display(struct graph G[], int nV)
{
  int i;
  printf("Parent \t Vertex \t Adjacency list\n");
  for (i = 0; i < nV; i++)
  {
    printf("%6d \t %6d \t ", G[i].parent, G[i].V);
    struct node *iterator = G[i].adjList;
    while (iterator != NULL)
    {
      printf("(%d,%d)", iterator->vertex, iterator->weight);
      iterator = iterator->next;
    }
    printf("\n");
  }
}

void print(int distance[], int nV)
{
  for (int i = 0; i < nV; i++)
  {
    if (distance[i] == INF)
    {
      printf("INF ,");
    }
    else if (distance[i] == -INF)
    {
      printf("-INF ,");
    }
    else
    {
      printf("%d ,", distance[i]);
    }
  }
  printf("\n");
}

void bellman_ford(int distance[], struct graph G[], int nV, int start)
{
  distance[start] = 0;
  for (int j = 0; j < nV - 1; j++)
  {
    for (int i = 0; i < nV; i++)
    {
      struct node *iterator = G[i].adjList;
      while (iterator != NULL)
      {
        if (distance[i] + iterator->weight < distance[iterator->vertex])
        {
          G[iterator->vertex].parent = i;
          distance[iterator->vertex] = distance[i] + iterator->weight;
        }
        iterator = iterator->next;
      }
    }
  }
}

void bellman_ford_neg(int distance[], struct graph G[], int nV, int start)
{
  for (int j = 0; j < nV - 1; j++)
  {
    for (int i = 0; i < nV; i++)
    {
      struct node *iterator = G[i].adjList;
      while (iterator != NULL)
      {
        if (distance[i] + iterator->weight < distance[iterator->vertex])
        {
          distance[iterator->vertex] = -INF;
        }
        iterator = iterator->next;
      }
    }
  }
}

void displayList(struct node *head)
{
  printf("START -> ");
  while (head != NULL)
  {
    printf("%d -> ", head->vertex);
    head = head->next;
  }
  printf("END\n\n");
}

void path(struct graph G[], int nV, int start, int end)
{
  if (G[end].parent == -1)
  {
    printf("\n\n NO PATH EXISTS !!");
    return;
  }
  int i = end;
  struct node *head = NULL;
  printf("\n        SHORTEST PATH FROM %d TO %d : \n", start, end);
  while (i != -1)
  {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
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
  int nV, start, end;
  printf("Enter number of vertices : ");
  scanf("%d", &nV);
  struct graph G[nV];
  // INPUT INTO ADJACENCY LIST
  input(G, nV);
  // DISPLAYING ADJACENCY LIST BEFORE BFS
  printf("\n        ADJACENCY LIST (BEFORE DIJKSTRA) \n");
  display(G, nV);
  // INPUT START AND END VERTEX
  printf("\nEnter start vertex : ");
  scanf("%d", &start);
  printf("\nEnter end vertex : ");
  scanf("%d", &end);
  // BELLMAN-FORD
  int distance[nV];
  for (int i = 0; i < nV; i++)
  {
    distance[i] = INF;
  }
  printf("\n DISTANCES (BEFORE BELLMAN-FORD) : \n");
  print(distance, nV);
  bellman_ford(distance, G, nV, start);
  printf("\n DISTANCES (AFTER BELLMAN-FORD): \n");
  print(distance, nV);
  bellman_ford_neg(distance, G, nV, start);
  printf("\n DISTANCES (AFTER BELLMAN-FORD DETECTS NEG CYCLES): \n");
  print(distance, nV);
  // DISPLAYING ADJACENCY LIST AFTER BELLMAN-FORD
  printf("\n        ADJACENCY LIST (AFTER BELLMAN-FORD) \n");
  display(G, nV);
  path(G, nV, start, end);
  return 0;
}