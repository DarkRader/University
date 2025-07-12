package pages

import models.AsciiImage

class AsciiExportPage(asciiImage: AsciiImage) extends TextPage {

  override def display(): String = {
    val output = new StringBuilder()
    for (y <- 0 until asciiImage.height) {
      for (x <- 0 until asciiImage.width) {
        output.append(asciiImage.getPixel(x, y).value)
      }
      output.append(System.lineSeparator())
    }
    output.toString()
  }
}