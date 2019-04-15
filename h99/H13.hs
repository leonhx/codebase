module H13 where


data Dup a = Multiple Int a | Single a deriving (Show)


dup :: a -> Int -> Dup a
dup x 1 = Single x
dup x n = Multiple n x


encodeDirectWith :: (Eq a) => [a] -> a -> Int -> [Dup a]
encodeDirectWith [] x c = [dup x c]
encodeDirectWith (x':xs) x c
    | x' == x = encodeDirectWith xs x (c + 1)
    | otherwise = dup x c : encodeDirectWith xs x' 1


encodeDirect :: (Eq a) => [a] -> [Dup a]
encodeDirect [] = []
encodeDirect (x:xs) = encodeDirectWith xs x 1
