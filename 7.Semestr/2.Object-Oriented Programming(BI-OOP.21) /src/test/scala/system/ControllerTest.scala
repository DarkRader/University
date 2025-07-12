package system

import controllers.{ImageConsoleController, ImageController}
import filter.{GreyScaleMirrorFilter, GreyScaleNegativeFilter, GreyScaleResizingFilter, ImageRotationFilter}
import load.LoadFileImage
import models.{Ascii, AsciiImage, GreyScale, GreyScaleImage}
import org.scalatest.funsuite.AnyFunSuite
import table.BourkeAsciiTransformationTable
import transformation.{ContrastAdjustment, GreyscaleConversion}

import java.io.File

class ControllerTest extends AnyFunSuite {

  test("ImageController should retrieve filters correctly") {
    val controller = new ImageController()

    val filterParams = Map(
      "rotate" -> Seq("90"),
      "scale" -> Seq("2.0"),
      "invert" -> Seq(),
      "flip" -> Seq("x", "y")
    )

    val filters = controller.retrieveImageFilters(filterParams)
    assert(filters.length == 5)
    assert(filters.exists(_.isInstanceOf[ImageRotationFilter]))
    assert(filters.exists(_.isInstanceOf[GreyScaleResizingFilter]))
    assert(filters.exists(_.isInstanceOf[GreyScaleNegativeFilter]))
    assert(filters.count(_.isInstanceOf[GreyScaleMirrorFilter]) == 2)
  }

  test("ImageController should retrieve operations correctly") {
    val controller = new ImageController()
    val operations = controller.retrieveImageOperations()

    assert(operations.length == 2)
    assert(operations.exists(_.isInstanceOf[ContrastAdjustment]))
    assert(operations.exists(_.isInstanceOf[GreyscaleConversion]))
  }

  test("ImageController should select the correct transformation table") {
    val controller = new ImageController()
    val bourkeTable = controller.selectTransformationTable("bourke")

    assert(bourkeTable.isInstanceOf[BourkeAsciiTransformationTable])
  }

  test("ImageController should select the default table for unknown type") {
    val controller = new ImageController()
    val defaultTable = controller.selectTransformationTable("unknown")

    assert(defaultTable.isInstanceOf[BourkeAsciiTransformationTable])
  }

  test("ImageConsoleController should export image to console and file") {
    val loader = new LoadFileImage()
    val asciiImage = new AsciiImage(2, 2)
    asciiImage.setPixel(0, 0, Ascii('A'))
    asciiImage.setPixel(1, 0, Ascii('B'))
    asciiImage.setPixel(0, 1, Ascii('C'))
    asciiImage.setPixel(1, 1, Ascii('D'))

    val controller = new ImageConsoleController(loader)

    val filePath = "./output.txt"
    val outputModes = Map("outputFile" -> "file", "outputPath" -> filePath, "outputStd" -> "std")

    controller.exportImage(asciiImage, outputModes)

    val fileContent = scala.io.Source.fromFile(filePath).getLines.mkString("\n")
    assert(fileContent == "AB\nCD")

    new File(filePath).delete()
  }
}