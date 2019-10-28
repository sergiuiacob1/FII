add2 :: Int -> Int
add2 x = x + 2

add2' = \x -> x + 2

functie y = \x -> x + 2

add2'' = functie 2

huh f = \x -> f (f x)

double x = x + x
triple x = 3 * x
adauga s = 'a':s