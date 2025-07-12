package pages

trait TextPage extends Page[String] {
  def display(): String
}