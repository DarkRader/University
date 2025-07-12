package unit

import load.LoadFileImage
import models.{RGB, RGBImage}
import org.scalatest.funsuite.AnyFunSuite
import java.io.File
import javax.imageio.ImageIO

class LoadFileImageTest extends AnyFunSuite {

  test("LoadFileImage should correctly load a valid image file") {

    val width = 2
    val height = 2
    val testImagePath = "src/test/scala/test_image.png"
    val bufferedImage = new java.awt.image.BufferedImage(width, height, java.awt.image.BufferedImage.TYPE_INT_RGB)
    
    bufferedImage.setRGB(0, 0, (255 << 16) | (0 << 8) | 0) 
    bufferedImage.setRGB(1, 0, (0 << 16) | (255 << 8) | 0) 
    bufferedImage.setRGB(0, 1, (0 << 16) | (0 << 8) | 255) 
    bufferedImage.setRGB(1, 1, (255 << 16) | (255 << 8) | 255) 
    
    val outputFile = new File(testImagePath)
    ImageIO.write(bufferedImage, "png", outputFile)

    try {
      val loader = new LoadFileImage()
      val loadedImage = loader.load(testImagePath)
      
      assert(loadedImage.width == width)
      assert(loadedImage.height == height)
      assert(loadedImage.getPixel(0, 0) == RGB(255, 0, 0)) 
      assert(loadedImage.getPixel(1, 0) == RGB(0, 255, 0)) 
      assert(loadedImage.getPixel(0, 1) == RGB(0, 0, 255)) 
      assert(loadedImage.getPixel(1, 1) == RGB(255, 255, 255)) 
    } finally {
      if (outputFile.exists()) {
        outputFile.delete()
      }
    }
  }

  test("LoadFileImage should throw an exception for an invalid file path") {
    val loader = new LoadFileImage()
    val invalidFilePath = "nonexistent.png"

    val exception = intercept[Exception] {
      loader.load(invalidFilePath)
    }

    assert(exception.isInstanceOf[Exception])
  }

  test("LoadFileImage should throw an exception for an empty file path") {
    val loader = new LoadFileImage()

    val exception = intercept[Exception] {
      loader.load("")
    }

    assert(exception.isInstanceOf[Exception])
  }
}