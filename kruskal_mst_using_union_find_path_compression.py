import random

edge_list = []
V = int(input('Enter number of vertices : '))
E = int(input('Enter the number of edges : '))
print('Input Specification : U V W')
for i in range(E):
  edge = list(map(int,input('Enter edge {} : '.format(i)).strip().split()))
  edge_list.append(edge)

def swap(a,i,j):
  temp = a[i]
  a[i] = a[j]
  a[j] = temp

def quick_sort_3(a,l,r):
  if l>=r:
    return
  pivot_index = random.randint(l,r)
  swap(a,l,pivot_index)
  pivot_index = l
  greater = l+1
  for i in range(l+1,r+1):
    if a[i][2]==a[pivot_index][2]:
      swap(a,i,greater)
      greater=greater+1

    if a[i][2]<a[pivot_index][2]:
      swap(a,i,pivot_index)
      swap(a,i,greater)
      pivot_index=pivot_index+1
      greater=greater+1
  quick_sort_3(a,l,pivot_index-1)
  quick_sort_3(a,greater,r)
  return

def union(id,size,u,v):
  root_u = find(id,u)
  root_v = find(id,v)
  if size[root_u]>=size[root_v]:
    id[root_v] = root_u
    size[root_u]+=size[root_v]
  else:
    id[root_u] = root_v
    size[root_v]+=size[root_u]

def find(id,u):
  if id[u]==u:
    return id[u]
  else:
    x = find(id,id[u])
    id[u] = x
    return id[u]

def kruskal_mst(edge_list,id,size,V):
    mst = 0
    count = 0
    for edge in edge_list:
        if count==V-1:
            return mst
        if find(id,edge[0])!=find(id,edge[1]):
            union(id,size,edge[0],edge[1])
            print('MST INCLUDES EDGE BETWEEN {},{} WITH WEIGHT : {}'.format(edge[0],edge[1],edge[2]))
            mst+=edge[2]
            count+=1
    return mst


quick_sort_3(edge_list,0,E-1)

id = []
size = [1]*V
for i in range(V):
  id.append(i) 


mst = kruskal_mst(edge_list,id,size,V)
print('MST WEIGHT : {}'.format(mst))