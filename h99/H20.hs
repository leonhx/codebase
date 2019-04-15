module H20 where


removeAt :: (Integral i) => i -> [a] -> (a, [a])
removeAt 1 (x:xs) = (x, xs)
removeAt n (x:xs) = (e, x:es)
    where
        (e, es) = removeAt (n - 1) xs
