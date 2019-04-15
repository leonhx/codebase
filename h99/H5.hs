{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All


myReverse :: [a] -> [a]
myReverse xs = foldl (\s e -> e:s) [] xs


prop_myReverse xs = myReverse xs == reverse xs


main = $(quickCheckAll)
