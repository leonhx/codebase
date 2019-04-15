module H31 where


isPrime :: (Integral i) => i -> Bool
isPrime 1 = False
isPrime n = all (\x -> n `mod` x /= 0) [2..floor $ sqrt $ fromIntegral n]
