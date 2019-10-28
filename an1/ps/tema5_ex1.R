statistic_test_t_sample = function(sample, val_ipoteza, confidence_level, asimetric_st)
{
  alfa = 1 - confidence_level
  media = mean(sample)
  s = sd(sample)
  n = length(sample)
  tScore = (media - val_ipoteza) / (s/sqrt(n))
  print("Scor test:")
  print(tScore)
  if (asimetric_st)
  {
    tStea = qt(alfa,n-1)
    print("Scor t:")
    print(tStea)
    if (tScore<tStea)
      print("Ipoteza nula H0 este respinsa")
    else
      print("Nu exista suficiente dovezi pentru a respinge ipoteza nula H0 si a accepta ipoteza alternativa Ha")
  }
  else#sunt pe dreapta
  {
    tStea = qt(1-alfa,n-1)
    print("Scor t:")
    print(tStea)
    if (tScore>tStea)
      print("Ipoteza nula H0 este respinsa")
    else
      print("Nu exista suficiente dovezi pentru a respinge ipoteza nula H0 si a accepta ipoteza alternativa Ha")
  }
}

sample = c(1.64, 1.54, 1.56, 1.57, 1.44, 1.48, 1.56)
statistic_test_t_sample(sample, 1.6, 0.99, 1)
