package models


trait ImageBase

trait Image[T <: Pixel] extends ImageBase {
  protected var data: Array[Array[T]]
  def getPixel(x: Int, y: Int): T
  def setPixel(x: Int, y: Int, value: T): Unit
  def width: Int
  def height: Int
}