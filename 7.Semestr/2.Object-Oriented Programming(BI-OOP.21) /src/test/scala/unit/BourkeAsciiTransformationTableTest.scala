package unit

import models.{Ascii, GreyScale}
import table.BourkeAsciiTransformationTable
import org.scalatest.funsuite.AnyFunSuite

class BourkeAsciiTransformationTableTest extends AnyFunSuite {

  test("BourkeAsciiTransformationTable should map low brightness to the first character") {
    val transformationTable = new BourkeAsciiTransformationTable()
    val inputPixel = GreyScale(0)
    val outputAscii = transformationTable.transformPixel(inputPixel)

    assert(outputAscii == Ascii(' '))
  }

  test("BourkeAsciiTransformationTable should map maximum brightness to the last character") {
    val transformationTable = new BourkeAsciiTransformationTable()
    val inputPixel = GreyScale(255)
    val outputAscii = transformationTable.transformPixel(inputPixel)

    assert(outputAscii == Ascii('@'))
  }

  test("BourkeAsciiTransformationTable should map mid-range brightness correctly") {
    val transformationTable = new BourkeAsciiTransformationTable()
    val inputPixel = GreyScale(128)
    val outputAscii = transformationTable.transformPixel(inputPixel)

    assert(outputAscii.value == '=')
  }

  test("BourkeAsciiTransformationTable should handle brightness values near boundaries") {
    val transformationTable = new BourkeAsciiTransformationTable()

    val lowPixel = GreyScale(10)
    val lowAscii = transformationTable.transformPixel(lowPixel)
    assert(lowAscii.value == ' ')

    val highPixel = GreyScale(245)
    val highAscii = transformationTable.transformPixel(highPixel)
    assert(highAscii.value == '%')
  }

  test("BourkeAsciiTransformationTable should correctly handle non-standard brightness values") {
    val transformationTable = new BourkeAsciiTransformationTable()

    val highValuePixel = GreyScale(300)
    val outputAscii = transformationTable.transformPixel(highValuePixel)

    assert(outputAscii.value == '@')
  }
}