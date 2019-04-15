module P1 where


solve :: (Integral i) => i -> i
solve n = sum $ takeWhile (< n) $ filter (\x -> x `mod` 3 == 0 || x `mod` 5 == 0) [1..]
