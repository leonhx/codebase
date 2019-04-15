object PreprocessUtil {
  def whiteSepStrToList[T](str: String, fn: String => T) =
    str.split("""\s+""").map(fn).toList
}