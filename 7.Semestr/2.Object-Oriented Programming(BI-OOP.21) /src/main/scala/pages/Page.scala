package pages

trait Page[T] {
  def display(): T
}