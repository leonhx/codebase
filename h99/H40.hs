module H40 where


primes :: (Integral i) => [i]
primes = sieve [2..]
    where
        sieve (p:ps) = p : sieve [p' | p' <- ps, p' `mod` p /= 0]


primesN n = takeWhile (< n) primes


goldbach :: (Integral i) => i -> (i, i)
goldbach n
    | n <= 2 || n `mod` 2 /= 0 = error "invalid parameter"
    | otherwise = findSum n (primesN n)
    where
        findSum n xs = head $ filter (\(x, y) -> x + y == n) (cross xs xs)
        cross [] _ = []
        cross [x] ys = map (\y -> (x,y)) ys
        cross (x:xs) ys = cross [x] ys ++ cross xs ys
