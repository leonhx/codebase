import scala.collection.immutable.Stack

object StackUtil {

  def validate[T](input: List[T], pushOrder: List[T], stack: Stack[T]): Boolean =
    input match {
      case Nil => stack.isEmpty && pushOrder.isEmpty
      case x :: remaining =>
        if (!stack.isEmpty && stack.head == x)
          validate(remaining, pushOrder, stack.pop)
        else pushOrder match {
          case y::order => validate(input, order, stack.push(y))
          case _ => false
        }
    }

  def validate[T <% Ordered[T]](input: List[T]): Boolean =
    validate(input, input.sortWith(_ < _), Stack())
    
  def validate(input: String): Boolean =
    validate(PreprocessUtil.whiteSepStrToList(input, _.toInt))

  def main(args: Array[String]): Unit = {
    println(validate("2 1 4 6 5 7 8 9 3 0"))
  }

}