module H28 where


sort :: (Ord b) => (a -> b) -> [a] -> [a]
sort _ [] = []
sort func xs = let k = func $ head xs
                   as = [x' | x' <- xs, func x' < k]
                   bs = [x' | x' <- xs, func x' == k]
                   cs = [x' | x' <- xs, func x' > k]
               in
                   sort func as ++ bs ++ sort func cs


lsort :: [[a]] -> [[a]]
lsort xs = sort length xs


lfsort :: (Ord a) => [[a]] -> [[a]]
lfsort xs = let lengths = sort id $ map length xs
                lf = freq lengths
            in
                sort (\x -> search lf (length x)) xs
    where
        freq' [] x n = [(x, n)]
        freq' (x':xs) x n
            | x' == x = freq' xs x (n + 1)
            | otherwise = (x, n) : (freq' xs x' 1)
        freq [] = []
        freq (x:xs) = freq' xs x 1
        search ((k', w):kws) k
            | k' == k = w
            | otherwise = search kws k
