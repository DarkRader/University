package system

import main.Main
import org.scalatest.funsuite.AnyFunSuite


class MainTest extends AnyFunSuite {
  test("Comprehensive tests for multiple image transformations for jpg format"){
    val imageFormat = "jpg"
    val rotateDegree = List(" ", "90", "180", "270", "360",
      "-90", "-180", "-270", "-360", "+90", "+270")
    for (index <- 1 to 10) {
      val sourceImagePath = s"src/test/scala/images/$imageFormat/test$index.$imageFormat"
      val outputAsciiPath = s"src/test/scala/images/$imageFormat/result/test$index.txt"
      val arguments =
        if (index % 2 == 0) {
          Array("--image", sourceImagePath, "--output-file", outputAsciiPath, "--invert", "--rotate", rotateDegree(index), "--scale", "0.25")
        } else {
          Array("--image", sourceImagePath, "--output-file", outputAsciiPath, "--rotate", rotateDegree(index), "--scale", "1")
        }
      Main.main(arguments)
    }
  }

  test("Comprehensive tests for multiple image transformations for png format") {
    val imageFormat = "png"
    for (index <- 1 to 10) {
      val sourceImagePath = s"src/test/scala/images/$imageFormat/test$index.$imageFormat"
      val outputAsciiPath = s"src/test/scala/images/$imageFormat/result/test$index.txt"
      val arguments =
        if (index % 2 == 0) {
          Array("--image", sourceImagePath, "--output-file", outputAsciiPath, "--scale", "0.25", "--flip", "x")
        } else {
          Array("--image", sourceImagePath, "--output-file", outputAsciiPath, "--scale", "0.25", "--flip", "y")
        }
      Main.main(arguments)
    }
  }

  test("Comprehensive tests for multiple image transformations for jpeg format") {
    val imageFormat = "jpeg"
    for (index <- 1 to 10) {
      val sourceImagePath = s"src/test/scala/images/$imageFormat/test$index.$imageFormat"
      val outputAsciiPath = s"src/test/scala/images/$imageFormat/result/test$index.txt"
      val arguments =
        if (index % 2 == 0) {
          Array("--image", sourceImagePath, "--output-file", outputAsciiPath, "--invert")
        } else {
          Array("--image", sourceImagePath, "--output-file", outputAsciiPath, "--scale", "4", "--invert")
        }
      Main.main(arguments)
    }
  }
}