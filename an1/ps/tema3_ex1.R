#C1
abs_error = function(calculated_value,expected_value)
{
  rez=calculated_value -expected_value
  if (rez<0)
    rez=-rez
  return(rez)
}

rel_error = function(calculated_value,expected_value)
{
  rez=abs_error(calculated_value,expected_value)
  if (expected_value < 0)
    expected_value = -expected_value
  rez=rez/expected_value
  return(rez)
}

elipsoid_volume = function(N,a,b,c)
{
  N_C = 0
  for (i in 1:N)
  {
    x = runif(1,-a,a)
    y = runif(1,-b,b)
    z = runif(1,-c,c)
    
    if ( (x*x)/(a*a) + (y*y)/(b*b) + (z*z)/(c*c) <= 1)
      N_C = N_C +1
  }
  return( (a+a)*(b+b)*(c+c)*N_C / N )
}

rez = elipsoid_volume(10000,2,3,4)
print(rez)
abs_error(rez,(4*3.141592*24)/3)
rel_error(rez,(4*3.141592*24)/3)

rez = elipsoid_volume(20000,2,3,4)
print(rez)
abs_error(rez,(4*3.141592*24)/3)
rel_error(rez,(4*3.141592*24)/3)

rez = elipsoid_volume(50000,2,3,4)
print(rez)
abs_error(rez,(4*3.141592*24)/3)
rel_error(rez,(4*3.141592*24)/3)
