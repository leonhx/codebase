
package object common {
  type Instance = (Vector[Double], Int)

  type DataSet = Vector[Instance]

  def sign(x: Double): Int = if (x > 0) 1 else -1
}
