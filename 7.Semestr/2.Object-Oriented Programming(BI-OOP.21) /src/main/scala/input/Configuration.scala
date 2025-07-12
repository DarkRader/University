package input

class Configuration {
  private var options: Map[String, List[String]] = Map()

  def addOption(key: String, value: String): Unit = {
    val existingValues = options.getOrElse(key, List())
    options = options.updated(key, existingValues :+ value)
  }

  def getOption(key: String): List[String] = {
    options.getOrElse(key, List())
  }

  def containsOption(key: String): Boolean = {
    options.contains(key)
  }
}