package graph

import io.Reader

import scala.collection.mutable
import scala.util.Random

class AdjacentList[T] private () {
  private val graph = mutable.Map.empty[Vertex[T], mutable.ArrayBuffer[Vertex[T]]]
    .withDefaultValue(mutable.ArrayBuffer.empty[Vertex[T]])

  private def edges = graph.toVector flatMap { case (start, ends) =>
    ends.map(Edge(start, _))
  }

  private def vertices: Set[Vertex[T]] = graph.flatMap{ case (v, vs) => vs.toSet + v }.toSet

  def add(edge: Edge[T]) = {
    graph(edge.start) = graph(edge.start) :+ edge.end
    this
  }

  def contains(vertex: Vertex[T]) = vertices.contains(vertex)

  def contains(edge: Edge[T]) = graph.exists(p => p._1 == edge.start && p._2.contains(edge.end))

  def apply(vertex: Vertex[T]): Option[mutable.ArrayBuffer[Vertex[T]]] = if (!contains(vertex)) None
    else Some(graph(vertex))

  def contract(edge: Edge[T]) = {
    require(contains(edge))
    graph(edge.start) = graph(edge.start) ++ graph(edge.end)
    graph -= edge.end
    graph foreach { case (start, ends) =>
        graph(start) = ends map (v => if (v == edge.end) edge.start else v)
    }
    graph(edge.start) = graph(edge.start) filter (_ != edge.start)
  }

  def randomContract() = try {
    val selected = edges(Random.nextInt(edges.length))
    contract(selected)
  } catch {
    case e: IllegalArgumentException =>
      println(edges.length, vertices.size, graph)
      throw e
  }

  def numOfNodes = vertices.size

  def numOfEdges = edges.size
}

object AdjacentList {
  def empty[T] = new AdjacentList[T]

  def main(args: Array[String]) {
    var min = 100
    1 to 1000 foreach { _ =>
      val graph = AdjacentList.empty[Int]
      Reader.from("/kargerMinCut.txt") foreach { line =>
        val start = line.head
        line.tail foreach { end =>
          if (!graph.contains(Edge(end, start)))
            graph add Edge(start, end)
        }
      }

      while (graph.numOfNodes > 2)
        graph.randomContract()

      min = if (graph.numOfEdges < min) graph.numOfEdges else min
      println(graph.numOfEdges, min)
    }
  }
}