module H10 where


import H9


encode :: (Eq a) => [a] -> [(Int, a)]
encode xs = map (\as -> (length as, head as)) (H9.pack xs)
