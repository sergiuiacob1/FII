{-

Mai jos avem un tip de date pentru expresii aritmetice cu numere
(intregi pe 32 de biti), + si *.

De exemplu, expresia matematica (3 + 4) * 5 este reprezentata de
valoarea Haskell:

-- > Produs (Suma (Numar 3) (Numar 4)) (Numar 5)
-- Produs (Suma (Numar 3) (Numar 4)) (Numar 5)

-}

data Exp = Numar Int
         | Suma Exp Exp
         | Produs Exp Exp
         | MinusUnar Exp
         | MinusBinar Exp Exp
         | Impartire Exp Exp
         deriving Show

{-

Exercitiul 1

Cum reprezentam expresia aritmetica 4 * (3 + 2) * 2?
Produs (Produs (Numar 4) (Suma (Numar 3) (Numar 2))) (Numar 2)
-}

{-

Dandu-se o expresie aritmetica, putem calcula valoarea acesteia
folosind functia "eval":

-}

eval :: Exp -> Int
eval (Numar n) = n
eval (Suma e1 e2) = (eval e1) + (eval e2)
eval (Produs e1 e2) = (eval e1) * (eval e2)
eval (MinusUnar exp) = -(eval exp)
eval (MinusBinar exp1 exp2) = eval(exp1) - eval(exp2)
eval (Impartire e1 e2) = div (eval (e1)) (eval (e2))

{-

Exercitiul 2

Extindeti tipul Exp cu constructori pentru:

1) minus unar (e.g. MinusUnar (Numar 5) reprezinta expresia "-5")
2) minus binar (e.g. MinusBinar (Numar 3) (Numar 3) reprezinta expresia "-3")

Adaptati functia eval astfel incat sa trateze si cazul noilor
constructori.

Evaluati folosind functia voastra expresiile -(3 + 4) si ((-3) * 4) +
(10 * 2).

-}


{-

Exercitiul 3

Extindeti expresiile cu operatia de impartire.

Ce se intampla in cazul unei impartiri prin 0?

-}



{-
Tipuri parametrizate

Tipul parametrizat List:
> import Data.List
> :i []
data [] a = [] | a : [a]
...
In definitia tipul de date List, "a" este o variabila de tip. 
Prin urmare definitia listelor este parametrica in tipul elementelor.
...

Tipul parametrizat Maybe:

> :i Maybe
data Maybe a = Nothing | Just a
...
Tipul "Maybe a" contine toate valorile tipului "a", protejate de constructorul "Just",
precum si inca o valoare "Nothing". De exemplu, valorile de tip Maybe Int sunt
Nothing, Just 0, Just (-2), Just 7, ...

Cum ne-ar putea ajuta acest tip sa tratam cazul impartirii la zero?
-}

data Poate a = Nimic | Doar a deriving Show

--2 constructori; a este o variabila de tip (poate primi orice tip de date)
--valorile pentru Poate Bool pot fi Nimic, Doar True, Doar False
--valorile pentru Poate Int: Nimic, Doar 1, Doar (-10) etc.

--Poate (Poate Bool)
--1. Nimic
--2. Doar Nimic
--3. Doar (Doar True)
--4. Doar (Doar False)

safediv :: Int -> Int -> Poate Int
safediv a 0 = Nimic
safediv a b = Doar (div a b)

saferdiv :: Poate Int -> Poate Int -> Poate Int
--saferdiv a Nimic = Nimic
--saferdiv Nimic b = Nimic
--saferdiv Nimic Nimic = Nimic
saferdiv (Doar a) (Doar b) = safediv a b
saferdiv _ _ = Nimic