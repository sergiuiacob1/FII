

{-

Exercitiul 1

Scrieti o functie care primeste doua valori de tip Maybe Int si
intoarce o valoare de tip Maybe Int care contine catul impartirii,
daca aceasta se poate calcula, sau Nothing in caz contrar.

-}

impartireMaybe :: Maybe Int -> Maybe Int -> Maybe Int
impartireMaybe (Just a) (Just 0) = Nothing
impartireMaybe (Just a) (Just b) = Just (div a b)
impartireMaybe _ _ = Nothing
{-

Exercitiul 2

Aceeasi cerinta pentru functia sumaMaybe.

-}

sumaMaybe :: Maybe Int -> Maybe Int -> Maybe Int
sumaMaybe (Just a) (Just b) = Just (a + b)
sumaMaybe (Just a) Nothing = Just a
sumaMaybe Nothing (Just a) = Just a
{-

Mai jos avem un tip de date pentru expresii aritmetice cu numere
(intregi pe 32 de biti), "+" si "/".

-}

data Exp = Numar Int
         | Suma Exp Exp
         | Impartire Exp Exp
         | MinusUnar Exp
         | MinusBinar Exp Exp
         | Produs Exp Exp
         | Radical Exp
         | Exponentiere Exp Exp
         | Factorial Exp
         deriving Show

{-

De exemplu, expresia matematica (3 + 4) / 5 este reprezentata de:
-- > Impartire (Suma (Numar 3) (Numar 4)) (Numar 5)
-- Impartire (Suma (Numar 3) (Numar 4)) (Numar 5)

Dandu-se o expresie aritmetica, putem calcula valoarea acesteia
folosind functia "eval":

-}

minusUnarMaybe :: Maybe Int -> Maybe Int
minusUnarMaybe Nothing = Nothing
minusUnarMaybe (Just x) = Just (-x)

minusBinarMaybe :: Maybe Int -> Maybe Int -> Maybe Int
minusBinarMaybe (Just x) (Just y) = Just (x - y)
minusBinarMaybe (Just x) Nothing = Just x
minusBinarMaybe _ _ = Nothing

produsMaybe :: Maybe Int -> Maybe Int -> Maybe Int
produsMaybe (Just x) (Just y) = Just (x * y)
produsMaybe _ _ = Nothing

exponentiereMaybe :: Maybe Int -> Maybe Int -> Maybe Int
exponentiereMaybe (Just a) (Just b) = Just (a ^ b)
exponentiereMaybe _ _ = Nothing
    
castToExp :: Maybe Int -> Exp
castToExp (Just x) = (Numar x)

minusExp :: Exp -> Exp -> Exp
minusExp (Numar x) (Numar y) = Numar (x - y)

eval :: Exp -> Maybe Int
eval (Numar n) = Just n
eval (Suma e1 e2) = sumaMaybe (eval e1) (eval e2)
eval (Impartire e1 e2) = impartireMaybe (eval e1) (eval e2)
eval (MinusUnar e1) = minusUnarMaybe (eval e1)
eval (MinusBinar a b) = minusBinarMaybe (eval a) (eval b)
eval (Produs e1 e2) = produsMaybe (eval e1) (eval e2)
eval (Exponentiere e1 e2) = exponentiereMaybe (eval e1) (eval e2)
eval (Factorial (Numar 0)) = Just 1
eval (Factorial e2) = produsMaybe (eval e2) (eval (Factorial (minusExp (e2) (Numar 1))))
{-

De data aceasta, functia "eval" intoarce o valoare de tip "Maybe Int".
Daca expresia nu contine erori de tipul impartirii prin zero, atunci
rezultatul este "Just n", unde n este un Int care este valoarea
expresiei.  In caz contrar, daca expresia contine erori de tipul
impartirii prin zero, rezultatul este "Nothing".

-}

{-

Exercitiul 3

Incercati sa evaluati, folosind functia de mai sus, expresiile
aritmetice 10 / (3 + -3) si (4 + 5) / 3. Atentie! -3 este numarul
intreg -3 :: Int, nu expresia - 3, adica operatorul minus unar (pe
care nu-l avem deocamdata) aplicat numarului 3.

eval (Impartire (Numar 10) (Suma (Numar 3) (Numar (-3))))


-}

{-

Exercitiul 4

Extindeti tipul Exp cu constructori pentru: minus unar, minus binar,
produs, modulo, radical (intreg), exponentiere, factorial si eventual
alte operatii interesante.  Adaptati functia eval astfel incat sa
trateze si cazul noilor constructori. Testati pe cateva exemple
relevante functiile de mai sus.

-}
