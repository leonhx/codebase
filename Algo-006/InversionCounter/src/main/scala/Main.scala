
import scala.io.Source

object Main extends App {
//  println(InversionCounter.count(Vector(1, 2, 3, 4, 5, 7, 6, 8, 9)))

  println(InversionCounter.count(Source.fromURI(getClass.getResource("/IntegerArray.txt").toURI).getLines().map(_.toInt).toVector))

}
