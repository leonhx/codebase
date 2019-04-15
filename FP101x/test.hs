module Test where


import Data.Char

let2int c
  | isLower c = ord c - ord 'a'
  | otherwise = ord c - ord 'A'


int2letL n = chr (ord 'a' + n)

int2letU n = chr (ord 'A' + n)


shift n c
  | isLower c = int2letL ((let2int c + n) `mod` 26)
  | isUpper c = int2letU ((let2int c + n) `mod` 26)
  | otherwise = c

encode n xs = [shift n c | c <- xs]

data Tree a = Leaf a | Node (Tree a) (Tree a)

tree :: Tree Char
tree =  Node (Node (Leaf 'a') (Leaf 'b')) (Leaf 'c')


type State = Int
data ST a = S (State -> (a, State))

apply        :: ST a -> State -> (a, State)
apply (S f) x = f x


instance Monad ST where
    -- return :: a -> ST a
    return x   = S (\s -> (x,s))

    -- (>>=)  :: ST a -> (a -> ST b) -> ST b
    st >>= f   = S (\s -> let (x,s') = apply st s in apply (f x) s')

fresh :: ST Int
fresh =  S (\n -> (n, n+1))

mlabel           :: Tree a -> ST (Tree (a,Int))
mlabel (Leaf x)   =  do n <- fresh
                        return (Leaf (x,n))
mlabel (Node l r) =  do l' <- mlabel l
                        r' <- mlabel r
                        return (Node l' r')

label  :: Tree a -> Tree (a,Int)
label t = fst (apply (mlabel t) 0)

