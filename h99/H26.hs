module H26 where


combinations :: (Integral i) => i -> [a] -> [[a]]
combinations _ [] = []
combinations 1 xs = map (\x -> [x]) xs
combinations n (x:xs) = map (\c -> x:c) (combinations (n - 1) xs) ++
    combinations n xs
