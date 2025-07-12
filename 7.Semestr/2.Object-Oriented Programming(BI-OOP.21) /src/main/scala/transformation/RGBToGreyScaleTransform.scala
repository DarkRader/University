package transformation

import models.{GreyScaleImage, RGBImage, GreyScale, RGB}

class RGBToGreyScaleTransform extends ImageTransformation[RGBImage, GreyScaleImage, RGB, GreyScale] {
  override def getPixel(pixel: RGB): GreyScale = {
    val luminance = calculateLuminance(pixel)
    GreyScale(luminance)
  }

  override def getInstance(width: Int, height: Int): GreyScaleImage = new GreyScaleImage(width, height)

  private def calculateLuminance(rgbPixel: RGB): Int = {
    val red = rgbPixel.red
    val green = rgbPixel.green
    val blue = rgbPixel.blue
    val intensity = (red * 0.3 + green * 0.59 + blue * 0.11).toInt
    intensity
  }
}