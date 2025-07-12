package transformation

import models.{GreyScaleImage, ImageBase, GreyScale}

trait ImageProcessor[T <: ImageBase] {
  def apply(image: T): T
}

trait PixelProcessor extends ImageProcessor[GreyScaleImage] {

}

class ContrastAdjustment(param: Double) extends PixelProcessor {
  def apply(image: GreyScaleImage): GreyScaleImage = {
    val imgWidth = image.width
    val imgHeight = image.height
    
    var brightnessSum = 0
    for (x <- 0 until imgWidth; y <- 0 until imgHeight) {
      brightnessSum += image.getPixel(x, y).value.toByte & 0xFF
    }
    val avgBrightness = brightnessSum / (imgWidth * imgHeight)
    
    val adjustedImage = new GreyScaleImage(imgWidth, imgHeight)
    
    for (x <- 0 until imgWidth; y <- 0 until imgHeight) {
      val pixelBrightness = image.getPixel(x, y).value.toByte & 0xFF
      val adjustedPixelBrightness = ((pixelBrightness - avgBrightness) * param + avgBrightness).toInt
      
      val clampedBrightness = math.min(255, math.max(0, adjustedPixelBrightness))
      adjustedImage.setPixel(x, y, GreyScale(clampedBrightness))
    }

    adjustedImage
  }
}

class GreyscaleConversion() extends PixelProcessor {
  def apply (image: GreyScaleImage): GreyScaleImage = {
    val imgWidth = image.width
    val imgHeight = image.height
    val greyImage = new GreyScaleImage(imgWidth, imgHeight)

    for (x <- 0 until imgWidth) {
      for (y <- 0 until imgHeight) {
        val pixelColor = image.getPixel(x, y).value.toByte & 0xFF
        greyImage.setPixel(x, y, GreyScale(pixelColor))
      }
    }

    greyImage
  }
}