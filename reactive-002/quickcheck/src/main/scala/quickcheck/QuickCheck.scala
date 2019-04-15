package quickcheck

import org.scalacheck.Arbitrary._
import org.scalacheck.Gen._
import org.scalacheck.Prop._
import org.scalacheck._

abstract class QuickCheckHeap extends Properties("Heap") with IntHeap {

  property("min1") = forAll { a: Int =>
    val h = insert(a, empty)
    findMin(h) == a
  }

  property("gen1") = forAll { (h: H) =>
    val m = if (isEmpty(h)) 0 else findMin(h)
    findMin(insert(m, h)) == m
  }

  property("min is the smaller one") = forAll { (x1: A, x2: A) =>
    val h = insert(x1, insert(x2, empty))
    findMin(h) == (if (x1 < x2) x1 else x2)
  }

  property("empty") = forAll { x: A =>
    val h = insert(x, empty)
    isEmpty(deleteMin(h))
  }

  property("heapsort") = forAll { h: H =>
    def heapSort(h: H): List[A] =
      if (isEmpty(h)) Nil
      else findMin(h) :: heapSort(deleteMin(h))
    val sorted = heapSort(h)
    def checkOrder(a: A, arr: List[A]): Boolean = arr match {
      case x :: xs => a <= x && checkOrder(x, xs)
      case _ => true
    }
    checkOrder(sorted.head, sorted.tail)
  }

  property("meld") = forAll { (h1: H, h2: H) =>
    val h = meld(h1, h2)
    val mh = findMin(h)
    mh == findMin(h1) || mh == findMin(h2)
  }

  lazy val genHeap: Gen[H] = for {
    x <- arbitrary[A]
    h <- oneOf(const(empty), genHeap)
  } yield insert(x, h)

  implicit lazy val arbHeap: Arbitrary[H] = Arbitrary(genHeap)

}
