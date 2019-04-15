module H18 where


import H17


slice :: (Integral i) => [a] -> i -> i -> [a]
slice xs m n = snd $ split (fst (H17.split xs n)) (m - 1)
