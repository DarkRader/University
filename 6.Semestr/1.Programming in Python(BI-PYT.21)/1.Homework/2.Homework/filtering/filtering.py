"""My program"""
import numpy as np


def apply_filter(image: np.array, kernel: np.array) -> np.array:
    """
    Apply given filter on image
    :param image: The input image on which we want to perform the convolution
    :param kernel: Kernel, which we'll be running with the image
    :return: Aray our filtered picture
    """
    # A given image has to have either 2 (grayscale) or 3 (RGB) dimensions
    assert image.ndim in [2, 3]
    # A given filter has to be 2 dimensional and square
    assert kernel.ndim == 2
    assert kernel.shape[0] == kernel.shape[1]

    image_height = image.shape[0]
    image_width = image.shape[1]
    kernel_size = kernel.shape[0]
    kernel_to_center_size = kernel_size // 2

    if image.ndim == 3:
        pad_image = np.pad(image, ((kernel_to_center_size, kernel_to_center_size),
                                   (kernel_to_center_size, kernel_to_center_size), (0, 0)), mode='constant')
    else:
        pad_image = np.pad(image, kernel_to_center_size, mode='constant')

    result_image = np.zeros_like(image)

    for y in range(image_height):
        for x in range(image_width):

            if image.ndim == 3:
                neighbor = pad_image[y:y + kernel_size, x:x + kernel_size, :]
            else:
                neighbor = pad_image[y:y + kernel_size, x:x + kernel_size]

            if image.ndim == 3:
                conv_values = np.sum(neighbor * kernel[:, :, np.newaxis], axis=(0, 1))
            else:
                conv_values = np.sum(neighbor * kernel)

            conv_values = np.clip(conv_values, 0, 255)

            if image.ndim == 3:
                result_image[y, x, :] = conv_values
            else:
                result_image[y, x] = conv_values

    return result_image
