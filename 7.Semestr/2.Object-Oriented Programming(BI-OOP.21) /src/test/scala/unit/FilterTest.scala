package unit

import org.scalatest.funsuite.AnyFunSuite
import filter._
import models._

class FilterTest extends AnyFunSuite {

  test("MirrorFilter should correctly mirror an image along the x-axis") {
    val image = new GreyScaleImage(2, 2)
    image.setPixel(0, 0, GreyScale(10))
    image.setPixel(1, 0, GreyScale(20))
    image.setPixel(0, 1, GreyScale(30))
    image.setPixel(1, 1, GreyScale(40))

    val filter = new GreyScaleMirrorFilter("x")
    val mirrored = filter.apply(image)

    assert(mirrored.getPixel(0, 0) == GreyScale(30))
    assert(mirrored.getPixel(1, 0) == GreyScale(40))
    assert(mirrored.getPixel(0, 1) == GreyScale(10))
    assert(mirrored.getPixel(1, 1) == GreyScale(20))
  }

  test("MirrorFilter should correctly mirror an image along the y-axis") {
    val image = new GreyScaleImage(2, 2)
    image.setPixel(0, 0, GreyScale(10))
    image.setPixel(1, 0, GreyScale(20))
    image.setPixel(0, 1, GreyScale(30))
    image.setPixel(1, 1, GreyScale(40))

    val filter = new GreyScaleMirrorFilter("y")
    val mirrored = filter.apply(image)

    assert(mirrored.getPixel(0, 0) == GreyScale(20))
    assert(mirrored.getPixel(1, 0) == GreyScale(10))
    assert(mirrored.getPixel(0, 1) == GreyScale(40))
    assert(mirrored.getPixel(1, 1) == GreyScale(30))
  }

  test("NegativeFilter should correctly invert pixel values") {
    val image = new GreyScaleImage(2, 2)
    image.setPixel(0, 0, GreyScale(100))
    image.setPixel(1, 0, GreyScale(200))
    image.setPixel(0, 1, GreyScale(50))
    image.setPixel(1, 1, GreyScale(0))

    val filter = new GreyScaleNegativeFilter()
    val negative = filter.apply(image)

    assert(negative.getPixel(0, 0) == GreyScale(155))
    assert(negative.getPixel(1, 0) == GreyScale(55))
    assert(negative.getPixel(0, 1) == GreyScale(205))
    assert(negative.getPixel(1, 1) == GreyScale(255))
  }

  test("RotateFilter should correctly rotate an image by 90 degrees clockwise") {
    val image = new GreyScaleImage(2, 2)
    image.setPixel(0, 0, GreyScale(10))
    image.setPixel(1, 0, GreyScale(20))
    image.setPixel(0, 1, GreyScale(30))
    image.setPixel(1, 1, GreyScale(40))

    val filter = new ImageRotationFilter(90)
    val rotated = filter.apply(image)

    assert(rotated.width == 2)
    assert(rotated.height == 2)
    assert(rotated.getPixel(0, 0) == GreyScale(30))
    assert(rotated.getPixel(1, 0) == GreyScale(10))
    assert(rotated.getPixel(0, 1) == GreyScale(40))
    assert(rotated.getPixel(1, 1) == GreyScale(20))
  }

  test("ResizingFilter should correctly resize an image") {
    val image = new GreyScaleImage(2, 2)
    image.setPixel(0, 0, GreyScale(10))
    image.setPixel(1, 0, GreyScale(20))
    image.setPixel(0, 1, GreyScale(30))
    image.setPixel(1, 1, GreyScale(40))

    val filter = new GreyScaleResizingFilter(0.5)
    val resized = filter.apply(image)

    assert(resized.width == 1)
    assert(resized.height == 1)
    assert(resized.getPixel(0, 0) == GreyScale(10))
  }

  test("ResizingFilter should correctly upscale an image") {
    val image = new GreyScaleImage(2, 2)
    image.setPixel(0, 0, GreyScale(10))
    image.setPixel(1, 0, GreyScale(20))
    image.setPixel(0, 1, GreyScale(30))
    image.setPixel(1, 1, GreyScale(40))

    val filter = new GreyScaleResizingFilter(2.0)
    val resized = filter.apply(image)

    assert(resized.width == 4)
    assert(resized.height == 4)
    assert(resized.getPixel(0, 0) == GreyScale(10))
    assert(resized.getPixel(2, 0) == GreyScale(20))
    assert(resized.getPixel(0, 2) == GreyScale(30))
    assert(resized.getPixel(2, 2) == GreyScale(40))
  }
}