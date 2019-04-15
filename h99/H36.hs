module H36 where


isPrime :: (Integral i) => i -> Bool
isPrime 1 = False
isPrime n = all (\x -> n `mod` x /= 0) [2..floor $ sqrt $ fromIntegral n]


primeFactors :: (Integral i) => i -> [i]
primeFactors n
    | isPrime n = [n]
    | otherwise = let f = head $ filter (\n' -> and [isPrime n', n `mod` n' == 0]) [2..n]
                  in
                      f : (primeFactors $ n `div` f)


prime_factors_mult :: (Integral i) => i -> [(i, i)]
prime_factors_mult n = groupIt $ primeFactors n
    where
        groupIt' n x [] = [(x, n)]
        groupIt' n x (x':xs)
            | x == x' = groupIt' (n+1) x xs
            | otherwise = (x, n) : groupIt' 1 x' xs
        groupIt [] = []
        groupIt (x:xs) = groupIt' 1 x xs
