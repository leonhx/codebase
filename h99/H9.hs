module H9
(pack
) where


packWith :: (Eq a) => [a] -> [a] -> [[a]]
packWith [] acc = [acc]
packWith (x:xs) [] = packWith xs [x]
packWith (x:xs) acc = if x == head acc then packWith xs (x:acc)
                      else acc : packWith xs [x]


pack :: (Eq a) => [a] -> [[a]]
pack [] = []
pack xs = packWith xs []
