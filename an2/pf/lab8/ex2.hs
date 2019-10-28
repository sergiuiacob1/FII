import System.Environment
import System.IO

-- printStringList :: [String] -> IO ()
-- printStringList [] = return ()
-- printStringList (x:xs) = do
--                             putStrLn x
--                             printStringList xs

-- main :: IO ()
-- main = do
--     ls <- getArgs
--     printStringList ls

printLineByLine :: Handle -> IO ()
printLineByLine handle = do
                            rez <- hIsEOF handle
                            case rez of
                                True -> return ()
                                False -> do
                                    line <- hGetLine handle
                                    putStrLn line
                                    printLineByLine handle

printFileContents :: String -> IO ()    
printFileContents filename = do
                                handle <- openFile filename ReadMode
                                printLineByLine handle
                                

main :: IO ()
main = do
        ls <- getArgs
        case ls of
            [] -> putStrLn "Please provide filename!"
            (x:_) -> printFileContents x