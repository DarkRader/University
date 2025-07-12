package load

import models.Image

trait LoadImage[T <: Image[?]] extends Load[Image[?]] {
  def load(path: String): T
}