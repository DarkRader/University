package filter

import models.{GreyScale, Pixel, GreyScaleImage, Image}

trait NegativeFilter[T <: Image[D], D <: Pixel] extends ImageFilter[T, D] {
  protected def applyNegativeEffect(inputImage: T): T = {
    val outputImage = createInstance(inputImage.width, inputImage.height)
    for (x <- 0 until inputImage.width; y <- 0 until inputImage.height) {
      val originalValue = getPixel(inputImage, x, y)
      val negatedValue = 255 - (originalValue & 0xFF)
      val negativePixel = setPixel(negatedValue)
      outputImage.setPixel(x, y, negativePixel)
    }
    outputImage
  }
}

class GreyScaleNegativeFilter extends NegativeFilter[GreyScaleImage, GreyScale] {
  override def apply(inputImage: GreyScaleImage): GreyScaleImage = applyNegativeEffect(inputImage)

  override protected def createInstance(width: Int, height: Int): GreyScaleImage = new GreyScaleImage(width, height)

  override protected def getPixel(inputImage: GreyScaleImage, x: Int, y: Int): Int = inputImage.getPixel(x, y).value

  override protected def setPixel(value: Int): GreyScale = GreyScale(value)
}