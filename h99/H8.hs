module H8 where


compressWith :: (Eq a) => [a] -> a -> [a]
compressWith [] _ = []
compressWith (x:xs) x' = if x == x' then compressWith xs x
                         else x : compressWith xs x


compress :: (Eq a) => [a] -> [a]
compress [] = []
compress (x:xs) = x : compressWith xs x
