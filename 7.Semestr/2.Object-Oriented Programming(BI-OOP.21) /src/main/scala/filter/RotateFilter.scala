package filter

import models.{GreyScale, Pixel, GreyScaleImage, Image}

trait RotateFilter[T <: Image[D], D <: Pixel] extends ImageFilter[T, D] {
  private def rotateImage(image: T, clockwise: Boolean = false): T = {
    val rotatedWidth = image.height
    val rotatedHeight = image.width
    val outputImage = createInstance(rotatedWidth, rotatedHeight)

    for (x <- 0 until image.width; y <- 0 until image.height) {
      val (newX, newY) = if (clockwise) {
        (y, image.width - 1 - x)
      } else {
        (image.height - 1 - y, x)
      }
      val pixelData = setPixel(getPixel(image, x, y))
      outputImage.setPixel(newX, newY, pixelData)
    }

    outputImage
  }

  protected def adjustRotation(image: T, angle: Double): T = {
    val angleNormalized = angle % 360
    angleNormalized match {
      case 90 => rotateImage(image)
      case -90 => rotateImage(image, clockwise = true)
      case 180 => rotateImage(rotateImage(image, clockwise = true), clockwise = true)
      case -180 => rotateImage(rotateImage(image, clockwise = true), clockwise = true)
      case 270 => rotateImage(image, clockwise = true)
      case -270 => rotateImage(image)
      case _ => image
    }
  }
}

class ImageRotationFilter(val angle: Double) extends RotateFilter[GreyScaleImage, GreyScale] {
  override def apply(image: GreyScaleImage): GreyScaleImage = adjustRotation(image, angle)

  override protected def createInstance(width: Int, height: Int): GreyScaleImage = new GreyScaleImage(width, height)

  override protected def getPixel(image: GreyScaleImage, x: Int, y: Int): Int = image.getPixel(x, y).value

  override protected def setPixel(value: Int): GreyScale = GreyScale(value)
}