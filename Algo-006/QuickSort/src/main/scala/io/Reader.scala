package io

import scala.io.Source

object Reader {
  def fromFile(file: String): Vector[Int] = Source.fromURL(getClass.getResource(file)).getLines().map(_.toInt).toVector

  def main(args: Array[String]) {
    val arr = fromFile("/QuickSort.txt")
    println(arr.length)
  }
}
