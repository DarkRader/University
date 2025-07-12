package filter

import models.{GreyScale, Pixel, GreyScaleImage, Image}

trait ResizingFilter[T <: Image[D], D <: Pixel] extends ImageFilter[T, D] {
  protected def resizeImage(inputImage: T, factor: Double): T = {
    val resizedWidth = (inputImage.width * factor).toInt
    val resizedHeight = (inputImage.height * factor).toInt
    val outputImage = createInstance(resizedWidth, resizedHeight)

    for (newX <- 0 until resizedWidth; newY <- 0 until resizedHeight) {
      val originalX = (newX / factor).toInt
      val originalY = (newY / factor).toInt
      val pixel = setPixel(getPixel(inputImage, originalX, originalY))
      outputImage.setPixel(newX, newY, pixel)
    }
    outputImage
  }
}

class GreyScaleResizingFilter(factor: Double) extends ResizingFilter[GreyScaleImage, GreyScale] {
  override def apply(inputImage: GreyScaleImage): GreyScaleImage = resizeImage(inputImage, factor)

  override protected def createInstance(width: Int, height: Int): GreyScaleImage = new GreyScaleImage(width, height)

  override protected def getPixel(inputImage: GreyScaleImage, col: Int, row: Int): Int = inputImage.getPixel(col, row).value

  override protected def setPixel(value: Int): GreyScale = GreyScale(value)
}