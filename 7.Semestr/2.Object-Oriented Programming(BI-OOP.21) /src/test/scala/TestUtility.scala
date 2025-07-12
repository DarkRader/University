import models.{GreyScaleImage, RGBImage, GreyScale, RGB}

import java.io.File
import java.util.UUID
import scala.util.Random

trait TestUtility {

  // Paths for test data
  val sampleImagePath = "./src/test/scala/testFiles/test_image.jpg"
  val testDirectory = "./src/test/scala/testFiles/"

  def generateTestFilePath: String = s"$testDirectory${UUID.randomUUID().toString}.txt"
  def generateTestImagePath: String = s"$testDirectory${UUID.randomUUID().toString}.png"

  // Predefined GreyScale Images
  val testGreyScaleImages: Seq[GreyScaleImage] = Seq(
    buildGreyScaleImage(1, 1),
    buildGreyScaleImage(2, 2),
    buildGreyScaleImage(10, 10),
    buildGreyScaleImage(50, 100),
    buildGreyScaleImage(1, 500),
    buildGreyScaleImage(1000, 1)
  )

  val emptyGreyScaleImages: Seq[GreyScaleImage] = Seq(
    buildGreyScaleImage(0, 0),
    buildGreyScaleImage(0, 5),
    buildGreyScaleImage(5, 0),
    buildGreyScaleImage(0, 50),
    buildGreyScaleImage(100, 0),
    buildGreyScaleImage(0, 500)
  )

  // Predefined RGB Images
  val rgbTestImages: Seq[RGBImage] = Seq(
    new RGBImage(1, 1),
    new RGBImage(2, 2),
    new RGBImage(10, 10),
    new RGBImage(50, 100),
    new RGBImage(1, 500),
    new RGBImage(1000, 1)
  )

  // Function to create GreyScaleImage
  def buildGreyScaleImage(width: Int, height: Int): GreyScaleImage = new GreyScaleImage(width, height)

  // Filling GreyScale Image with Test Data
  def populateGreyScaleImage(image: GreyScaleImage, defaultPixel: GreyScale = GreyScale(256)): Unit = {
    val randomizer = new Random()
    for (row <- 0 until image.height; col <- 0 until image.width) {
      val pixelValue = if (defaultPixel.value == 256) {
        GreyScale(randomizer.nextInt(256))
      } else {
        defaultPixel
      }
      image.setPixel(col, row, pixelValue)
    }
  }

  // Filling RGB Image with Test Data
  def populateRGBImage(image: RGBImage, defaultPixel: RGB = RGB(256, 256, 256)): Unit = {
    val randomizer = new Random()
    for (row <- 0 until image.height; col <- 0 until image.width) {
      val pixelValue = if (defaultPixel.red == 256 && defaultPixel.green == 256 && defaultPixel.blue == 256) {
        RGB(randomizer.nextInt(256), randomizer.nextInt(256), randomizer.nextInt(256))
      } else {
        defaultPixel
      }
      image.setPixel(col, row, pixelValue)
    }
  }

  // Ensure file exists or is created
  def ensureFileExists(fileName: String): Unit = {
    deleteIfExists(fileName)
    val file = new File(fileName)
    if (!file.createNewFile()) {
      throw new RuntimeException(s"Unable to create file: $fileName")
    }
  }

  // Ensure file is deleted
  def deleteIfExists(filePath: String): Unit = {
    val file = new File(filePath)
    if (file.exists() && !file.delete()) {
      throw new RuntimeException(s"Unable to delete file: $filePath")
    }
  }

  // Compare Two GreyScale Images
  def areGreyScaleImagesEqual(img1: GreyScaleImage, img2: GreyScaleImage): Boolean = {
    if (img1.width != img2.width || img1.height != img2.height) {
      println("Image dimensions do not match.")
      false
    } else {
      (0 until img1.height).forall { row =>
        (0 until img1.width).forall { col =>
          val pixel1 = img1.getPixel(col, row).value
          val pixel2 = img2.getPixel(col, row).value
          if (pixel1 != pixel2) {
            println(s"Mismatch at ($col, $row): $pixel1 vs $pixel2")
          }
          pixel1 == pixel2
        }
      }
    }
  }
}