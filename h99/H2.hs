{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All


myButLast :: [a] -> a
myButLast [] = error "cannot apply myLast on empty list"
myButLast [_] = error "cannot apply myLast on empty list"
myButLast [x, _] = x
myButLast (_ : xs) = myButLast xs


prop_myLast xs = length xs >= 2 ==> myButLast xs == xs !! (length xs - 2)


return []
runTests = $quickCheckAll


main = do
    runTests

