module H11 where


import H9


data Dup a = Multiple Int a | Single a deriving (Show)


encodeModified :: (Eq a) => [a] -> [Dup a]
encodeModified xs = map (\as -> if length as > 1
                                then Multiple (length as) (head as)
                                else Single (head as))
                        (H9.pack xs)
