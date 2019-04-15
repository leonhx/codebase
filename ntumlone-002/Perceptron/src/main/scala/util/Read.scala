package util

import common._
import model.Instance

import scala.io.Source

object Read {
  def fromFile(file: String): Dataset = {
    Source.fromURL(getClass.getResource(file)).getLines().map { l =>
      val row = l.split( """\s+""")
      Instance(1.0 +: row.init.map(_.toDouble).toVector, row.last.toInt)
    }.toVector
  }
}
