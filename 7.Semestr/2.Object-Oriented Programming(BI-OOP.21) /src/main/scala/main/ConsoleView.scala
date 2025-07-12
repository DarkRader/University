package main

import controllers.ImageConsoleController
import input.InputSource

class ConsoleView(userInput: InputSource, imageController: ImageConsoleController) {
  private val configuration = userInput.fetchImageConfig

  def start(): Unit = {
    val rgbImage = imageController.loadImage(getSourcePath())
    val appliedFilters = extractFilters()
    val transformationTable = extractTableType()
    val asciiImage = imageController.processImage(rgbImage, appliedFilters, transformationTable)
    val exportModes = extractOutputModes()
    imageController.exportImage(asciiImage, exportModes)
  }

  private def extractFilters(): Map[String, Seq[String]] = {
    var filtersMap: Map[String, Seq[String]] = Map()
    val rotationFilter = "rotate"
    val flippingFilter = "flip"
    val scalingFilter = "scale"
    val invertFilter = "invert"

    if (configuration.containsOption(rotationFilter)) {
      filtersMap += (rotationFilter -> configuration.getOption(rotationFilter))
    }
    if (configuration.containsOption(flippingFilter)) {
      filtersMap += (flippingFilter -> configuration.getOption(flippingFilter))
    }
    if (configuration.containsOption(scalingFilter)) {
      filtersMap += (scalingFilter -> configuration.getOption(scalingFilter))
    }
    if (configuration.containsOption(invertFilter)) {
      filtersMap += (invertFilter -> configuration.getOption(invertFilter))
    }
    filtersMap
  }

  private def extractTableType(): String = {
    configuration.getOption("table").headOption.getOrElse("")
  }

  private def getSourcePath(): String = {
    configuration.getOption("input").headOption.getOrElse("")
  }

  private def extractOutputModes(): Map[String, String] = {
    var outputConfig: Map[String, String] = Map()
    val fileOutputMode = "outputFile"
    val consoleOutputMode = "outputStd"
    val outputPathMode = "outputPath"

    if (configuration.containsOption(fileOutputMode)) {
      outputConfig += fileOutputMode -> configuration.getOption(fileOutputMode).headOption.getOrElse("")
    }
    if (configuration.containsOption(consoleOutputMode)) {
      outputConfig += consoleOutputMode -> configuration.getOption(consoleOutputMode).headOption.getOrElse("")
    }
    if (configuration.containsOption(outputPathMode)) {
      outputConfig += outputPathMode -> configuration.getOption(outputPathMode).headOption.getOrElse("")
    }
    outputConfig
  }
}