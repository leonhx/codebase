package main

import common._
import io.Reader

object DecisionStump {
  def fit1D(data: DataSet): (Hypothesis, Double, Double) = Hypothesis.allOfDichotomies(data).par
    .map(h => (h, h.errorOn(data), h.errorOut)).minBy(_._2)

  def fitMD(data: DataSet): (Hypothesis, Double, Int) = (0 until data.head._1.length)
    .map(i => (i, fit1D(data.map(ins => (Vector(ins._1(i)), ins._2)))))
    .map(i => (i._2._1, i._2._2, i._1)).minBy(_._2)

  def main(args: Array[String]) {
    //    val N = 5000
    //    println((1 to N).par.map{_: Int => fit1D(Reader.loadDataSet(20))._2}.sum / N)
    val (h, ein, i) = fitMD(Reader.loadDataSet("/hw2_train.dat"))
    println(h)
    println(ein)
    println(h.errorOn(Reader.loadDataSet("/hw2_test.dat").map(ins => (Vector(ins._1(i)), ins._2))))
  }
}
