package transformation

import models.{Image, Pixel}

trait ImageTransformation[A <: Image[T], B <: Image[D], T <: Pixel, D <: Pixel]
  extends Transformation[A, B, T, D] {

  protected def getPixel(sourcePixel: T): D
  protected def getInstance(width: Int, height: Int): B

  override def applyTransformation(inputImage: A): B = {
    val outputImage = getInstance(inputImage.width, inputImage.height)
    for (x <- 0 until inputImage.width; y <- 0 until inputImage.height) {
      val transformedPixel = getPixel(inputImage.getPixel(x, y))
      outputImage.setPixel(x, y, transformedPixel)
    }
    outputImage
  }
}