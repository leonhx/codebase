{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All


elementAt :: (Integral b) => [a] -> b -> a
elementAt [] _ = error "cannot apply elementAt on empty list"
elementAt (x : _) 0 = x
elementAt (_ : xs) k = elementAt xs (k - 1)


prop_elementAt xs k = elementAt xs k == xs !! k


main = $(quickCheckAll)
