package `export`

import java.io.OutputStream

class TextStreamExport(destinationStream: OutputStream) extends TextExport {
  private var isClosed = false

  private def writeToStream(content: String): Unit = {
    if (isClosed)
      throw new IllegalStateException("The stream has already been closed.")

    val bytes = content.getBytes("UTF-8")
    destinationStream.write(bytes)
    destinationStream.flush()
  }

  def closeStream(): Unit = {
    if (!isClosed) {
      destinationStream.close()
      isClosed = true
    }
  }

  override def show(content: String): Unit = writeToStream(content)
}