{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All

myLast :: [a] -> a
myLast [] = error "cannot apply myLast on empty list"
myLast [x] = x
myLast (_:xs) = myLast xs


prop_myLast xs = not (null xs) ==> myLast xs == last xs


return []
runTests = $quickCheckAll


main = do
    runTests
