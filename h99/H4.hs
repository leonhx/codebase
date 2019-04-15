{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All


myLength :: (Integral b) => [a] -> b
myLength [] = 0
myLength (_ : xs) = 1 + myLength xs


prop_myLength xs = myLength xs == length xs


main = $(quickCheckAll)
