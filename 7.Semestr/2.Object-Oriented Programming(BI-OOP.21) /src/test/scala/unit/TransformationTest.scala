package unit

import models.{Ascii, AsciiImage, GreyScale, GreyScaleImage, RGB, RGBImage}
import org.scalatest.funsuite.AnyFunSuite
import table.BourkeAsciiTransformationTable
import transformation._

class TransformationTest extends AnyFunSuite {

  test("RGBToGreyScaleTransform should correctly convert RGB to GreyScale") {
    val rgbImage = new RGBImage(2, 2)
    rgbImage.setPixel(0, 0, RGB(255, 0, 0)) 
    rgbImage.setPixel(1, 0, RGB(0, 255, 0)) 
    rgbImage.setPixel(0, 1, RGB(0, 0, 255)) 
    rgbImage.setPixel(1, 1, RGB(255, 255, 255)) 

    val transformer = new RGBToGreyScaleTransform()
    val greyScaleImage = transformer.applyTransformation(rgbImage)

    assert(greyScaleImage.width == 2)
    assert(greyScaleImage.height == 2)
    assert(greyScaleImage.getPixel(0, 0).value == 76) 
    assert(greyScaleImage.getPixel(1, 0).value == 150) 
    assert(greyScaleImage.getPixel(0, 1).value == 28) 
    assert(greyScaleImage.getPixel(1, 1).value == 255) 
  }

  test("GreyScaleToAsciiTransform should correctly convert GreyScale to Ascii") {
    val greyScaleImage = new GreyScaleImage(3, 1)
    greyScaleImage.setPixel(0, 0, GreyScale(0))  
    greyScaleImage.setPixel(1, 0, GreyScale(128)) 
    greyScaleImage.setPixel(2, 0, GreyScale(255)) 

    val transformationTable = new BourkeAsciiTransformationTable()
    val transformer = new GreyScaleToAsciiTransform(transformationTable)
    val asciiImage = transformer.applyTransformation(greyScaleImage)

    assert(asciiImage.width == 3)
    assert(asciiImage.height == 1)
    assert(asciiImage.getPixel(0, 0).value == ' ') 
    assert(asciiImage.getPixel(1, 0).value == '=') 
    assert(asciiImage.getPixel(2, 0).value == '@') 
  }

  test("ContrastAdjustment should correctly adjust contrast") {
    val greyScaleImage = new GreyScaleImage(3, 1)
    greyScaleImage.setPixel(0, 0, GreyScale(50))
    greyScaleImage.setPixel(1, 0, GreyScale(100))
    greyScaleImage.setPixel(2, 0, GreyScale(150))

    val contrast = new ContrastAdjustment(1.5)
    val adjustedImage = contrast.apply(greyScaleImage)

    assert(adjustedImage.width == 3)
    assert(adjustedImage.height == 1)
    
    assert(adjustedImage.getPixel(0, 0).value >= 0 && adjustedImage.getPixel(0, 0).value <= 255)
    assert(adjustedImage.getPixel(1, 0).value >= 0 && adjustedImage.getPixel(1, 0).value <= 255)
    assert(adjustedImage.getPixel(2, 0).value >= 0 && adjustedImage.getPixel(2, 0).value <= 255)
    
    val modified = greyScaleImage.getPixel(0, 0).value != adjustedImage.getPixel(0, 0).value ||
      greyScaleImage.getPixel(1, 0).value != adjustedImage.getPixel(1, 0).value ||
      greyScaleImage.getPixel(2, 0).value != adjustedImage.getPixel(2, 0).value
    assert(modified, "At least one pixel's brightness should be adjusted")
  }

  test("GreyscaleConversion should retain the same values in GreyScaleImage") {
    val greyScaleImage = new GreyScaleImage(2, 2)
    greyScaleImage.setPixel(0, 0, GreyScale(50))
    greyScaleImage.setPixel(1, 0, GreyScale(100))
    greyScaleImage.setPixel(0, 1, GreyScale(150))
    greyScaleImage.setPixel(1, 1, GreyScale(200))

    val greyscaleConversion = new GreyscaleConversion()
    val convertedImage = greyscaleConversion.apply(greyScaleImage)

    assert(convertedImage.width == 2)
    assert(convertedImage.height == 2)
    assert(convertedImage.getPixel(0, 0).value == 50)
    assert(convertedImage.getPixel(1, 0).value == 100)
    assert(convertedImage.getPixel(0, 1).value == 150)
    assert(convertedImage.getPixel(1, 1).value == 200)
  }
}