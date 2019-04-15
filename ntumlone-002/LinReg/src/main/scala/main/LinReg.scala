package main

import breeze.linalg.{DenseVector, DenseMatrix}
import common.DataSet

object LinReg {
  def fit(dataSet: DataSet): LinearFunction = {
    val N = dataSet.length
    val dim = dataSet.head._1.length

    val X = DenseMatrix.zeros[Double](N, dim + 1)
    val Y = DenseVector.zeros[Int](N)

    dataSet.zipWithIndex foreach { case ((x, y), i) =>
        X(i, ::) := DenseVector((1.0 +: x).toArray).t
        Y(i) = y
    }

    LinearFunction(X \ Y)
  }

  def main(args: Array[String]) {
    val l = fit(Vector((Vector(0), 0),
                        (Vector(1), 1)))
    println(l.w)
  }
}
