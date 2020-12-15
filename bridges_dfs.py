adj_list = []
V = int(input('Enter the number of vertices : '))
for i in range(V):
  adj_list.append(list(map(int,input('Enter adjacent vertices to {} : '.format(i)).strip().split())))

def dfs_bridges(adj_list,vertex,parent,low_link,V):
  global id_stamp
  low_link[vertex] = id_stamp
  id_stamp+=1
  for i in adj_list[vertex]:
    if i==parent:
      continue
    if low_link[i]==V+1:
      x = dfs_bridges(adj_list,i,vertex,low_link,V)
      if x<low_link[vertex]:
        low_link[vertex] = x
    else:
      if low_link[i]<low_link[vertex]:
        low_link[vertex] = low_link[i]
  return low_link[vertex]

def print_bridges(adj_list,low_link,V):
  for i in range(V):
    for j in adj_list[i]:
      if i>j:
        continue
      if low_link[i]!=low_link[j]:
        print('BRIDGE BETWEEN {} and {}'.format(i,j))

low_link = [V+1]*V
id_stamp = 0
dfs_bridges(adj_list,0,-1,low_link,V)
print_bridges(adj_list,low_link,V)