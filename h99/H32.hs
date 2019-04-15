module H32 where


myGCD :: (Integral i) => i -> i -> i
myGCD 0 y = y
myGCD x y
    | x < 0 = myGCD (-x) y
    | y < 0 = myGCD x (-y)
    | x > y = myGCD y x
    | otherwise = myGCD (y `mod` x) x
