package filter

import models.{GreyScale, Pixel, GreyScaleImage, Image}

trait MirrorFilter[T <: Image[D], D <: Pixel] extends ImageFilter[T, D] {
  protected def mirrorImage(inputImage: T, flipAxis: String): T = {
    val mirroredImage = createInstance(inputImage.width, inputImage.height)

    flipAxis.toLowerCase match {
      case "x" =>
        copySection(inputImage, mirroredImage, 0, 0, inputImage.width, inputImage.height, flipX = true, flipY = false)

      case "y" =>
        copySection(inputImage, mirroredImage, 0, 0, inputImage.width, inputImage.height, flipX = false, flipY = true)

      case _ => return inputImage
    }

    mirroredImage
  }

  private def copySection(source: T, target: T, startX: Int, startY: Int, endX: Int, endY: Int, flipX: Boolean, flipY: Boolean): Unit = {
    for (x <- startX until endX; y <- startY until endY) {
      val targetX = if (flipY) endX - 1 - (x - startX) else x
      val targetY = if (flipX) endY - 1 - (y - startY) else y
      val pixel = setPixel(getPixel(source, x, y))
      target.setPixel(targetX, targetY, pixel)
    }
  }
}

class GreyScaleMirrorFilter(flipAxis: String) extends MirrorFilter[GreyScaleImage, GreyScale] {
  override def apply(inputImage: GreyScaleImage): GreyScaleImage = mirrorImage(inputImage, flipAxis)

  override protected def createInstance(width: Int, height: Int): GreyScaleImage = new GreyScaleImage(width, height)

  override protected def getPixel(inputImage: GreyScaleImage, col: Int, row: Int): Int = inputImage.getPixel(col, row).value

  override protected def setPixel(value: Int): GreyScale = GreyScale(value)
}