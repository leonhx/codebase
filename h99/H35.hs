module H35 where


isPrime :: (Integral i) => i -> Bool
isPrime 1 = False
isPrime n = all (\x -> n `mod` x /= 0) [2..floor $ sqrt $ fromIntegral n]


primeFactors :: (Integral i) => i -> [i]
primeFactors n
    | isPrime n = [n]
    | otherwise = let f = head $ filter (\n' -> and [isPrime n', n `mod` n' == 0]) [2..n]
                  in
                      f : (primeFactors $ n `div` f)
