module P2 where


fibs :: (Integral i) => [i]
fibs = 1 : 2 : next fibs
    where
        next (a : t@(b:_)) = (a+b) : next t


solve :: (Integral i) => i
solve = sum $ filter (\x -> x `mod` 2 == 0) $ takeWhile (< 4000000) fibs
