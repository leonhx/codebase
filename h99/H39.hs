module H39 where


primes :: (Integral i) => [i]
primes = sieve [2..]
    where
        sieve (p:ps) = p : sieve [p' | p' <- ps, p' `mod` p /= 0]


primesN n = takeWhile (< n) primes


primesR :: (Integral i) => i -> i -> [i]
primesR a b = dropWhile (< a) $ primesN b
