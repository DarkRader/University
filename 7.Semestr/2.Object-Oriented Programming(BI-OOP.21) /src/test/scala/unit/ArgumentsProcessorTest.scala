package unit

import input._
import org.scalatest.funsuite.AnyFunSuite

class ArgumentsProcessorTest extends AnyFunSuite {

  test("ArgumentsProcessor should correctly handle valid arguments") {
    val args = List("--image", "dog_test.jpg", "--rotate", "90", "--scale", "1.5", "--flip", "x")
    val processor = new ArgumentsProcessor()
    val config = new Configuration()

    val updatedConfig = processor.processNext(config, args)

    assert(updatedConfig.getOption("input") == List("dog_test.jpg"))
    assert(updatedConfig.getOption("rotate") == List("90"))
    assert(updatedConfig.getOption("scale") == List("1.5"))
    assert(updatedConfig.getOption("flip") == List("x"))
  }

  test("ArgumentsProcessor should skip unrecognized arguments and process known ones") {
    val args = List("--image", "dog_test.jpg", "--flip", "y", "--unknown", "value")
    val processor = new ArgumentsProcessor()
    val config = new Configuration()

    val updatedConfig = processor.processNext(config, args)

    assert(updatedConfig.getOption("input") == List("dog_test.jpg"))
    assert(updatedConfig.getOption("flip") == List("y"))
    assert(updatedConfig.getOption("unknown").isEmpty)
  }

  test("ArgumentsProcessor should throw exception for invalid rotation value") {
    val args = List("--image", "dog_test.jpg", "--rotate", "invalid")
    val processor = new ArgumentsProcessor()
    val config = new Configuration()

    val exception = intercept[IllegalArgumentException] {
      processor.processNext(config, args)
    }

    assert(exception.getMessage.contains("Rotation value must be an integer"))
  }
}