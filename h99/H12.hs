module H12 where


data Dup a = Multiple Int a | Single a deriving (Show)


decodeModified :: (Eq a) => [Dup a] -> [a]
decodeModified [] = []
decodeModified (Single x : as) = x : decodeModified as
decodeModified (Multiple n x : as) = take n (repeat x) ++ decodeModified as
