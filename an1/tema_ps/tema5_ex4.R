z_test_means=function(caz, alfa, m0, n1, n2, xn1, xn2, sigma1, sigma2)
{
  combined_sigma = sqrt((sigma1^2)/n1 + (sigma2^2)/n2)
  if(caz=="st")
    critical_z = qnorm(alfa, 0, 1)
  
  if(caz=="dr")
    critical_z = qnorm(1 - alfa, 0, 1)
  
  if(caz=="sim")
    critical_z = qnorm(1 - (alfa/2), 0, 1)
  
  zStea = (xn1-xn2-m0)/combined_sigma
  
  if(caz=="st")
  {
    if(zStea<critical_z)
      print("Ipoteza nula respinsa")
    else
      print("Ipoteza nula nu este respinsa")
  }
  
  if(caz=="dr")
  {
    if(zStea>critical_z)
      print("Ipoteza nula respinsa")
    else
      print("Ipoteza nula nu este respinsa")
  }
  
  if(caz=="sim")
  {
    if(abs(zStea)>abs(critical_z))
      print("Ipoteza nula respinsa")
    else
      print("Ipoteza nula nu este respinsa")
  }
}

z_test_means("sim", 0.01, 0, 155, 150, 15, 14.5, 0.75, 0.78)
z_test_means("sim", 0.05, 0, 155, 150, 15, 14.5, 0.75, 0.78)
