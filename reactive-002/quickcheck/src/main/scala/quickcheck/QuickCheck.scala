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

  property("heapsort") = forAll { xs: List[Int] =>
    def genH(xs: List[A], h: H): H = xs match {
      case Nil => h
      case x :: xs_ => genH(xs_, insert(x, h))
    }
    val h = genH(xs, empty)
    def heapSort(h: H): List[A] =
      if (isEmpty(h)) Nil
      else findMin(h) :: heapSort(deleteMin(h))
    val heapSorted = heapSort(h)
    val stdSorted = xs.sorted
    heapSorted.zip(stdSorted).forall{case (x1, x2) => x1 == x2}
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
