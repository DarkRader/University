package transformation

import models.{AsciiImage, GreyScaleImage, GreyScale, Ascii}
import models.{Ascii, GreyScale}
import table.ImageTableTransformation

class GreyScaleToAsciiTransform(transformationTable: ImageTableTransformation)
  extends ImageTransformation[GreyScaleImage, AsciiImage, GreyScale, Ascii] {

  override def getPixel(sourcePixel: GreyScale): Ascii = transformationTable.transformPixel(sourcePixel)

  override def getInstance(width: Int, height: Int): AsciiImage = new AsciiImage(width, height)
}