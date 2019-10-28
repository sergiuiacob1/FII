getExpBinOp :: Token -> Maybe (Exp -> Exp -> BExp)
getExpBinOp token = case token of
                         TLess      -> Just Less -- <
                         TGreater   -> Just Greater -- >
                         TEq        -> Just Equal -- ==
                         TLessEq    -> Just LessEq -- <=
                         TGreaterEq -> Just GreaterEq -- >=

parseBExp (TTrue:rest)      = Just (TrueExp,  rest)
parseBExp (TFalse:rest)     = Just (FalseExp, rest)
parseBExp (TNot:rest)       = case (parseBExp rest) of
                                   Just (b, rest') -> Just (Not b,   rest')
                                   _ -> Nothing
parseBExp (TParenLeft:rest) = case (parseBExp rest) of
                                   Just (b, TParenRight:rest') -> Just (b, rest')
                                   _ -> Nothing
parseBExp tokens            = case (parseExp tokens) of
                                   Just (e, bin_op:rest') -> case getExpBinOp bin_op of
                                                                  Just bexp_op -> case (parseExp rest') of
                                                                                    Just (e', rest'') -> Just ((bexp_op e e'), rest'')
                                                                                    _ -> Nothing
                                                                  _ -> Nothing
                                   _ -> Nothing
