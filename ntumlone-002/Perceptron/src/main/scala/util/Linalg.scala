package util

object Linalg {
  def dot(x: Vector[Double], y: Vector[Double]): Double = x.zip(y).foldLeft(0.0) { case (acc, (a, b)) => acc + a * b }

  def add(x: Vector[Double], y: Vector[Double]) = x.zip(y).map { case (a, b) => a + b}

  def scale(x: Vector[Double], n: Double) = x.map(_ * n)
}
