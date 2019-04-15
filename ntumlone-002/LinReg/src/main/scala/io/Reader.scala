package io

import common._

import scala.util.Random

object Reader {
  private val rand = new Random

  private def flip(instance: Instance) = (instance._1, -instance._2)

  private def f(x1: Double, x2: Double): Int = sign(x1 * x1 + x2 * x2  - 0.6)

  private def getInstance(x1: Double, x2: Double) = ((x1, x2), f(x1, x2))

  private def randomInstance: Instance = getInstance(rand.nextDouble() * 2 - 1, rand.nextDouble() * 2 - 1)

  def loadDataSet(size: Int): DataSet =
    Random.shuffle(for (i <- 0 until size) yield if (i < size / 10) flip(randomInstance) else randomInstance).toVector

}
