  import Data.Char
import System.Environment


{- Tokenizare -}

{-

Exercitiul 1

Extindeti tokenizatorul, parserul si interpretorul astfel incat limbajul
definit sa permita utilizarea expresiilor booleene: true, false, not, <, >, 
==, <=, =>. 
Aveti grija sa modificati instructiunile 'if' si 'while' astfel incat 
conditiile sa fie expresii booleene.

-} 

data Token = TInt String -- intregi
           | TSuma -- +
           | TMinus -- -
           | TProdus -- *
           | TParenLeft -- (
           | TParenRight -- )
           | TVar String -- variabile
           | TAtrib -- =
           | TSemicolon -- ;
           | TIf -- if
           | TThen -- then
           | TElse -- else
           | TWhile -- while
           | TBraceLeft -- {
           | TBraceRight -- }
           | TBool String
           | TLower
           | TGreater
           | TEqual
           | TLowerEqual
           | TGreaterEqual
             deriving Show

skipWhiteSpace :: String -> String
skipWhiteSpace (' ':rs) = skipWhiteSpace rs
skipWhiteSpace ('\n':rs) = skipWhiteSpace rs
skipWhiteSpace s = s
getInteger :: String -> (String, String)
getInteger (c:cs) | isDigit c = let (cn, cr) = getInteger cs in (c : cn, cr)
getInteger (c:cs)             = ("", c:cs)
getInteger []                 = ("", "")
getString  :: String -> (String, String)
getString (c:cs) | isLetter c = let (cn, cr) = getString cs in (c : cn, cr)
getString (c:cs)              = ("", c:cs)
getString []                  = ("", "")
getBool :: String -> (String, String)
getBool ("True":cs)           = ("True", cs)
getBool ("False":cs)          = ("False", cs)
getBool []                    = ("", "")
getBoolValue :: String -> Bool
getBoolValue "True" = True
getBoolValue "False" = False

keyword :: String -> Maybe Token
keyword "while" = Just TWhile
keyword "if"    = Just TIf
keyword "then"  = Just TThen
keyword "else"  = Just TElse
keyword _       = Nothing
tokenNext :: String -> Maybe (Token, String)
tokenNext s@(c:rs) | isDigit c        = let (x, y) = getInteger s in Just (TInt x, y)
                   | isLetter c       = let (x, y) = getString  s in case keyword x of
                                                                     Just t -> Just (t, y)
                                                                     Nothing -> Just (TVar x, y)
                   | c == '+'         = Just (TSuma, rs)
                   | c == '-'         = Just (TMinus, rs)
                   | c == '*'         = Just (TProdus, rs)
                   | c == '('         = Just (TParenLeft, rs)
                   | c == ')'         = Just (TParenRight, rs)
                   | c == '{'         = Just (TBraceLeft, rs)
                   | c == '}'         = Just (TBraceRight, rs)
                   | c == ';'         = Just (TSemicolon, rs)
                   | isBool c         = let (x, y) = getBool s in Just (TBool x, y)
                   | c == "<"         = Just (TLower, rs)
                   | c == ">"         = Just (TGreater, rs)
                   | c == "=="         = Just (TEqual, rs)
                   | c == "<="         = Just (TLowerEqual, rs)
                   | c == ">="         = Just (TGreaterEqual, rs)
                   | c == "T"         = if ( rs = "rue":rest)
tokenNext _      = Nothing

isBool :: String -> Bool
isBool ("True":s) = True
isBool ("False":s) = True
isBool _ = False

tokenize :: String -> Maybe [Token]
tokenize s = if skipWhiteSpace s == "" then
               Just []
             else
               case tokenNext (skipWhiteSpace s) of
                 Just (token, rest) ->
                      case tokenize rest of
                        Nothing -> Nothing
                        Just tokenList -> Just (token : tokenList)
                 Nothing -> Nothing


{- Parsare -}
parseFactor :: [Token] -> Maybe (Exp, [Token])
parseTerm :: [Token] -> Maybe (Exp, [Token])
parseExp :: [Token] -> Maybe (Exp, [Token])
parseBExp :: [Token] -> Maybe (BExp, [Token])

parseTerm te = case parseFactor te of
                 Just (el, trest) ->
                   case trest of
                     (TProdus:ter) -> case parseTerm ter of
                                       Nothing -> Just (el, TProdus:ter)
                                       Just (er, tl) -> Just ((Produs el er), tl)
                     []          -> Just (el, [])
                     l           -> Just (el, l)
                 Nothing -> Nothing

parseExp te = case parseTerm te of
                 Just (el, trest) ->
                   case trest of
                     (TSuma:ter) -> case parseExp ter of
                                       Nothing -> Just (el, TSuma:ter)
                                       Just (er, tl) -> Just ((Suma el er), tl)
                     (TMinus:ter) -> case parseExp ter of
                                       Nothing -> Just (el, TMinus:ter)
                                       Just (er, tl) -> Just ((Minus el er), tl)
                     []          -> Just (el, [])
                     l           -> Just (el, l)
                 Nothing -> Nothing

-- not, <, >, ==, <=, =>. 
parseBExp te = case parseTerm te of
                 Just (el, trest) ->
                   case trest of
                     (TSuma:ter) -> case parseBExp ter of
                                       Nothing -> Just (el, TSuma:ter)
                                       Just (er, tl) -> Just ((Suma el er), tl)
                     (TMinus:ter) -> case parseExp ter of
                                       Nothing -> Just (el, TMinus:ter)
                                       Just (er, tl) -> Just ((Minus el er), tl)
                     []          -> Just (el, [])
                     l           -> Just (el, l)
                 Nothing -> Nothing


parseFactor (TInt x:rest)           = Just (Numar (read x), rest)
parseFactor (TVar x:rest)           = Just (Var x, rest)
parseFactor (TParenLeft:rest)       = case parseExp rest of
                                        Just (e, TParenRight:rest') -> Just (e, rest')
                                        _                           -> Nothing
parseFactor (TBool x:rest)          = Just (Boolean (getBoolValue x), rest)
parseFactor _                       = Nothing

parseInstr :: [Token] -> Maybe (Instr, [Token]) 
parseInstr (TVar x:TAtrib:rest)  = case parseExp rest of
                                        Just (e, TSemicolon:rest') -> Just (Atrib x e, rest')
                                        _               -> Nothing
parseInstr _ = Nothing

parseProgram :: [Token] -> Maybe ([Instr], [Token])
parseProgram [] = Just ([], [])
parseProgram (TBraceLeft:s) = case parseProgram s of
                              Just (pgm, TBraceRight:rest) -> Just (pgm, rest)
                              _ -> Just ([], TBraceLeft:s)

parseProgram s = case parseInstr s of
                 Just (i, rest) -> case parseProgram rest of
                                   Just (is, rest') -> Just (i:is, rest')
                                   _                -> Nothing
                 _              -> Just ([], s)



parse :: String -> Maybe Program
parse s = case tokenize s of
            Nothing -> Nothing  
            Just tl -> case parseProgram tl of
                         Just (pgm, []) -> Just pgm 
                         _              -> Nothing




{- Interpretare -} 

data Exp = Var String
         | Numar Int
         | Suma Exp Exp
         | Minus Exp Exp
         | Produs Exp Exp
         deriving Show

-- true, false, not, <, >, ==, <=, =>. 
data BExp = BVar String
          | Boolean Bool
          | Not BExp
          | Lower BExp BExp
          | Greater BExp BExp
          | Equal BExp BExp
          | LowerEqual BExp BExp
          | GreaterEqual BExp BExp
          deriving Show

type ValuationPar = String -> Maybe Int

lift2 :: (a -> b -> c) -> Maybe a -> Maybe b -> Maybe c
lift2 f Nothing _ = Nothing
lift2 f _ Nothing = Nothing
lift2 f (Just x) (Just y) = Just (f x y)
sumaMaybe :: Maybe Int -> Maybe Int -> Maybe Int
sumaMaybe = lift2 (+)
difMaybe :: Maybe Int -> Maybe Int -> Maybe Int
difMaybe = lift2 (-)
produsMaybe :: Maybe Int -> Maybe Int -> Maybe Int
produsMaybe = lift2 (*)

evalp :: Exp -> ValuationPar -> Maybe Int
evalp (Numar x) _ = Just x
evalp (Var y) valp = valp y
evalp (Suma e1 e2) valp = sumaMaybe (evalp e1 valp) (evalp e2 valp)
evalp (Minus e1 e2) valp = difMaybe (evalp e1 valp) (evalp e2 valp)
evalp (Produs e1 e2) valp = produsMaybe (evalp e1 valp) (evalp e2 valp)




empty :: ValuationPar
empty _ = Nothing

update :: ValuationPar -> String -> Maybe Int -> ValuationPar
update f variabila valoare = \x -> if x == variabila then valoare else f x 

data Instr = Atrib String Exp
type Program = [Instr]


executaProgram :: ValuationPar -> Program -> Maybe ValuationPar
executaProgram valuatie [] = Just valuatie
executaProgram valuatie (i:is) = case executaInstr valuatie i of
                                     Nothing        -> Nothing
                                     Just valuatie' -> executaProgram valuatie' is

executaInstr :: ValuationPar -> Instr -> Maybe ValuationPar
executaInstr valuatie (Atrib x e) = Just (update valuatie x (evalp e valuatie))
evalProgram :: Program -> Maybe Int
evalProgram prog = case (executaProgram empty prog) of
                      Just valuatie -> valuatie "result"
                      Nothing       -> Nothing

interpret :: String -> Maybe Int
interpret pgmstring = case tokenize pgmstring of
                      Just tokens -> case parseProgram tokens of
                                     Just (pgm, []) -> evalProgram pgm
                                     _ -> Nothing
                      _ -> Nothing

main = do
     args <- getArgs
     contents <- readFile (head args)
     let result = interpret contents in
         case result of
         Just n -> putStrLn (show n)
         _ -> putStrLn "Invalid program"

{- 

Exercitiul 2

Scrieti cel putin 3 programe interesante si testati interpretorul.

-}
