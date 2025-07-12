package `export`

import java.io.{File, FileOutputStream}

class FileExport(file: File) extends TextStreamExport(new FileOutputStream(file))