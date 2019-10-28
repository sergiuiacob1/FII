binomial = function(n, p){
  x=seq(0,n-1,1)
  y=dbinom(x,n,p)
  barplot(y,space=0,main='repr. binomial',sub='subtitlul',xlab='axa x',ylab='axa y')
}

poisson = function(n,lambda){
  x=seq(0,n-1,1)
  y=dpois(x,lambda)
  barplot(y,space=0,main='repr. poisson',sub='subtitlul',xlab='axa x',ylab='axa y')
}

geometric = function(n, p){
  x=seq(0,n-1,1)
  y=dgeom(x,p)
  barplot(y,space=0,main='repr. geometrica',sub='subtitlul',xlab='axa x',ylab='axa y')

}

poisson(20, 3)
binomial(10, 0.3)
geometric(10, 0.3)



