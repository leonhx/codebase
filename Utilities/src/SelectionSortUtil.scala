object SelectionSortUtil {

  def selection_sort_demo(input: List[Int], index: Int, ex_count: Int): List[Int] = {
    println("%d: %s".format(ex_count, input.mkString(" ")))
    if (index >= input.length)
      input
    else {
      val head = input.take(index)
      val tail = input.drop(index)
      val min = tail.min
      if (min == tail.head)
        selection_sort_demo(input, index + 1, ex_count)
      else
        selection_sort_demo(head ::: min :: tail.tail.map(x => if (x == min) tail.head else x), index + 1, ex_count + 1)
    }
  }

  def selection_sort_demo(input: List[Int]): List[Int] = selection_sort_demo(input, 0, 0)

  def main(args: Array[String]): Unit = {
    selection_sort_demo(PreprocessUtil.whiteSepStrToList("89 34 12 45 26 14 50 11 48 28", _.toInt))
  }

}