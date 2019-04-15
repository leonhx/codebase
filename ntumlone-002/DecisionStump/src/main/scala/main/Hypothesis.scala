package main

import common._
import io.Reader

class Hypothesis(s: Int, theta: Double) {
  require(s == 1 || s == -1)

  def apply(x: Double): Int = s * sign(x - theta)

  def errorOn(data: DataSet): Double =
    data.count { case (Vector(x), y) => this(x) != y } * 1.0 / data.size

  lazy val errorOut: Double =
    0.5 + 0.3 * s * (theta.abs - 1)

  override def toString: String = {
    val prefix = if (s == 1) "" else "-"
    if (theta < 0) "h(x) = %s sign(x + %f)" format (prefix, -theta)
    else if (theta == 0) "h(x) = %s sign(x)" format prefix
    else "h(x) = %s sign(x - %f)" format (prefix, theta)
  }
}

object Hypothesis {
  def apply(s: Int, theta: Double) = new Hypothesis(s, theta)

  def allOfDichotomies(data: DataSet): Vector[Hypothesis] = {
    val orderedXs = data.map(_._1.head).sorted
    orderedXs.init.zip(orderedXs.tail).map(p => (p._1 + p._2) / 2.0)
      .flatMap(theta => Vector(Hypothesis(-1, theta), Hypothesis(1, theta))) :+
      Hypothesis(1, -2) :+ Hypothesis(-1, -2)
  }

  def main(args: Array[String]) {
    val data = Reader.loadDataSet(10)
    data.sortBy(_._1.head) foreach { case (Vector(x), y) => println("%f, %d" format (x, y)) }
    println()
    Hypothesis.allOfDichotomies(data) foreach { h: Hypothesis =>
      println("%s => %f, %f" format (h, h.errorOn(data), h.errorOut))
    }
  }
}
