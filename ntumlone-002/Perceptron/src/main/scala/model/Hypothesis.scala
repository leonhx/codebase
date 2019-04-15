package model

import common._
import util.Linalg

class Hypothesis private(w: Vector[Double]) {
  def hasSeparated(dataset: Dataset) = dataset forall {
    isCorrectOn(_)
  }

  def isCorrectOn(i: Instance) = apply(i.x) == i.y

  def apply(x: Vector[Double]): Int = Hypothesis.sign(Linalg.dot(w, x))

  def update(i: Instance) = {
    require(!isCorrectOn(i))
    Hypothesis(Linalg.add(w, Linalg.scale(i.x, i.y)))
  }

  override def toString = w.mkString("Hypothesis(", ", ", ")")
}

object Hypothesis {
  def apply(w: Vector[Double]) = new Hypothesis(w)

  private def sign(x: Double) = if (x > 0) 1 else -1
}
