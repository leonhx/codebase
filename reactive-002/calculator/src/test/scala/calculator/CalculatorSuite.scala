package calculator

import org.scalatest.FunSuite

import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

import org.scalatest._

import TweetLength.MaxTweetLength

@RunWith(classOf[JUnitRunner])
class CalculatorSuite extends FunSuite with ShouldMatchers {

  /******************
   ** TWEET LENGTH **
   ******************/

  def tweetLength(text: String): Int =
    text.codePointCount(0, text.length)

  test("tweetRemainingCharsCount with a constant signal") {
    val result = TweetLength.tweetRemainingCharsCount(Var("hello world"))
    assert(result() == MaxTweetLength - tweetLength("hello world"))

    val tooLong = "foo" * 200
    val result2 = TweetLength.tweetRemainingCharsCount(Var(tooLong))
    assert(result2() == MaxTweetLength - tweetLength(tooLong))
  }

  test("tweetRemainingCharsCount with a supplementary char") {
    val result = TweetLength.tweetRemainingCharsCount(Var("foo blabla \uD83D\uDCA9 bar"))
    assert(result() == MaxTweetLength - tweetLength("foo blabla \uD83D\uDCA9 bar"))
  }


  test("colorForRemainingCharsCount with a constant signal") {
    val resultGreen1 = TweetLength.colorForRemainingCharsCount(Var(52))
    assert(resultGreen1() == "green")
    val resultGreen2 = TweetLength.colorForRemainingCharsCount(Var(15))
    assert(resultGreen2() == "green")

    val resultOrange1 = TweetLength.colorForRemainingCharsCount(Var(12))
    assert(resultOrange1() == "orange")
    val resultOrange2 = TweetLength.colorForRemainingCharsCount(Var(0))
    assert(resultOrange2() == "orange")

    val resultRed1 = TweetLength.colorForRemainingCharsCount(Var(-1))
    assert(resultRed1() == "red")
    val resultRed2 = TweetLength.colorForRemainingCharsCount(Var(-5))
    assert(resultRed2() == "red")
  }

  test("should solve cyclic computations") {
    var namedExpressions: Map[String, Signal[Expr]] = Map() + ("a" -> Signal(Ref("b")))
    namedExpressions = namedExpressions + ("b" -> Signal(Ref("a")))
    // detects cyclic variables with the eval method
    assert(java.lang.Double.isNaN(Calculator.eval(Ref("a"), namedExpressions)))
    assert(java.lang.Double.isNaN(Calculator.eval(Ref("b"), namedExpressions)))

    // detects cyclic variables with the computeValues method
    var exprSignals = Calculator.computeValues(namedExpressions)
    val signalA = exprSignals.getOrElse("a", Var(0.0))
    assert(java.lang.Double.isNaN(signalA()))
    val signalB = exprSignals.getOrElse("b", Var(0.0))
    assert(java.lang.Double.isNaN(signalB()))
  }

  test("cyclic"){
    val v1 = new Literal(3)
    val b = new Ref("b")
    val a = new Ref("a")
    val va: Signal[Expr] = Signal{new Plus(v1, b)}
    val v3 = new Literal(1)
    val vb: Signal[Expr] = Signal{new Plus(a, v3)}
    val m = Map(("a", va), ("b", vb))

    val c = Calculator.computeValues(m)
    assert(java.lang.Double.isNaN(c("a").apply()))
  }

  test("cyclic2") {
    val input: Map[String, Signal[Expr]] = Map(
      "a" -> Signal { Plus(Literal(3), Ref("b")) },
      "b" -> Signal { Plus(Ref("a"), Literal(1)) })

    val results = Calculator.computeValues(input)

    for ((k,result) <- results.mapValues(x => x()))
      assert(result.isNaN())
  }

  test("cyclic3"){
    val v1 = new Literal(3)
    val b = new Ref("b")
    val a = new Ref("a")
    val va: Signal[Expr] = Signal{new Plus(v1, b)}
    val v3 = new Literal(1)
    val vb: Signal[Expr] = Signal{new Plus(a, v3)}
    val m = Map(("a", va), ("b", vb))

    val c = Calculator.computeValues(m)
    assert(c("a").apply() equals Double.NaN)
  }

  test("a = a") {
    val a: Expr = Ref("a")
    val map = Map("a" -> Signal {
      a
    })

    val ret = Calculator.computeValues(map)
    assert(ret.get("a").get().isNaN)
  }
}
