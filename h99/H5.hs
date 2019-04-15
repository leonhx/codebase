{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All


myReverse :: [a] -> [a]
myReverse xs = foldl (\s e -> e:s) [] xs


prop_myReverse xs = myReverse (myReverse xs) == xs

prop_myReverse_2 xs = let par = myReverse xs ++ xs
                      in myReverse par == par


return []
runTests = $quickCheckAll


main = do
    runTests
