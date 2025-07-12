package unit

import `export`._
import org.scalatest.funsuite.AnyFunSuite
import java.io.{File, ByteArrayOutputStream}

class ExportTest extends AnyFunSuite {

  test("FileExport should correctly write to a file") {
    val filePath = "./test_output.txt"
    val file = new File(filePath)

    if (file.exists()) {
      file.delete()
    }

    val fileExport = new FileExport(file)

    val testContent = "This is a file test."
    fileExport.show(testContent)

    val fileContent = scala.io.Source.fromFile(filePath).getLines.mkString
    assert(fileContent == testContent)

    file.delete()
  }

  test("TextStreamExport should throw an exception if the stream is closed") {
    val outputStream = new ByteArrayOutputStream()
    val textStreamExport = new TextStreamExport(outputStream)

    textStreamExport.closeStream()

    val exception = intercept[IllegalStateException] {
      textStreamExport.show("This should fail")
    }

    assert(exception.getMessage == "The stream has already been closed.")
  }

  test("TextStreamExport should correctly write to the stream") {
    val outputStream = new ByteArrayOutputStream()
    val textStreamExport = new TextStreamExport(outputStream)

    val testContent = "Test content for TextStreamExport"
    textStreamExport.show(testContent)

    assert(new String(outputStream.toByteArray) == testContent)
  }
}