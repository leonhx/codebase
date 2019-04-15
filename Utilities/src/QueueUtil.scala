import scala.collection.immutable.Queue

object QueueUtil {
  
  def validate[T](input: List[T], pushOrder: List[T], queue: Queue[T]): Boolean =
    input match {
      case Nil => queue.isEmpty && pushOrder.isEmpty
      case x :: remaining =>
        if (!queue.isEmpty && queue.head == x)
          validate(remaining, pushOrder, queue.dequeue._2)
        else pushOrder match {
          case y::order => validate(input, order, queue.enqueue(y))
          case _ => false
        }
    }

  def validate[T <% Ordered[T]](input: List[T]): Boolean =
    validate(input, input.sortWith(_ < _), Queue())
    
  def validate(input: String): Boolean =
    validate(PreprocessUtil.whiteSepStrToList(input, _.toInt))

  def main(args: Array[String]): Unit = {
    println(validate("0 1 2 3 4 5 6 7 8 9"))
  }

}