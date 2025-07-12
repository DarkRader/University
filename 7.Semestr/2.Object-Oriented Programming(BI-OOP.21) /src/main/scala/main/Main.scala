package main

import controllers.ImageConsoleController
import input.CommandInput
import load.LoadFileImage

object Main {
  def main(args: Array[String]): Unit = {
    val loader = new LoadFileImage()
    val input = new CommandInput(args)
    val controller = new ImageConsoleController(loader)
    val view = new ConsoleView(input, controller)
    view.start()
  }
}

