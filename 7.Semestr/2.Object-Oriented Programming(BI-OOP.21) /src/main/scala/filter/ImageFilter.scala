package filter

import models.{Image, Pixel}

trait ImageFilter[T <: Image[D], D <: Pixel] extends Filter[T] {
  protected def createInstance(width: Int, height: Int): T

  protected def getPixel(image: T, x: Int, y: Int): Int

  protected def setPixel(value: Int): D
}