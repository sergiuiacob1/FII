vec = c(82, 72, 82, 78, 76, 84, 84, 82, 87, 80, 81, 69, 73, 79, 79,
        75, 68, 80, 74, 68, 77, 80, 78, 81, 76, 75, 70, 76, 78, 82,
        72, 78, 86, 79, 91, 70, 84, 73, 69, 70, 83, 76, 47, 67, 76);

as.vector(summary(vec))[2];
as.vector(summary(vec))[5];

valoriAberante=function(vec){
  medie = mean(vec);
  deviatie = sd(vec);
  vals = vector();
  nr = 0
  for (i in 1:length(vec))
    if (vec[i]<=medie-2*deviatie || vec[i]>=medie+2*deviatie){
       nr = nr + 1;
       vals[nr]=vec[i];
    }

  return (vals);
}


print(median(vec))
print(mean(vec))
print(sd(vec))

print(valoriAberante(vec))
