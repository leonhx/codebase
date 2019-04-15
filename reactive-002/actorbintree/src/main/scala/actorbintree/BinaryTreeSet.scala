/**
 * Copyright (C) 2009-2013 Typesafe Inc. <http://www.typesafe.com>
 */
package actorbintree

import akka.actor._

import scala.collection.immutable.Queue

object BinaryTreeSet {

  trait Operation {
    def requester: ActorRef
    def id: Int
    def elem: Int
  }

  trait OperationReply {
    def id: Int
  }

  /** Request with identifier `id` to insert an element `elem` into the tree.
    * The actor at reference `requester` should be notified when this operation
    * is completed.
    */
  case class Insert(requester: ActorRef, id: Int, elem: Int) extends Operation

  /** Request with identifier `id` to check whether an element `elem` is present
    * in the tree. The actor at reference `requester` should be notified when
    * this operation is completed.
    */
  case class Contains(requester: ActorRef, id: Int, elem: Int) extends Operation

  /** Request with identifier `id` to remove the element `elem` from the tree.
    * The actor at reference `requester` should be notified when this operation
    * is completed.
    */
  case class Remove(requester: ActorRef, id: Int, elem: Int) extends Operation

  /** Request to perform garbage collection*/
  case object GC

  /** Holds the answer to the Contains request with identifier `id`.
    * `result` is true if and only if the element is present in the tree.
    */
  case class ContainsResult(id: Int, result: Boolean) extends OperationReply
  
  /** Message to signal successful completion of an insert or remove operation. */
  case class OperationFinished(id: Int) extends OperationReply

}


class BinaryTreeSet extends Actor {
  import BinaryTreeSet._
  import BinaryTreeNode._

  def createRoot: ActorRef = context.actorOf(BinaryTreeNode.props(0, initiallyRemoved = true))

  var root = createRoot

  // optional
  var pendingQueue = Queue.empty[Operation]

  // optional
  def receive = normal

  // optional
  /** Accepts `Operation` and `GC` messages. */
  val normal: Receive = {
    case op: Operation => root ! op

    case GC =>
      val newRoot = createRoot
      context.become(garbageCollecting(newRoot))
      root ! CopyTo(newRoot)
  }

  // optional
  /** Handles messages while garbage collection is performed.
    * `newRoot` is the root of the new binary tree where we want to copy
    * all non-removed elements into.
    */
  def garbageCollecting(newRoot: ActorRef): Receive = {
    case op: Operation => pendingQueue = pendingQueue.enqueue(op)

    case CopyFinished =>
      root = newRoot
      while (pendingQueue.nonEmpty) {
        val result = pendingQueue.dequeue
        root ! result._1
        pendingQueue = result._2
      }
      context.become(normal)

    case GC => // do nothing
  }

}

object BinaryTreeNode {
  trait Position

  case object Left extends Position
  case object Right extends Position

  case class CopyTo(treeNode: ActorRef)
  case object CopyFinished

  def props(elem: Int, initiallyRemoved: Boolean) = Props(classOf[BinaryTreeNode],  elem, initiallyRemoved)
}

class BinaryTreeNode(val elem: Int, initiallyRemoved: Boolean) extends Actor {
  import BinaryTreeNode._
  import BinaryTreeSet._

  var subtrees = Map[Position, ActorRef]()
  var removed = initiallyRemoved

  // optional
  def receive = normal

  // optional
  /** Handles `Operation` messages and `CopyTo` requests. */
  val normal: Receive = {
    case insert @ Insert(requester, id, e) =>
      if (e == elem) {
        if (removed) removed = false
        requester ! OperationFinished(id)
      } else if (e < elem) {
        if (subtrees.contains(Left)) subtrees(Left) ! insert
        else {
          subtrees += Left -> context.actorOf(props(e, initiallyRemoved = false))
          requester ! OperationFinished(id)
        }
      } else {
        if (subtrees.contains(Right)) subtrees(Right) ! insert
        else {
          subtrees += Right -> context.actorOf(props(e, initiallyRemoved = false))
          requester ! OperationFinished(id)
        }
      }

    case contains @ Contains(requester, id, e) =>
      if (e == elem) requester ! ContainsResult(id, result = !removed)
      else if (e < elem) {
        if (subtrees.contains(Left)) subtrees(Left) ! contains
        else requester ! ContainsResult(id, result = false)
      } else {
        if (subtrees.contains(Right)) subtrees(Right) ! contains
        else requester ! ContainsResult(id, result = false)
      }

    case remove @ Remove(requester, id, e) =>
      if (e == elem) {
        removed = true
        requester ! OperationFinished(id)
      } else if (e < elem) {
        if (subtrees.contains(Left)) subtrees(Left) ! remove
        else requester ! OperationFinished(id)
      } else {
        if (subtrees.contains(Right)) subtrees(Right) ! remove
        else requester ! OperationFinished(id)
      }

    case copy @ CopyTo(newRoot) =>
      if (!removed) newRoot ! Insert(self, -1, elem)
      var expected = Set[ActorRef]()
      if (subtrees.contains(Left)) expected += subtrees(Left)
      if (subtrees.contains(Right)) expected += subtrees(Right)
      context.become(copying(expected, sender(), insertConfirmed = false))
      expected foreach { _ ! copy }
  }

  // optional
  /** `expected` is the set of ActorRefs whose replies we are waiting for,
    * `insertConfirmed` tracks whether the copy of this node to the new tree has been confirmed.
    */
  def copying(expected: Set[ActorRef], confirmTo: ActorRef, insertConfirmed: Boolean): Receive = {
    if (insertConfirmed) {
      self ! PoisonPill
      normal
    } else if (expected.isEmpty) {
      confirmTo ! CopyFinished
      copying(expected, confirmTo, insertConfirmed = true)
    } else {
      case CopyFinished => context.become(copying(expected - sender(), confirmTo, insertConfirmed))
    }
  }
}
