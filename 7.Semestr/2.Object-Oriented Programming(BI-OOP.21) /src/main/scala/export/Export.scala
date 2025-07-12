package `export`

trait Export[T] {
  def show(image: T): Unit
}