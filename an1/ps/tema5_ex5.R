T_test_means=function(caz, alfa, n1, n2, s1, s2, xn1, xn2, m0)
{
  #!!!!!DISPERSIILE NU SUNT EGALE!!!!!!
  
  FsCritical = qf(alfa/2, n1 - 1, n2 - 1)
  FdCritical = qf(1 - alfa/2, n1 - 1, n2 - 1)
  FStea = (s1^2)/(s2^2)
  
  if(FStea < FsCritical || FStea > FdCritical)
  {
    df = min(n1 - 1, n2 - 1)
    combined_sigma = sqrt((s1^2)/n1 + (s2^2)/n2)
  }
  else
  {
    df = n1 + n2 - 2
    combined_sigma = sqrt(((n1 - 1)*(s1^2) + (n2 - 1)*(s2^2))/df)*sqrt((1/n1)+(1/n2))
  }
  
  if(caz=="st")
    tStea = qt(alfa/2, df)
  
  if(caz=="dr")
    tStea = qt(1 - alfa, df)
  
  if(caz=="sim")
    tStea = qt(1 - (alfa/2), df)
  
  tCritical = (xn1 - xn2 - m0)/combined_sigma

  if(caz=="st")
  {
    if(tCritical<tStea)
      print("Ipoteza nula respinsa")
    else
      print("Ipoteza nula nu este respinsa")
  }
  
  if(caz=="dr")
  {
    if(tCritical>tStea)
      print("Ipoteza nula respinsa")
    else
      print("Ipoteza nula nu este respinsa")
  }
  
  if(caz=="sim")
  {
    if(abs(tCritical)>abs(tStea))
      print("Ipoteza nula respinsa")
    else
      print("Ipoteza nula nu este respinsa")
  }
}

T_test_means("sim", 0.05, 66, 68, 1.2, 1.1, 21, 20, 0)

