package models

class RGBImage(override val width: Int, override val height: Int) extends Image[RGB] {
  protected var data: Array[Array[RGB]] = Array.fill(height, width)(RGB(0, 0, 0))
  override def getPixel(x: Int, y: Int): RGB = data(y)(x)
  override def setPixel(x: Int, y: Int, value: RGB): Unit = data(y)(x) = value
}