aprox_waiting_time = function(n){
  
  time = 0
  for (i in 1:n)
  {
    time = time + rexp(1,1) #latenta client-server
    server_chance = runif(1,0,1)
    if (server_chance < 0.5)
      time = time + rgamma(1,5,3) #request server 1
    else
    {if (server_chance < 0.8)
      time = time + rgamma(1,7,5) # request server 2
    else
      time = time + rgamma(1,5,2) # request server 3
    }
    time = time + rexp(1,1) #latenta server-client
  }
  
  return (time/n)
}

rez = aprox_waiting_time(10000)
print(rez)

rez = aprox_waiting_time(20000)
print(rez)

rez = aprox_waiting_time(50000)
print(rez)