module H19 where


import H17


rotate :: (Integral i) => [a] -> i -> [a]
rotate xs n = bs ++ as
    where
        (as, bs) = H17.split xs (if n >= 0 then n else fromIntegral (length xs) + n)
