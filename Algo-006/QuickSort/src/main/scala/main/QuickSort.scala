package main

import java.security.InvalidParameterException

import io.Reader

object QuickSort {
  private def partition(arr: Vector[Int], pivot: Vector[Int] => Int) = {
    val p = pivot(arr)
    (arr.filter(_ < p), p, arr.filter(_ > p))
  }

  private def middle(arr: Vector[Int]) = arr((arr.length - 1) / 2)

  private def median(a: Int, b: Int, c: Int) =
    if (a <= b && b <= c) b
    else if (c <= b && b <= a) b
    else if (b <= a && a <= c) a
    else if (c <= a && a <= b) a
    else if (a <= c && c <= b) c
    else if (b <= c && c <= a) c
    else {
      throw new InvalidParameterException
    }

  private def medianPivot(arr: Vector[Int]) = median(arr.head, middle(arr), arr.last)

  def sort(arr: Vector[Int], pivot: Vector[Int] => Int): (Vector[Int], Int) =
    if (arr.length <= 1) (arr, 0)
    else {
      val (left, p, right) = partition(arr, pivot)
      val (leftArr, leftCount) = sort(left, pivot)
      val (rightArr, rightCount) = sort(right, pivot)
      (leftArr ++ (p +: rightArr), leftCount + rightCount + arr.length - 1)
    }

  def countCmpOn(arr: Vector[Int], pivot: Vector[Int] => Int = _.head): Int = sort(arr, pivot)._2

  def testOn(file: String) = {
    val arr = Reader.fromFile(file)
    (countCmpOn(arr, _.head), countCmpOn(arr, _.last), countCmpOn(arr, medianPivot))
  }

  def main(args: Array[String]) {
    println(testOn("/10.txt"))
    println(testOn("/100.txt"))
    println(testOn("/1000.txt"))
  }
}
