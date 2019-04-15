module H21 where


insertAt :: (Integral i) => a -> [a] -> i -> [a]
insertAt x' xs 1 = x':xs
insertAt x' (x:xs) n = x : insertAt x' xs (n - 1)
