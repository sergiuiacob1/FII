t_conf_interval = function(n, media, deviatia_standard, confidence_level)
{
  alfa=1-confidence_level
  err_std = deviatia_standard / sqrt(n)
  critical_t = qt(1-alfa/2,n-1)
  a = media - critical_t*err_std
  b = media + critical_t*err_std
  if (a > b)
  {
    aux = a
    a = b
    b = aux
  }
  interval = c(a,b)
  return(interval)
}

rez = t_conf_interval(144,20,sqrt(18),0.9)
print(rez)
