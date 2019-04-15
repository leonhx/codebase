package recfun

import org.scalatest.FunSuite

import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

@RunWith(classOf[JUnitRunner])
class PascalSuite extends FunSuite {
  import Main.pascal
  test("pascal: col=0,row=0") {
    assert(pascal(0, 0) === 1)
  }

  test("pascal: col=0,row=2") {
    assert(pascal(0, 2) === 1)
  }

  test("pascal: col=1,row=2") {
    assert(pascal(1, 2) === 2)
  }

  test("pascal: col=1,row=3") {
    assert(pascal(1, 3) === 3)
  }

  test("pascal: col=0,row=122") {
    assert(pascal(0, 122) === 1)
  }

  test("pascal: col=122,row=122") {
    assert(pascal(122, 122) === 1)
  }

  test("pascal: recursive relationship") {
    assert(pascal(124, 156) === pascal(123, 155) + pascal(124,155))
  }
}
