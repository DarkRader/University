package controllers

import models.{AsciiImage, GreyScaleImage, RGBImage}
import transformation.{GreyScaleToAsciiTransform, RGBToGreyScaleTransform}
import pages.AsciiExportPage
import `export`.{ConsoleExport, FileExport, TextExport}
import load.LoadFileImage

import java.io.File

class ImageConsoleController(loaderInstance: LoadFileImage) {

  def loadImage(filePath: String): RGBImage = loaderInstance.load(filePath)

  def processImage(image: RGBImage, filterParams: Map[String, Seq[String]], tableType: String): AsciiImage = {
    val greyImage = convertToGreyScale(image)
    val processedImage = applyImageOperations(greyImage)
    val filteredImage = applyImageFilters(processedImage, filterParams)
    transformUsingTable(filteredImage, tableType)
  }

  def exportImage(image: AsciiImage, outputMode: Map[String, String]): Unit = {
    val pageRenderer = new AsciiExportPage(image)
    val outputModes = determineExportModes(outputMode)
    val renderedImage = pageRenderer.display()
    outputModes.foreach { exporter => exporter.show(renderedImage) }
  }

  private def convertToGreyScale(image: RGBImage): GreyScaleImage = {
    val greyScaleTransformer = new RGBToGreyScaleTransform()
    greyScaleTransformer.applyTransformation(image)
  }

  private def applyImageOperations(image: GreyScaleImage): GreyScaleImage = {
    val operationController = new ImageController
    val operationsList = operationController.retrieveImageOperations()
    operationsList.foldLeft(image) { (currentImage, operation) => operation.apply(currentImage) }
  }

  private def applyImageFilters(image: GreyScaleImage, filters: Map[String, Seq[String]]): GreyScaleImage = {
    val filterController = new ImageController
    val applicableFilters = filterController.retrieveImageFilters(filters)
    if (applicableFilters.nonEmpty) {
      applicableFilters.foldLeft(image) { (currentImage, filter) => filter.apply(currentImage) }
    } else {
      image
    }
  }

  private def transformUsingTable(image: GreyScaleImage, table: String): AsciiImage = {
    val tableController = new ImageController
    val transformationTable = tableController.selectTransformationTable(table)
    val asciiTransformer = new GreyScaleToAsciiTransform(transformationTable)
    asciiTransformer.applyTransformation(image)
  }

  private def determineExportModes(modeConfig: Map[String, String]): Seq[TextExport] = {
    val outputPath = modeConfig.getOrElse("outputPath", "")
    modeConfig.collect {
      case ("outputFile", _) if outputPath.nonEmpty =>
        new FileExport(new File(outputPath))
      case ("outputStd", _) =>
        new ConsoleExport
    }.toSeq
  }
}