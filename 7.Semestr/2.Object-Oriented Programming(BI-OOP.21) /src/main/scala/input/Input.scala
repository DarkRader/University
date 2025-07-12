package input

import scala.annotation.tailrec

trait InputSource {
  def fetchImageConfig: Configuration
}

class CommandInput(args: Array[String]) extends InputSource {
  override def fetchImageConfig: Configuration = {
    val argsProcessor = new ArgumentsProcessor()

    if (args.count(_ == "--image") > 1) {
      throw new IllegalArgumentException("Duplicate image argument detected")
    }

    if (!args.contains("--image") && !args.contains("--image-random")) {
      throw new IllegalArgumentException("Image argument is missing")
    }

    val defaultArgs = Array("--table", "bourke")
    var adjustedArgs = args.clone()
    if (!args.contains("--table")) {
      adjustedArgs = args ++ defaultArgs.filterNot(arg => args.contains(arg))
    }

    val configuration = new Configuration()
    argsProcessor.processNext(configuration, adjustedArgs.toList)
  }
}

class WebInput(resourceUrl: String) extends InputSource {
  override def fetchImageConfig: Configuration = {
    val configuration = new Configuration()
    configuration
  }
}

class FileInputLoader(fileLocation: String) extends InputSource {
  override def fetchImageConfig: Configuration = {
    val configuration = new Configuration()
    configuration
  }
}

class ArgumentsProcessor() {
  private val parsersWithValues: Map[String, ArgsHandler] = Map(
    "--image" ->                new PictureHandler(),
    "--output-file" ->          new SaveFileHandler(),
    "--rotate" ->               new RotateHandler(),
    "--flip" ->                 new MirrorHandler(),
    "--scale" ->                new ScaleHandler(),
    "--table" ->                new PaletteHandler(),
    "--custom-table" ->         new CustomPaletteHandler()
  )
  private val parsersWithoutValues: Map[String, ArgsHandler] = Map(
    "--output-console" ->       new ConsoleOutputHandler(),
    "--image-random" ->         new RandomImageHandler(),
    "--invert" ->               new InversionHandler(),
  )

  @tailrec
  final def processNext(configuration: Configuration, argList: List[String]): Configuration = {
    argList match {
      case option :: remaining if parsersWithoutValues.contains(option) =>
        val handler = parsersWithoutValues(option)
        val (isSuccessful, updatedConfig) = handler.process("", configuration)
        if (isSuccessful) processNext(updatedConfig, remaining) else updatedConfig

      case option :: value :: remaining if parsersWithValues.contains(option) =>
        val handler = parsersWithValues(option)
        val (isSuccessful, updatedConfig) = handler.process(value, configuration)
        if (isSuccessful) processNext(updatedConfig, remaining) else updatedConfig

      case _ => configuration
    }
  }
}