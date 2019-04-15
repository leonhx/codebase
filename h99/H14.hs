module H14 where


dupli :: [a] -> [a]
dupli [] = []
dupli (x:xs) = x:x:dupli xs
