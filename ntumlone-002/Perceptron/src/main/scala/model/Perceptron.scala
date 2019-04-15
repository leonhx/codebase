package model

import util.Read

object Perceptron {
  def q15() = {
    val dataset = Read.fromFile("/hw1_15_train.dat")
    def iter(h: Hypothesis, i: Int, n: Int, no_error: Boolean): Int =
      if (n > 60) n
      else if (i == 0 && no_error && h.hasSeparated(dataset)) n
      else {
        val nextIndex = (i + 1) % dataset.length
        val instance = dataset(i)
        if (h.isCorrectOn(instance)) iter(h, nextIndex, n, i == 0 || no_error)
        else iter(h.update(instance), nextIndex, n + 1, false)
      }
    iter(Hypothesis(Vector.fill(dataset.head.x.length)(0.0)), 0, 0, true)
  }
}
