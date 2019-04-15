module H17 where


split :: (Integral i) => [a] -> i -> ([a], [a])
split xs 0 = ([], xs)
split xs n = (as ++ [head bs], tail bs)
    where
        (as, bs) = split xs (n - 1)
