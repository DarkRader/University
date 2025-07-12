package unit

import models.{Ascii, AsciiImage}
import pages.AsciiExportPage
import org.scalatest.funsuite.AnyFunSuite

class AsciiExportPageTest extends AnyFunSuite {

  test("AsciiExportPage should correctly display a single pixel image") {
    val asciiImage = new AsciiImage(1, 1)
    asciiImage.setPixel(0, 0, Ascii('A')) 

    val page = new AsciiExportPage(asciiImage)
    val output = page.display()

    assert(output == "A\n") 
  }

  test("AsciiExportPage should correctly display a 2x2 image") {
    val asciiImage = new AsciiImage(2, 2)
    asciiImage.setPixel(0, 0, Ascii('A'))
    asciiImage.setPixel(1, 0, Ascii('B'))
    asciiImage.setPixel(0, 1, Ascii('C'))
    asciiImage.setPixel(1, 1, Ascii('D'))

    val page = new AsciiExportPage(asciiImage)
    val output = page.display()

    assert(output == "AB\nCD\n")
  }

  test("AsciiExportPage should handle empty image") {
    val asciiImage = new AsciiImage(0, 0) 

    val page = new AsciiExportPage(asciiImage)
    val output = page.display()

    assert(output == "") 
  }

  test("AsciiExportPage should correctly display an image with different characters") {
    val asciiImage = new AsciiImage(3, 3)
    asciiImage.setPixel(0, 0, Ascii('1'))
    asciiImage.setPixel(1, 0, Ascii('2'))
    asciiImage.setPixel(2, 0, Ascii('3'))
    asciiImage.setPixel(0, 1, Ascii('4'))
    asciiImage.setPixel(1, 1, Ascii('5'))
    asciiImage.setPixel(2, 1, Ascii('6'))
    asciiImage.setPixel(0, 2, Ascii('7'))
    asciiImage.setPixel(1, 2, Ascii('8'))
    asciiImage.setPixel(2, 2, Ascii('9'))

    val page = new AsciiExportPage(asciiImage)
    val output = page.display()

    assert(output == "123\n456\n789\n") 
  }

  test("AsciiExportPage should handle larger image sizes") {
    val asciiImage = new AsciiImage(4, 3)
    asciiImage.setPixel(0, 0, Ascii('A'))
    asciiImage.setPixel(1, 0, Ascii('B'))
    asciiImage.setPixel(2, 0, Ascii('C'))
    asciiImage.setPixel(3, 0, Ascii('D'))
    asciiImage.setPixel(0, 1, Ascii('E'))
    asciiImage.setPixel(1, 1, Ascii('F'))
    asciiImage.setPixel(2, 1, Ascii('G'))
    asciiImage.setPixel(3, 1, Ascii('H'))
    asciiImage.setPixel(0, 2, Ascii('I'))
    asciiImage.setPixel(1, 2, Ascii('J'))
    asciiImage.setPixel(2, 2, Ascii('K'))
    asciiImage.setPixel(3, 2, Ascii('L'))

    val page = new AsciiExportPage(asciiImage)
    val output = page.display()

    assert(output == "ABCD\nEFGH\nIJKL\n") 
  }

}