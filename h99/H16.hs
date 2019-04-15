module H16 where


dropEvery :: (Integral i) => [a] -> i -> [a]
dropEvery xs n = dropEvery' xs n
    where
        dropEvery' [] _ = []
        dropEvery' (_:es) 1 = dropEvery' es n
        dropEvery' (e:es) i = e : dropEvery' es (i - 1)
