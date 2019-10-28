nr = c (5, 1, 4, 2, 7, 3, 6, 6)

quicksort = function (st, dr){
  if (st<dr){
    poz = divide (st, dr);
  
    quicksort (st, poz);
    quicksort (poz+1, dr);
  }
}

divide=function (left, right){
  pozPivot = sample(left:right, 1);
  pivot = nr[pozPivot];
  
  st=left
  dr=right;
  
  aux = nr[st];
  nr[st] <<- nr[pozPivot]
  nr[pozPivot] <<- aux
  
  while (st<dr){
    while (st<dr && nr[dr]>=pivot){
      dr=dr-1
    }
    
    while (st<dr && nr[st]<=pivot){
      st=st+1
    }
    
    if (st<dr){
      aux = nr[st];
      nr[st] <<- nr[dr];
      nr[dr] <<- aux;
    }
  }
  
  aux = nr[left];
  nr[left] <<- nr[dr];
  nr[dr] <<- aux;
  return (dr);
}

quicksort (1, length(nr))
print (nr)
