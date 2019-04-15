module H34 where


myGCD :: (Integral i) => i -> i -> i
myGCD 0 y = y
myGCD x y
    | x < 0 = myGCD (-x) y
    | y < 0 = myGCD x (-y)
    | x > y = myGCD y x
    | otherwise = myGCD (y `mod` x) x


coprime :: (Integral i) => i -> i -> Bool
coprime a b = myGCD a b == 1


totient :: (Integral i) => i -> i
totient 1 = 1
totient n = fromIntegral $ length $ filter (coprime n) [1..n]
