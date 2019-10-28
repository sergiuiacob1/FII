#20 accounts
hack = function (){
  currentlyHacked = vector (mode = "integer", length = 20)
  wasHacked = vector (mode = "integer", length = 20)
  for (i in 1:20){
    currentlyHacked[i] = 0;
    wasHacked[i] = 0;
  }
  
  victim = sample.int (20, 1, replace=T)
  currentlyHacked[victim] = 1
  wasHacked[victim] = 1
  infected = 1
  
  while (infected>0 && infected<20){
    for (i in 1:20){
      #25% probabilitate sa fie hacked
      prob = sample.int(100, 1, replace=T)
      if (currentlyHacked[i] == 0 && prob>=75){#25% sanse ca prob sa fie [75, 100]
        currentlyHacked[i] = 1
        wasHacked[i] = 1
        infected = infected + 1
      }
    }
    
    if (infected == 20)
      return (c(20, 20))
  
    #clean 5 random
    cleaned = 0
    while (cleaned!=5 && infected>0){
      victim = sample.int (20, 1, replace=T)
      
      if (currentlyHacked[victim] == 1){
        currentlyHacked[victim] = 0
        infected = infected - 1
        cleaned = cleaned + 1
      }
    }
  }
  
  hackedAtLeastOnce = 0
  for (i in 1:20){
    if (wasHacked[i] == 1)
      hackedAtLeastOnce = hackedAtLeastOnce + 1
  }
  
  rez = c(hackedAtLeastOnce, infected)
}

allHackedOnce = 0
allHackedInOneDay = 0
nrRuns = 1000

for (i in 1:nrRuns){
  rez = hack()
  if (rez[1] == 20)
    allHackedOnce = allHackedOnce + 1
  if (rez[2] == 20)
    allHackedInOneDay = allHackedInOneDay + 1
}

print ("Pct a: ")
print (allHackedOnce/nrRuns)
print ("Pct b: ")
print (allHackedInOneDay/nrRuns)

#Pct c:
alfa = 1-0.99
z = qnorm (alfa/2)
epsilon = 0.01
p = 0.0966 #ghicim o probabilitate (cea calc. cu 10000 de rulari)
Nmin = p*(1-p)*((z/epsilon)^2)
print (Nmin)
