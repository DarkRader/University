package input

import java.awt.image.BufferedImage
import java.awt.{Color, Font}
import java.io.File
import java.nio.file.{Files, Paths}
import java.util.Random
import javax.imageio.ImageIO

trait ArgsHandler {
  def process(arg: String, configuration: Configuration): (Boolean, Configuration)
}

class PictureHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    if (arg.trim.isEmpty) {
      throw new IllegalArgumentException("Image path is required")
    }

    val filePath = Paths.get(arg)
    if (!Files.exists(filePath) || !Files.isReadable(filePath)) {
      throw new IllegalArgumentException("Invalid or inaccessible file")
    }

    if (isImage(arg)) {
      configuration.addOption("input", arg)
      (true, configuration)
    } else {
      throw new IllegalArgumentException("Unsupported image format")
    }
  }

  private def isImage(path: String): Boolean = {
    try {
      val img = ImageIO.read(Files.newInputStream(Paths.get(path)))
      img != null
    } catch {
      case _: Exception => false
    }
  }
}

class SaveFileHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    val targetPath = Paths.get(arg)

    if (!targetPath.toString.endsWith(".txt")) {
      throw new IllegalArgumentException("Output file must have a .txt extension")
    }

    if (!Files.exists(targetPath)) Files.createFile(targetPath)

    if (Files.isWritable(targetPath)) {
      configuration.addOption("outputPath", arg)
      configuration.addOption("outputFile", "file")
      (true, configuration)
    } else {
      throw new IllegalArgumentException("Cannot write to specified file")
    }
  }
}

class RotateHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    arg.toIntOption match {
      case Some(rotationValue) =>
        configuration.addOption("rotate", arg)
        (true, configuration)
      case None =>
        throw new IllegalArgumentException("Rotation value must be an integer")
    }
  }
}

class MirrorHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    arg match {
      case "y" =>
        configuration.addOption("flip", "y")
        (true, configuration)
      case "x" =>
        configuration.addOption("flip", "x")
        (true, configuration)
      case _ =>
        throw new IllegalArgumentException("Invalid mirror option. Use 'y' or 'x'")
    }
  }
}

class ScaleHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    arg.toDoubleOption match {
      case Some(scaleValue) =>
        configuration.addOption("scale", arg)
        (true, configuration)
      case None =>
        throw new IllegalArgumentException("Invalid scaling factor. Provide a valid number")
    }
  }
}

class PaletteHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    arg match {
      case "bourke" =>
        configuration.addOption("table", "bourke")
      case "bourke#2" =>
        configuration.addOption("table", "bourke#2")
      case "unlinear" =>
        configuration.addOption("table", "unlinear")
      case _ =>
        configuration.addOption("table", "bourke")
    }
    (true, configuration)
  }
}

class ConsoleOutputHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    configuration.addOption("outputStd", "std")
    (true, configuration)
  }
}

class RandomImageHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    val generatedImagePath = generateRandomImage()
    if (generatedImagePath.isEmpty) {
      (false, configuration)
    } else {
      configuration.addOption("input", generatedImagePath)
      (true, configuration)
    }
  }

  private def generateRandomImage(): String = {
    val random = new Random()
    val imgWidth = 666
    val imgHeight = 666
    val bufferedImage = new BufferedImage(imgWidth, imgHeight, BufferedImage.TYPE_INT_RGB)
    val graphics = bufferedImage.createGraphics()

    // Generate a random solid-colored background
    val backgroundColor = new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256))
    graphics.setColor(backgroundColor)
    graphics.fillRect(0, 0, imgWidth, imgHeight)

    // Add random rectangles with varying opacities
    for (_ <- 1 to random.nextInt(10) + 5) {
      val rectangleColor = new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256), random.nextInt(128) + 128) // Semi-transparent
      graphics.setColor(rectangleColor)
      graphics.fillRect(
        random.nextInt(imgWidth),
        random.nextInt(imgHeight),
        random.nextInt(150) + 20,
        random.nextInt(150) + 20
      )
    }

    // Add random ovals with solid colors
    for (_ <- 1 to random.nextInt(10) + 5) {
      graphics.setColor(new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256)))
      graphics.fillOval(
        random.nextInt(imgWidth),
        random.nextInt(imgHeight),
        random.nextInt(100) + 10,
        random.nextInt(100) + 10
      )
    }

    // Add random diagonal lines
    for (_ <- 1 to random.nextInt(15) + 5) {
      graphics.setColor(new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256)))
      graphics.drawLine(
        random.nextInt(imgWidth),
        random.nextInt(imgHeight),
        random.nextInt(imgWidth),
        random.nextInt(imgHeight)
      )
    }

    // Add a watermark-like random text
    val messages = List("Whispering clocks argue with the shadows over stolen seconds",
      "A giraffe in a spacesuit can’t solve the mystery of invisible cheese",
      "The moon danced with its reflection, but the puddle forgot the steps",
      "An umbrella’s greatest fear is the sun’s laughter",
      "If penguins could yodel, would the mountains blush?",
      "Rainbows wear sunglasses when the stars are too bright")
    val fontSize = random.nextInt(10) + 25
    graphics.setFont(new Font("SansSerif", Font.ITALIC, fontSize))
    graphics.setColor(new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256), 200))
    graphics.drawString(messages(random.nextInt(messages.length)), 50, imgHeight / 2)

    graphics.dispose()

    val outputImagePath = "random_image.jpg"
    ImageIO.write(bufferedImage, "jpg", new File(outputImagePath))
    outputImagePath
  }
}

class InversionHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    configuration.addOption("invert", arg)
    (true, configuration)
  }
}

class CustomPaletteHandler extends ArgsHandler {
  override def process(arg: String, configuration: Configuration): (Boolean, Configuration) = {
    if (arg.isBlank) {
      println("Warning: No custom table provided. Using default palette.")
      configuration.addOption("table", "bourke")
    } else {
      configuration.addOption("custom", arg)
    }
    (true, configuration)
  }
}