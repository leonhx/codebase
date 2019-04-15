package main

import breeze.linalg.DenseVector
import common._

case class LinearFunction(w: DenseVector[Double]) {
  def apply(x: DenseVector[Double]): Int = sign(w dot x)
}
