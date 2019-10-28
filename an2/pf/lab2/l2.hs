data Boolean = Adev | Fals deriving Show

negatie :: Boolean -> Boolean
negatie Adev = Fals
negatie Fals = Adev

data Zi = Luni | Marti | Miercuri | Joi | Vineri | Sambata | Duminica
    deriving Show

next :: Zi -> Zi
next Luni = Marti
next Marti = Miercuri

data Nat = Zero | Succ Nat deriving Show

convert :: Nat -> Int
convert Zero = 0
convert (Succ n) = (convert n) + 1

convert' :: Int -> Nat
convert' 0 = Zero
convert' n = Succ (convert' (n - 1))

add :: Nat -> Nat -> Nat
add Zero n = n
add (Succ x) n = Succ (add x n)

mult :: Nat -> Nat -> Nat
mult Zero n = Zero
mult (Succ x) n = add (mult x n) n

data L a = N | C a (L a) deriving Show

len :: L a -> Int
len N = 0
len (C a x) = len x + 1

dbl :: L Int -> L Int
dbl N = N
dbl (C a list) = C (a*2) (dbl list)

adaugaLaSf :: L a -> a -> L a
adaugaLaSf N a = C a N
adaugaLaSf (C a l) c = C a (adaugaLaSf l c)

--reverse: primeste o lista si intoarce lista inversata
--append: primeste 2 liste si le concateneaza
--trei functii la alegere pe tipurile de date algebrice

reverseL :: L a -> L a
reverseL N = N;
reverseL (C x list) = adaugaLaSf (reverseL list) x

append :: L a -> L a -> L a
append list N = list
append N list = list
append list1 (C y list2) = append (adaugaLaSf list1 y) list2

stergeDeLaInc :: L a -> L a
stergeDeLaInc N = N
stergeDeLaInc (C x list) = list

stergeDeLaSf :: L a -> L a
stergeDeLaSf N = N
stergeDeLaSf (C x N) = N
stergeDeLaSf list = reverseL (stergeDeLaInc (reverseL list))

