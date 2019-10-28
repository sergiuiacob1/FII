ipoteza=function(n, succese, p0, asimetric, alfa){
  p_prim = succese/n
  zStea = (p_prim-p0)/sqrt(p0*(1 - p0)/n)

  if(asimetric == "st")
    critical_z = qnorm(alfa, 0, 1)
  if(asimetric == "dr")
    critical_z = qnorm(1 - alfa, 0, 1)
  if(asimetric == "sim")
    critical_z = qnorm(1 - alfa / 2, 0, 1)
  
  if(asimetric == "st"){
    if(zStea<critical_z)
      print("Schimbarea a fost utila! (ip. nula respinsa)")
    else print("Schimbarea a fost inutila! (ip. nula nu poate fi respinsa)")
  }
  
  if(asimetric == "dr"){
    if(zStea > critical_z)
      print("Schimbarea a fost utila! (ip. nula respinsa)")
    else print("Schimbarea a fost inutila! (ip. nula nu poate fi respinsa)")
  }
  
  if(asimetric == "sim"){
    if(abs(zStea) > abs(critical_z))
      print("Schimbarea a fost utila! (ip. nula respinsa)")
    else print("Schimbarea a fost inutila! (ip. nula nu poate fi respinsa)")
  }
}


#vreau sa fie asimetric la dreapta
#adica p>p0, verific daca exista mai multi clienti nemultumiti
#deci asimetric = "dr"
ipoteza (112, 14, 0.1, "dr", 0.05)#5% semnificatie
ipoteza (112, 14, 0.1, "dr", 0.01)#1% semnificatie
