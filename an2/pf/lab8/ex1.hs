import System.Environment

--tip de date "IO"
--reprezinta o actiune/comanda
--daca cineva produce actiunea,
--la sfarsit se produce o valoarea de tip "a";

--IO () asta produce o valoare unit (singura posibila)
--IO String asta produce un string

f:: Int -> () --"Unit"
f _ = ()

-- (>>) :: IO () -> IO () -> IO ()

-- main :: IO ()
-- --main = (putStrLn "Hello, World!") >> (putStrLn "Nice!")
-- main = do
--     putStrLn "Hello, World!"
--     putStrLn "Nice!"
--     putStrLn "I'm x!"

-- (>>=) :: IO String -> (String -> IO ()) -> IO ()

main :: IO ()
main = do
    putStrLn "Enter your name:"
    x <- getLine
    putStrLn ("Hello, " ++ x ++ "!")
-- main = (putStrLn "Enter your name: ") >> (getLine >>= (\x -> putStrLn ("Hello, " ++ x))