f x = 2 * x

suma :: Int -> Int -> Int
suma x y = x + y

arie ray = pi * ray^2
arie' ray = pi * ray * ray

si x y = x && y
negatie x = not x

identitate x = not (not x)
identitate' x = x

sumn :: Int -> Int
sumn n = div (n * (n + 1)) 2

sumn' :: Int -> Int
sumn' 0 = 0 a
sumn' n = n + (sumn' (n - 1))

fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n - 1) + fib (n - 2)

fibo' 0 a b = a
fibo' 1 a b = b
fibo' n a b = fibo' (n - 1) b (a + b)

fibo n = fibo' n 0 1

sumnaux 0 a = a
sumnaux n a = sumnaux (n - 1) (a + n)

sumn'' n = sumnaux n 0

fact :: Int -> Int
fact n = fact' n 1

fact' :: Int -> Int -> Int
fact' 0 a = 
fact' n a = fact' (n-1) a * n