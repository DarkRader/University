package table

import models.{Ascii, GreyScale, Pixel}

trait TableTransformation[T <: Pixel, D <: Pixel] {
  protected var characterData: String
  def transformPixel(sourcePixel: T): D
}

trait ImageTableTransformation extends TableTransformation[GreyScale, Ascii] {

}

class BourkeAsciiTransformationTable extends ImageTableTransformation {
  protected var characterData: String = " .:-=+*#%@"

  override def transformPixel(sourcePixel: GreyScale): Ascii = {
    val brightness = math.max(0, math.min(sourcePixel.value, 255))
    val charIndex = (brightness * (characterData.length - 1)) / 255
    Ascii(characterData(charIndex).charValue())
  }
} 