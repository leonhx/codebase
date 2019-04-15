{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All


isPalindrome :: (Eq a) => [a] -> Bool
isPalindrome xs = reverse xs == xs


prop_isPalindrome xs = reverse xs == xs ==> isPalindrome xs == True
prop_isNotPalindrome xs = reverse xs /= xs ==> isPalindrome xs == False


main = $(quickCheckAll)
