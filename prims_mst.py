V = int(input('Enter number of vertices : '))
E = int(input('Enter the number of edges : '))
print('Input Specification : U V W')
adj_list = []
for i in range(V):
  adj_list.append([])
for i in range(E):
  edge = list(map(int,input('Enter edge {} : '.format(i)).strip().split()))
  adj_list[edge[0]].append((edge[2],edge[1]))
  adj_list[edge[1]].append((edge[2],edge[0]))

def set_priority(in_pq,index,priority):
  if in_pq[index]>priority:
    in_pq[index] = priority
    return 1
  return 0

def poll(in_pq):
  min = in_pq[0]
  index = 0
  for i in range(len(in_pq)):
    if in_pq[i]<min:
      min = in_pq[i]
      index = i
  in_pq[index] = float('inf')
  return index,min

def prims(adj_list,in_pq,V):
  mst = 0
  count = 0
  set_priority(in_pq,0,0)
  visited = [0]*V
  parent = [-1]*V
  s = []
  while count<=V-1:
    index,priority = poll(in_pq)
    visited[index] = 1
    mst+=priority
    count+=1
    s.append("MST INCLUDES EDGE BETWEEN {},{} WITH WEIGHT : {}".format(index,parent[index],priority))
    for i in adj_list[index]:
      if visited[i[1]]==0:
        if set_priority(in_pq,i[1],i[0])==1:
          parent[i[1]] = index
  print('\n'.join(s[1:]))
  return mst

in_pq = [float('inf')]*V
mst = prims(adj_list,in_pq,V)
print('MST WEIGHT : {}'.format(mst))