module Expressions where

data AExp =
    AVar String
  | Number Int
  | Sum AExp AExp
  | Difference AExp AExp
  | Product AExp AExp
  deriving Show

data BExp =
    BVar String
  | TrueExp
  | FalseExp
  | Not BExp
  | Equal AExp AExp
  | Less AExp AExp
  | Greater AExp AExp
  | LessEq AExp AExp
  | GreaterEq AExp AExp
  | And BExp BExp
  | Or BExp BExp
  deriving Show

data Value =
    IntValue Int
  | BoolValue Bool

type ValuationPar = String -> Maybe Value

data Instruction =
    AssignAExp String AExp
  | AssignBExp String BExp
  | Cond BExp Program Program
  | Loop BExp Program
  deriving Show

type Program = [Instruction]

{- helper functions -}
lift2 :: (a -> b -> c) -> Maybe a -> Maybe b -> Maybe c
lift2 f Nothing _ = Nothing
lift2 f _ Nothing = Nothing
lift2 f (Just x) (Just y) = Just (f x y)

addMaybe :: Maybe Int -> Maybe Int -> Maybe Int
addMaybe = lift2 (+)

subtractMaybe :: Maybe Int -> Maybe Int -> Maybe Int
subtractMaybe = lift2 (-)

multiplyMaybe :: Maybe Int -> Maybe Int -> Maybe Int
multiplyMaybe = lift2 (*)

{- evaluation functions -}
evalAExp :: AExp -> ValuationPar -> Maybe Int
evalAExp (Number x) _ = Just x
evalAExp (AVar y) valp = case valp y of
  Just (IntValue i) -> Just i
  Just (BoolValue _) -> Nothing
  Nothing -> Nothing
evalAExp (Sum e1 e2) valp = addMaybe (evalAExp e1 valp) (evalAExp e2 valp)
evalAExp (Difference e1 e2) valp = subtractMaybe (evalAExp e1 valp) (evalAExp e2 valp)
evalAExp (Product e1 e2) valp = multiplyMaybe (evalAExp e1 valp) (evalAExp e2 valp)

evalBExp :: BExp -> ValuationPar -> Maybe Bool
evalBExp (BVar y) valp = case valp y of
                          Just (BoolValue i) -> Just i
                          Just (IntValue _) -> Nothing
evalBExp TrueExp _  = Just True
evalBExp FalseExp _ = Just False
evalBExp (Not b) valp = case evalBExp b valp of
  Just bl -> Just (not bl)
  _ -> Nothing
evalBExp (Equal e1 e2)     valp = (lift2 (==)) (evalAExp e1 valp) (evalAExp e2 valp)
evalBExp (Less  e1 e2)     valp = (lift2 (<))  (evalAExp e1 valp) (evalAExp e2 valp)
evalBExp (Greater e1 e2)   valp = (lift2 (>))  (evalAExp e1 valp) (evalAExp e2 valp)
evalBExp (LessEq e1 e2)    valp = (lift2 (<=)) (evalAExp e1 valp) (evalAExp e2 valp)
evalBExp (GreaterEq e1 e2) valp = (lift2 (>=)) (evalAExp e1 valp) (evalAExp e2 valp)
evalBExp (And e1 e2)       valp = ((lift2 (&&)) (evalBExp e1 valp) (evalBExp e2 valp))
evalBExp (Or e1 e2)        valp = ((lift2 (||)) (evalBExp e1 valp) (evalBExp e2 valp))
-- evalBExp (And e1 e2)       valp = case (evalBExp e1 valp) of
--                                     Just b1Val -> case (evalBExp e2 valp) of
--                                                   Just b2Val -> Just ((lift2 (&&)) b1Val b2Val)
--                                                   _ -> Nothing
--                                     _ -> Nothing
-- evalBExp (Or e1 e2)        valp = case (evalBExp e1 valp) of
--                                     Just b1Val -> case (evalBExp e2 valp) of
--                                                   Just b2Val -> Just ((lift2 (||)) b1Val b2Val)
--                                                   _ -> Nothing
--                                     _ -> Nothing

empty :: ValuationPar
empty _ = Nothing

update :: ValuationPar -> String -> Maybe Value -> ValuationPar
update f var value = \x -> if x == var then value else f x 

executeProgram :: ValuationPar -> Program -> Maybe ValuationPar
executeProgram valuation [] = Just valuation
executeProgram valuation (i:is) = case executeInstruction valuation i of
  Nothing -> Nothing
  Just valuation' -> executeProgram valuation' is

executeInstruction :: ValuationPar -> Instruction -> Maybe ValuationPar
executeInstruction valuation (AssignAExp x e) =
  case evalAExp e valuation of
    Nothing -> Nothing
    Just i -> Just (update valuation x (Just (IntValue i)))
executeInstruction valuation (AssignBExp x e) =
  case evalBExp e valuation of
    Nothing -> Nothing
    Just b -> Just (update valuation x (Just (BoolValue b)))
executeInstruction valuation (Cond be p1 p2) = case (evalBExp be valuation) of
  Just True -> executeProgram valuation p1
  Just False -> executeProgram valuation p2
  Nothing -> Nothing
executeInstruction valuation (Loop be p) = case (evalBExp be valuation) of
  Nothing -> Nothing
  Just False -> Just valuation
  Just True -> case (executeProgram valuation p) of
    Nothing -> Nothing
    Just valuation' -> executeInstruction valuation' (Loop be p)
