vector=scan("graf.txt")
graf=matrix(vector, 6, 6)
print(graf)

karger = function(graf,n)
{
  uz = vector(mode="numeric",n)
  for (i in 1:n)
    uz[i]=0
  nodesLeft=n
  
  while (nodesLeft>2)
  {
    i=runif(1,1,n+1)
    j=runif(1,1,n+1)
    if (uz[i]==0 & uz[j]==0 & graf[i,j]>0 & i!=j)
    {
      graf[i,j]=0
      graf[j,i]=0
      uz[j]=1
      
      for (k in 1:n)
        if (k!=i)
          if (graf[k,j]>0)
          {
            graf[i,k]=graf[i,k]+graf[k,j]
            graf[k,i]=graf[k,i]+graf[k,j]
            graf[k,j]=0
            graf[j,k]=0
          }
      
      nodesLeft=nodesLeft-1
    }
  }
  first=0
  second=0
  for (i in 1:n)
    if(uz[i]==0)
      if (first==0)
        first=i
      else
        second=i
  rez=as.numeric(graf[first,second])
  return(rez)
}

min_cut=999
for (i in 1:1000)
    {
    rez=karger(graf,6)
    if (rez<min_cut)
        min_cut=rez
    }

print(min_cut)

