package io

import scala.io.Source

object Reader {
  def from(file: String) = Source.fromURL(getClass.getResource(file)).getLines()
    .map(_.split("""\s+""").map(_.toInt))

  def main(args: Array[String]) {
    from("/kargerMinCut.txt") foreach { line =>
      println(line mkString ", ")
    }
  }
}
