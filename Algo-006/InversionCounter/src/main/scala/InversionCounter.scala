
object InversionCounter {
  private def mergeAndCount[T <% Ordered[T]](arr1: Vector[T], arr2: Vector[T], res: Vector[T], c: Long): (Vector[T], Long) =
    if (arr1.isEmpty) (res ++ arr2, c)
    else if (arr2.isEmpty) (res ++ arr1, c)
    else if (arr1.head <= arr2.head) mergeAndCount(arr1.tail, arr2, res :+ arr1.head, c)
    else mergeAndCount(arr1, arr2.tail, res :+ arr2.head, c + arr1.length)

  private def sortAndCount[T <% Ordered[T]](arr: Vector[T]): (Vector[T], Long) =
    if (arr.length < 2) (arr, 0)
    else {
      val thresholdIndex = arr.length / 2
      val left = arr.take(thresholdIndex)
      val right = arr.drop(thresholdIndex)
      val (orderedLeft, c1) = sortAndCount(left)
      val (orderedRight, c2) = sortAndCount(right)
      val (orderedArr, c) = mergeAndCount(orderedLeft, orderedRight, Vector(), 0)
      (orderedArr, c1 + c2 + c)
    }

  def count[T <% Ordered[T]](arr: Vector[T]): Long = sortAndCount(arr)._2
}
