first_int = function(N) {
  sum = 0;
  for(i in 1:N) {
    x = runif (1, 0, 1);
    sum = sum + (cos(50*x) + sin(20*x))^2;
  }
  return(sum/N);
}


valAproximata = first_int (1000)
print ("Prima integrala: ")
print (valAproximata)

second_int =function(N) {
  sum = 0;
  for(i in 1:N) {
    x = runif (1, 0, 3);
    sum = sum + x^3/(1+x^4)
  }
  return(3*sum/N);
}

valActuala = 1.10168
#in document apare 1.01168, dar e gresit!!! corect este 1.10168 (am calculat)
valAproximata = second_int (1000)

err_abs=abs (valActuala - valAproximata)

print("A doua integrala:")
err_rel = err_abs/valActuala
err_proc = err_rel * 100

print (valActuala)
print (valAproximata)
print (err_abs)
print (err_rel)
print (err_proc)
