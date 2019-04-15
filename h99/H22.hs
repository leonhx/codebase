module H22 where


range :: (Integral i) => i -> i -> [i]
range x y
    | x > y = []
    | otherwise = x : range (x + 1) y
