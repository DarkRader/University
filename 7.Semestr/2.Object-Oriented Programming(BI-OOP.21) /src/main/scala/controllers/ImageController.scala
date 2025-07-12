package controllers

import filter.{ImageRotationFilter, GreyScaleMirrorFilter, GreyScaleNegativeFilter, GreyScaleResizingFilter, ImageFilter}
import models.{GreyScaleImage, GreyScale}
import transformation.{ContrastAdjustment, GreyscaleConversion, PixelProcessor}
import table.{BourkeAsciiTransformationTable, ImageTableTransformation}

class ImageController {

  def retrieveImageFilters(filterParams: Map[String, Seq[String]]): Seq[ImageFilter[GreyScaleImage, GreyScale]] = {
    var appliedFilters = Seq.empty[ImageFilter[GreyScaleImage, GreyScale]]

    filterParams.foreach {
      case ("rotate", angles) =>
        angles.foreach(rotation => appliedFilters :+= new ImageRotationFilter(rotation.toDouble))
      case ("scale", scalingFactors) =>
        scalingFactors.foreach(factor => appliedFilters :+= new GreyScaleResizingFilter(factor.toDouble))
      case ("invert", _) =>
        appliedFilters :+= new GreyScaleNegativeFilter()
      case ("flip", directions) =>
        directions.foreach(direction => appliedFilters :+= new GreyScaleMirrorFilter(direction))
      case _ => // Ignore unknown filter types
    }

    appliedFilters
  }

  def retrieveImageOperations(): Seq[PixelProcessor] = {
    Seq(
      new ContrastAdjustment(1.2),
      new GreyscaleConversion()
    )
  }

  def selectTransformationTable(tableType: String): ImageTableTransformation = {
    tableType match {
      case "bourke" => new BourkeAsciiTransformationTable
      case _        => new BourkeAsciiTransformationTable 
    }
  }
}