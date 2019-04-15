{-# LANGUAGE TemplateHaskell #-}

module H7 where

import Test.QuickCheck
import Test.QuickCheck.All


data NestedList a = Elem a | List [NestedList a]
                    deriving (Show, Eq)


instance Arbitrary a => Arbitrary (NestedList a) where
  arbitrary = do
    n <- choose (1, 3) :: Gen Int
    case n of
        1 -> do x <- arbitrary
                return (Elem x)
        2 -> return (List [])
        3 -> do x <- arbitrary
                case x of
                    Elem _ -> return (List [x])
                    List xs -> do x' <- arbitrary
                                  return (List (x':xs))


flatten :: NestedList a -> [a]
flatten (Elem x) = [x]
flatten (List []) = []
flatten (List (x:xs)) = flatten x ++ flatten (List xs)


prop_flatten xs = flatten (List (map Elem $ flatten xs)) == flatten xs


return []
runTests = $quickCheckAll


main = do
    runTests
