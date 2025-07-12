package load

import models.{RGB, RGBImage}

import java.io.File
import javax.imageio.ImageIO

class LoadFileImage extends LoadImage[RGBImage] {
  def load(path: String): RGBImage = {
    val file = new File(path)
    val initImage = ImageIO.read(file)

    val width = initImage.getWidth
    val height = initImage.getHeight

    val pixelImage = new RGBImage(width, height)
    
    for (x <- 0 until width; y <- 0 until height) {
      val rgb = initImage.getRGB(x, y)
      val red = (rgb >> 16) & 0xFF
      val green = (rgb >> 8) & 0xFF
      val blue = rgb & 0xFF
      
      val pixel = RGB(red, green, blue)
      pixelImage.setPixel(x, y, pixel)
    }
    pixelImage
  }
}