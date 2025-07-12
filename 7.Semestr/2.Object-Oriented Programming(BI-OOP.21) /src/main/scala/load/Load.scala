package load

trait Load[T] {
  def load(path: String): T
}