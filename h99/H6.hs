{-# LANGUAGE TemplateHaskell #-}

module Main where

import Test.QuickCheck
import Test.QuickCheck.All


isPalindrome :: (Eq a) => [a] -> Bool
isPalindrome xs = reverse xs == xs


prop_isPalindrome xs = isPalindrome (xs ++ reverse xs) == True
prop_isNotPalindrome xs = reverse xs /= xs ==> isPalindrome xs == False


return []
runTests = $quickCheckAll


main = do
    runTests
