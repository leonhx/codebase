package io

import common._

import scala.io.Source
import scala.util.Random

object Reader {
  private val rand = new Random

  private def flip(y: Int): Int = if (rand.nextDouble() < 0.8) y else -y

  private def f(x: Double): Int = flip(sign(x))

  private def getInstance(x: Double) = (Vector(x), f(x))

  private def randomInstance: Instance = getInstance(rand.nextDouble() * 2 - 1)

  def loadDataSet(size: Int): DataSet = (for (_ <- 1 to size) yield randomInstance).toVector

  def loadDataSet(file: String): DataSet = Source.fromURL(getClass.getResource(file)).getLines().map { l =>
    val row = l.trim.split("""\s+""")
    (row.init.map(_.toDouble).toVector, row.last.toInt)
  }.toVector

  def main (args: Array[String]): Unit = {
    val N = 1000000
    val ys = loadDataSet(N)
    // about 80% of the instances have the same sign of x and y
    println(ys.par.count(ins => ins._1.head * ins._2 > 0) * 1.0 / N)

    loadDataSet("/hw2_train.dat") foreach { i =>
      println(i)
    }
  }
}
