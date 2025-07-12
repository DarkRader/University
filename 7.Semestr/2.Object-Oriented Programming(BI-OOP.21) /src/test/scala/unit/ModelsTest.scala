package unit

import org.scalatest.funsuite.AnyFunSuite
import models._

class ModelsTest extends AnyFunSuite {

  test("AsciiImage should set and get pixels correctly") {
    val asciiImage = new AsciiImage(3, 3)
    val testChar = Ascii('A')

    asciiImage.setPixel(1, 1, testChar)
    assert(asciiImage.getPixel(1, 1) == testChar)

    asciiImage.setPixel(0, 0, Ascii('B'))
    assert(asciiImage.getPixel(0, 0) == Ascii('B'))
  }

  test("GreyScaleImage should set and get pixels correctly") {
    val greyImage = new GreyScaleImage(3, 3)
    val testGrey = GreyScale(128)

    greyImage.setPixel(1, 1, testGrey)
    assert(greyImage.getPixel(1, 1) == testGrey)

    greyImage.setPixel(2, 2, GreyScale(200))
    assert(greyImage.getPixel(2, 2) == GreyScale(200))
  }

  test("RGBImage should set and get pixels correctly") {
    val rgbImage = new RGBImage(3, 3)
    val testRGB = RGB(255, 128, 64)

    rgbImage.setPixel(1, 1, testRGB)
    assert(rgbImage.getPixel(1, 1) == testRGB)

    rgbImage.setPixel(0, 2, RGB(128, 128, 128))
    assert(rgbImage.getPixel(0, 2) == RGB(128, 128, 128))
  }

  test("AsciiImage should initialize with default values") {
    val asciiImage = new AsciiImage(3, 3)
    for (x <- 0 until asciiImage.width; y <- 0 until asciiImage.height) {
      assert(asciiImage.getPixel(x, y) == Ascii('0'))
    }
  }

  test("GreyScaleImage should initialize with default values") {
    val greyImage = new GreyScaleImage(3, 3)
    for (x <- 0 until greyImage.width; y <- 0 until greyImage.height) {
      assert(greyImage.getPixel(x, y) == GreyScale(0))
    }
  }

  test("RGBImage should initialize with default values") {
    val rgbImage = new RGBImage(3, 3)
    for (x <- 0 until rgbImage.width; y <- 0 until rgbImage.height) {
      assert(rgbImage.getPixel(x, y) == RGB(0, 0, 0))
    }
  }

  test("GreyScale and RGB cases should support equality") {
    val grey1 = GreyScale(100)
    val grey2 = GreyScale(100)
    val grey3 = GreyScale(200)

    assert(grey1 == grey2)
    assert(grey1 != grey3)

    val rgb1 = RGB(10, 20, 30)
    val rgb2 = RGB(10, 20, 30)
    val rgb3 = RGB(40, 50, 60)

    assert(rgb1 == rgb2)
    assert(rgb1 != rgb3)
  }

  test("Image dimensions should match initialization") {
    val asciiImage = new AsciiImage(4, 5)
    val greyImage = new GreyScaleImage(6, 7)
    val rgbImage = new RGBImage(8, 9)

    assert(asciiImage.width == 4 && asciiImage.height == 5)
    assert(greyImage.width == 6 && greyImage.height == 7)
    assert(rgbImage.width == 8 && rgbImage.height == 9)
  }

  test("Attempting to access out-of-bounds pixels should throw exception") {
    val asciiImage = new AsciiImage(3, 3)

    assertThrows[IndexOutOfBoundsException] {
      asciiImage.getPixel(3, 3)
    }

    assertThrows[IndexOutOfBoundsException] {
      asciiImage.setPixel(3, 3, Ascii('X'))
    }
  }
}