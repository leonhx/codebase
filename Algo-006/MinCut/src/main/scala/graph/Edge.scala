package graph

case class Edge[T](start: Vertex[T], end: Vertex[T])

object Edge {
  def apply[T](start: T, end: T): Edge[T] = Edge(Vertex(start), Vertex(end))
}
