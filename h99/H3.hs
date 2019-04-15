{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All


elementAt :: (Integral b) => [a] -> b -> a
elementAt [] _ = error "cannot apply elementAt on empty list"
elementAt (x : _) 0 = x
elementAt (_ : xs) k = elementAt xs (k - 1)


prop_elementAt xs k = length xs > k && k >= 0 ==> elementAt xs k == xs !! k


return []
runTests = $quickCheckAll


main = do
    runTests
