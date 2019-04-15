module H27 where


combinations :: (Integral i) => i -> [a] -> [[a]]
combinations _ [] = []
combinations 1 xs = map (\x -> [x]) xs
combinations n (x:xs) = map (\c -> x:c) (combinations (n - 1) xs) ++
    combinations n xs


group :: (Integral i, Eq a) => [i] -> [a] -> [[[a]]]
group [_] xs = [[xs]]
group (n:ns) xs = let firstGroups = combinations n xs
                      others = map (\g -> filterElem g xs) firstGroups
                      otherGroups = map (\g -> group ns g) others
                      foPair = zip firstGroups otherGroups
                      gs = map (\(g, ogs) -> map (\og -> g:og) ogs) foPair
                  in
                    foldl (++) [] gs
    where
        filterElem as bs = filter (\b -> not $ elem b as) bs
