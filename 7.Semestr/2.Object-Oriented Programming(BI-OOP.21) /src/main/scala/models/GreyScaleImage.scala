package models

class GreyScaleImage(override val width: Int, override val height: Int) extends Image[GreyScale] {
  protected var data: Array[Array[GreyScale]] = Array.fill(height, width)(GreyScale(0))

  override def getPixel(x: Int, y: Int): GreyScale = data(y)(x)

  override def setPixel(x: Int, y: Int, value: GreyScale): Unit = data(y)(x) = value
}