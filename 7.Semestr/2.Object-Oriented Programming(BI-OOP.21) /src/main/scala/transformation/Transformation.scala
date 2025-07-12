package transformation

import models.{Image, Pixel}

trait Transformation[A <: Image[T], B <: Image[D], T <: Pixel, D <: Pixel] {
  def applyTransformation(image:  A): B
}