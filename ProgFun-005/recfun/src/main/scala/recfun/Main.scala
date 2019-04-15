package recfun
import common._

object Main {
  def main(args: Array[String]) {
    println("Pascal's Triangle")
    for (row <- 0 to 10) {
      for (col <- 0 to row)
        print(pascal(col, row) + " ")
      println()
    }
  }

  /**
   * Exercise 1
   */
  def pascal(c: Int, r: Int): Int = if (c == 0 || r == 0 || c == r) 1 else pascal(c - 1, r - 1) + pascal(c, r - 1)

  /**
   * Exercise 2
   */
  def balance(chars: List[Char]): Boolean = {
    def iter(chars: List[Char], parens: List[Char]): Boolean =
      if (chars.isEmpty) parens.isEmpty
      else if (chars.head != '(' && chars.head != ')') iter(chars.tail, parens)
      else if (parens.isEmpty) chars.head != ')' && iter(chars.tail, chars.head :: parens)
      else if (chars.head == parens.head) iter(chars.tail, chars.head :: parens)
      else iter(chars.tail, parens.tail)
    iter(chars, Nil)
  }

  /**
   * Exercise 3
   */
  def countChange(money: Int, coins: List[Int]): Int =
    if (money == 0) 1
    else if (coins.isEmpty) 0
    else if (money < coins.head) countChange(money, coins.tail)
    else countChange(money - coins.head, coins) + countChange(money, coins.tail)
}
