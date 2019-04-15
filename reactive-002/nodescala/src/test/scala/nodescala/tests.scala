package nodescala

import nodescala.NodeScala._
import org.junit.runner.RunWith
import org.scalatest._
import org.scalatest.junit.JUnitRunner

import scala.async.Async.async
import scala.collection._
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent._
import scala.concurrent.duration._
import scala.language.postfixOps

@RunWith(classOf[JUnitRunner])
class NodeScalaSuite extends FunSuite {

  test("A Future should always be completed") {
    val always = Future.always(517)

    assert(Await.result(always, 0 nanos) == 517)
  }
  test("A Future should never be completed") {
    val never = Future.never[Int]

    try {
      Await.result(never, 1 second)
      assert(false)
    } catch {
      case t: TimeoutException => // ok!
    }
  }

  test("A delayed Future") {
    val p = Promise[String]()
    Future.delay(2 seconds) onSuccess {
      case _ => p.success("done")
    }
    val f = p.future
    try {
      Await.result(f, 1 second)
      assert(false)
    } catch {
      case t: TimeoutException => // ok!
    }
    assert(Await.result(f, 1.01 second) == "done")
  }

  test("Any Future should completed") {
    val never = Future.never[Int]
    val delayed = Future.delay(1 second) continueWith(_ => 12)

    assert(Await.result(Future.any(List(never, delayed)), 1.01 second) == 12)
  }

  test("CancellationTokenSource should allow stopping the computation") {
    val cts = CancellationTokenSource()
    val ct = cts.cancellationToken
    val p = Promise[String]()

    async {
      while (ct.nonCancelled) {
        // do work
      }

      p.success("done")
    }

    cts.unsubscribe()
    assert(Await.result(p.future, 1 second) == "done")
  }

  test("continueWith should wait for the first future to complete") {
    val delay = Future.delay(1 second)
    val always = (f: Future[Unit]) => 42

    try {
      Await.result(delay.continueWith(always), 500 millis)
      assert(false)
    }
    catch {
      case t: TimeoutException => // ok
    }
  }

  test("continueWith simple")
  {
    val fS = Future { 3 }
      .continueWith(fT => (Await.result(fT, 0.01 seconds) + 1).toString)

    assert(Await.result(fS, 0.1 seconds) equals "4")
  }

  test("Future.run can be cancelled") {
    val p = Promise[String]()
    val working = Future.run() { ct =>
      Future {
        while (ct.nonCancelled) {
          //
        }
        p.success("done")
      }
    }
    Future.delay(1 second) onSuccess {
      case _ => working.unsubscribe()
    }
    assert(Await.result(p.future, 1.01 second) == "done")
  }

  class DummyExchange(val request: Request) extends Exchange {
    @volatile var response = ""
    val loaded = Promise[String]()
    def write(s: String) {
      response += s
    }
    def close() {
      loaded.success(response)
    }
  }

  class DummyListener(val port: Int, val relativePath: String) extends NodeScala.Listener {
    self =>

    @volatile private var started = false
    var handler: Exchange => Unit = null

    def createContext(h: Exchange => Unit) = this.synchronized {
      assert(started, "is server started?")
      handler = h
    }

    def removeContext() = this.synchronized {
      assert(started, "is server started?")
      handler = null
    }

    def start() = self.synchronized {
      started = true
      new Subscription {
        def unsubscribe() = self.synchronized {
          started = false
        }
      }
    }

    def emit(req: Request) = {
      val exchange = new DummyExchange(req)
      if (handler != null) handler(exchange)
      exchange
    }
  }

  class DummyServer(val port: Int) extends NodeScala {
    self =>
    val listeners = mutable.Map[String, DummyListener]()

    def createListener(relativePath: String) = {
      val l = new DummyListener(port, relativePath)
      listeners(relativePath) = l
      l
    }

    def emit(relativePath: String, req: Request) = this.synchronized {
      val l = listeners(relativePath)
      l.emit(req)
    }
  }
  test("Server should serve requests") {
    val dummy = new DummyServer(8191)
    val dummySubscription = dummy.start("/testDir") {
      request => for (kv <- request.iterator) yield (kv + "\n").toString
    }

    // wait until server is really installed
    Thread.sleep(500)

    def test(req: Request) {
      val webpage = dummy.emit("/testDir", req)
      val content = Await.result(webpage.loaded.future, 1 second)
      val expected = (for (kv <- req.iterator) yield (kv + "\n").toString).mkString
      assert(content == expected, s"'$content' vs. '$expected'")
    }

    test(immutable.Map("StrangeRequest" -> List("Does it work?")))
    test(immutable.Map("StrangeRequest" -> List("It works!")))
    test(immutable.Map("WorksForThree" -> List("Always works. Trust me.")))

    dummySubscription.unsubscribe()
  }

}




