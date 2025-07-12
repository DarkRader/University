package models

class AsciiImage(override val width: Int, override val height: Int) extends Image[Ascii] {
  protected var data: Array[Array[Ascii]] = Array.fill(height, width)(Ascii('0'))
  override def getPixel(x: Int, y: Int): Ascii = data(y)(x)
  override def setPixel(x: Int, y: Int, value: Ascii): Unit = data(y)(x) = value
}