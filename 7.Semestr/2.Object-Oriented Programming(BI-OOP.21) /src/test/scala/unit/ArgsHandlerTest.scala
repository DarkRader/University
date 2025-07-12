package unit

import input._
import org.scalatest.funsuite.AnyFunSuite
import java.io.File

class ArgsHandlerTest extends AnyFunSuite {

  test("PictureHandler should process valid image path") {
    val validImagePath = "src/test/scala/test_image.jpg"
    val config = new Configuration()
    val handler = new PictureHandler()

    val testFile = new File(validImagePath)
    if (!testFile.exists()) testFile.createNewFile()
    val (success, updatedConfig) = handler.process(validImagePath, config)

    assert(success)
    assert(updatedConfig.getOption("input") == List(validImagePath))
  }

  test("PictureHandler should throw exception for invalid image path") {
    val invalidImagePath = "invalid/image/path.jpg"
    val config = new Configuration()
    val handler = new PictureHandler()

    val exception = intercept[IllegalArgumentException] {
      handler.process(invalidImagePath, config)
    }

    assert(exception.getMessage.contains("Invalid or inaccessible file"))
  }

  test("SaveFileHandler should process valid file path") {
    val validFilePath = "./test_output.txt"
    val config = new Configuration()
    val handler = new SaveFileHandler()

    val file = new File(validFilePath)
    if (file.exists()) {
      file.delete()
    }

    val (success, updatedConfig) = handler.process(validFilePath, config)

    assert(success)
    assert(updatedConfig.getOption("outputPath") == List(validFilePath))
    assert(updatedConfig.getOption("outputFile") == List("file"))

    if (file.exists()) {
      file.delete()
    }
  }

  test("RotateHandler should process valid rotation argument") {
    val validRotation = "90"
    val config = new Configuration()
    val handler = new RotateHandler()

    val (success, updatedConfig) = handler.process(validRotation, config)

    assert(success)
    assert(updatedConfig.getOption("rotate") == List(validRotation))
  }

  test("RotateHandler should throw exception for invalid rotation argument") {
    val invalidRotation = "invalid"
    val config = new Configuration()
    val handler = new RotateHandler()

    val exception = intercept[IllegalArgumentException] {
      handler.process(invalidRotation, config)
    }

    assert(exception.getMessage.contains("Rotation value must be an integer"))
  }
}