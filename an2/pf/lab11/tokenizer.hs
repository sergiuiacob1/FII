module Tokenizer where

import Data.Char

data Token = TInt String -- intregi
           | TSum -- +
           | TDifference -- -
           | TProduct -- *
           | TParenLeft -- (
           | TParenRight -- )
           | TVar String -- variabile
           | TAssignInt -- :=
           | TAssignBool -- :-
           | TSemicolon -- ;
           | TIf -- if
           | TThen -- then
           | TElse -- else
           | TWhile -- while
           | TBraceLeft -- {
           | TBraceRight -- }
           | TTrue -- true
           | TFalse -- false
           | TNot -- not
           | TLess -- <
           | TGreater -- >
           | TEq -- ==
           | TLessEq -- <=
           | TGreaterEq -- >=
           | TAnd -- and
           | TOr -- or
             deriving Show

skipWhiteSpace :: String -> String
skipWhiteSpace (' ':rs) = skipWhiteSpace rs
skipWhiteSpace ('\n':rs) = skipWhiteSpace rs
skipWhiteSpace ('/':rs) = case rs of
                          '/':rstail -> skipWhiteSpace (skipCommentLine rstail)
                          _ -> skipWhiteSpace ('/':rs)
skipWhiteSpace s = s

skipCommentLine :: String -> String
skipCommentLine [] = []
skipCommentLine ('\n':rs) = rs
skipCommentLine (a:rs) = skipCommentLine rs

getInteger :: String -> (String, String)
getInteger (c:cs) | isDigit c = let (cn, cr) = getInteger cs in (c : cn, cr)
getInteger (c:cs) = ("", c:cs)
getInteger [] = ("", "")

getString  :: String -> (String, String)
getString (c:cs) | isLetter c = let (cn, cr) = getString cs in (c : cn, cr)
getString (c:cs) = ("", c:cs)
getString [] = ("", "")

keyword :: String -> Maybe Token
keyword "while" = Just TWhile
keyword "if" = Just TIf
keyword "then" = Just TThen
keyword "else" = Just TElse
keyword "true" = Just TTrue
keyword "false" = Just TFalse
keyword "not" = Just TNot
keyword "and" = Just TAnd
keyword "or" = Just TOr
keyword _ = Nothing

tokenNext :: String -> Maybe (Token, String)
tokenNext s@(c:rs)
  | isDigit c = let (x, y) = getInteger s in Just (TInt x, y)
  | isLetter c = let (x, y) = getString  s in case keyword x of
                                                Just t -> Just (t, y)
                                                Nothing -> Just (TVar x, y)
  | c == '+' = Just (TSum, rs)
  | c == '-'  = Just (TDifference, rs)
  | c == '*' = Just (TProduct, rs)
  | c == '(' = Just (TParenLeft, rs)
  | c == ')' = Just (TParenRight, rs)
  | c == '{' = Just (TBraceLeft, rs)
  | c == '}' = Just (TBraceRight, rs)
  | c == ';' = Just (TSemicolon, rs)
  | c == ':' = case rs of
      ('=':rstail) -> Just (TAssignInt, rstail)
      ('-':rstail) -> Just (TAssignBool, rstail)
      _ -> Nothing
  | c == '=' = case rs of
                 ('=':rstail) -> Just (TEq, rstail)
                 _ -> Nothing
  | c == '<' = case rs of
                 ('=':rstail) -> Just (TLessEq, rstail)
                 _ -> Just (TLess, rs)
  | c == '>' = case rs of
                 ('=':rstail) -> Just (TGreaterEq, rstail)
                 _ -> Just (TGreater, rs)

tokenNext _      = Nothing
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
