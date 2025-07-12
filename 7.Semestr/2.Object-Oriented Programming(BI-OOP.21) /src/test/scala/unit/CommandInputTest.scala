package unit

import input._
import org.scalatest.funsuite.AnyFunSuite

class CommandInputTest extends AnyFunSuite {

  test("CommandInput should throw exception for missing image argument") {
    val args = Array("--table", "bourke")
    val commandInput = new CommandInput(args)

    val exception = intercept[IllegalArgumentException] {
      commandInput.fetchImageConfig
    }

    assert(exception.getMessage.contains("Image argument is missing"))
  }

  test("CommandInput should throw exception for duplicate image argument") {
    val args = Array("--image", "test.jpg", "--image", "another.jpg")
    val commandInput = new CommandInput(args)

    val exception = intercept[IllegalArgumentException] {
      commandInput.fetchImageConfig
    }

    assert(exception.getMessage.contains("Duplicate image argument detected"))
  }

  test("CommandInput should correctly parse image argument") {
    val args = Array("--image", "dog_test.jpg", "--table", "bourke")
    val commandInput = new CommandInput(args)
    val config = commandInput.fetchImageConfig

    assert(config.getOption("input") == List("dog_test.jpg"))
    assert(config.getOption("table") == List("bourke"))
  }

  test("CommandInput should correctly handle missing --table argument") {
    val args = Array("--image", "dog_test.jpg")
    val commandInput = new CommandInput(args)
    val config = commandInput.fetchImageConfig

    assert(config.getOption("table") == List("bourke"))
  }

  test("CommandInput should throw exception for invalid --scale argument") {
    val args = Array("--image", "dog_test.jpg", "--scale", "invalid")
    val commandInput = new CommandInput(args)

    val exception = intercept[IllegalArgumentException] {
      commandInput.fetchImageConfig
    }

    assert(exception.getMessage.contains("Invalid scaling factor. Provide a valid number"))
  }
}