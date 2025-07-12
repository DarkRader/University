# Semestral Project

## ASCII art

<link rel="stylesheet" href="../resources/custom.css"/>
<link rel="stylesheet" href="../resources/default.css"/>
<script src="../resources/highlight.pack.js"></script>
<script>hljs.initHighlightingOnLoad();</script>


The idea of this project is to load images, translate them into ASCII ART images, optionally apply filters, and save them. Something like this:

![Planet](ASCII-art-example-1.png)

It is also possible to lower the font-size, increase density, and create more detailed art:

![ASCII meme](ASCII-art-example-2.png)

## Application basics

The app will be a simple console-executable, that:

1. Loads an image
2. Translates the image into ASCII art
3. Applies filters if required – no filters by default
4. Outputs the image into an output (console, file, ...)

These steps are not necessarily how your application should work internally. It is just a high-level description to explain the process. You may approach the problem in a way you seem fit (for example, delay the image loading, etc.). However, the input and output of the application must remain the same – load an image and export an ASCII version of it, possibly with applied filters.

When inside the sbt shell (after running the `sbt` command), the `run` command can look like this:

``` plaintext
run --image "../images/test-image.jpg" --rotate +90 --scale 0.25 --invert --output-console
```

``` plaintext
run --image "test-image.jpg" --output-file "../outputs/output.txt"
```

``` plaintext
run --image "test-image.jpg" --rotate +90 --invert --output-file "../outputs/output.txt" --output-console --table "bourke-small"
```

## Grading

The project is separated into sections. To receive full points from each section, the student must implement the application using objects and propper object modeling. Usage of polymorphism, immutable objects, and common design patterns is expected, but not necessarily required – otherwise, students must defend their design decisions.

The applications' design and code should be clean, clear, and as readable as possible. Complicated and hard-to-understand methods/designs are not appreciated. Simplicity is valued. Do not over-engineer, but keep the application expandable and scalable.

Bonus challenges will have minimal impact on the resulting number of points. The focus should be mainly on the core required functionalities.

Testing is a big part of development. The student is expected to automate tests that will check the functionality of all major classes. Tests must be just as clean and clear as the rest of the application. This ensures that the application is functional and testable. **A section that is not properly tested will receive up to a 50 % point penalty.**

**The main focus of this semestral project is quality OOP design.** User interface and algorithms do not need to be perfect.

Please try not to write a lot of extra complicated designs and classes. More code means more space for errors. If you want to be sure you get a good amount of points, focus on the core functionalities, and do not get carried away with crazy ideas.

## Libraries and dependencies

<div class="admonition-block important">
  <p><strong>It is not allowed to use external libraries, except for testing.</strong></p>
</div>

*Note: It is recommended to use ImageIO to load images. Since ImageIO is from JDK, you can use it freely.*

## Testing – 50 %

**Each business feature/module of your application needs to be covered with unit tests.** Tests are worth 50 % of your points. **Test each module and class individually.**

**Multiple test cases for regular uses-cases and edge-cases are expected.**

Unit-tests for the following modules are **explicitly required**:

- Loading an image
- ASCII conversion
- Image filters
- Saving an image
- *Other business classes (controllers)*
- *Other modules you added*

Unit-tests for the following are **optional**:

- Console IO tests (view tests)

**System tests**, **integration tests** and other types of tests are also welcomed; however, they are **optional** (unlike very much-needed and essential unit tests).

**Do not underestimate the (points) value of testing.**

## Detailed description

### UI – 8 points

The application provides a user interface via the console. Feel free to handle application arguments in a way you think is the best and makes the most sense. All UI solutions that make some sort of sense for your solution will be accepted.

Some of the recommended and possible ways to handle arguments are:

- Ignore the order of arguments and handle operations in a pre-de$$fined order.
- Load all arguments one-by-one and process them all one-by-one in the inputted order.
- **The most recommended**: Read some arguments regardless of their order (load), but read and then execute all other arguments (filters, outputs) in their inputted order.

**It is expected that the UI part of the program will be handled in an OOP manner and well thought out.** Feel free to use any suitable pattern (MVC, MVP, MVVM) or make your own system.

### Load an image – 10 points

The application must always process an image. **The minimum requirement for receiving full points from this section is the support of at least two different formats and a random image generator.**

If one of the arguments is `--image-random`, the application will generate a random image. The process of generating an image is up to you. Use trivial randomness of pixels, a noise function of whatever your heart desires. Dimensions of the random image should be also random, but with reasonable limits.

At least one of the two required image formats must be either:

- jpg
- png
- gif

When specifying a concrete image, the path can be absolute or relative. The specific image is passed as an argument `--image "path"`. If a user uses unsupported extensions, he must be notified.

Only one `--image*` argument can be specified. If there is not exactly one `--image*` argument, the user must be notified.

It is expected that even tho libraries such as ImageIO can load various types of images without any setup, the student will at least check the image type and use appropriate tools. **Loading must be extendable, meaning it should be possible to easily add more loading sources, such as exotic file formats, network data, random image generation methods, and other various data sources.**

*Note: Avoid making a single universal file importer.*

*Note: The random generator must be deterministically testable.*

### ASCII conversion – 18 points

Any loaded image must be, at some point, translated into ASCII art. A simple and recommended method works as follows:

1. Load individual pixels in RGB (Red, Green, and Blue values in the 0-255 range).
2. Calculate each pixels greyscale value using the following formula: `greyscale value = ((0.3 * Red) + (0.59 * Green) + (0.11 * Blue))` ([explained on Tutorials Point](https://www.tutorialspoint.com/dip/grayscale_to_rgb_conversion.htm)).
3. Convert greyscale values into ASCII characters using a conversion table / algorithm. The result ASCII image must resemble its source image (at least slightly).

The minimum requirements for receiving full points from this section are:

- **The support of one linear transformation table**, for example, a [Paul Bourkes' table](http://paulbourke.net/dataformats/asciiart/). A linear transformation table is a table where the range of 255 greyscale values is equally divied between a set of ASCII characters (`255 / characterCount`).
- **The support for the user to manually set a linear table.**
- **The support of one non-linear transformation table**, where 255 greyscale values are divided un-equally. For example, one character is for values 0-200, and the rest is divided between 20 other characters. Feel free to be creative. Fry the image into oblivion if you need to.

**More tables and ASCII algorithms with arbitrary logic should be easily added if needed.**

The argument for setting a predefined table is `--table name`, where "name" is the name/identification of the predefined table. The argument for setting a user-defined table is `--custom-table characters`, where "characters" is a set of characters representing a linear scale (for example, `.:-=+*#%@`). If no conversion is explicitly defined, a default table is used – the default table is up to the student. Exactly one table should be used.

Note that **the pixel conversion is supposed to be one-to-one**, meaning one pixel translates into one character. You may notice that the resulting ASCII images have a different aspect ratio, but the currently used font probably causes that to display the text. If you want to fix this, make a filter that will correct the aspect ratio according to the most popular fonts and their letter aspect ratio. It is not mandatory tho.

Other more innovative conversion methods are welcomed as well.

**The ASCII conversion process should be easily modifiable and extendable.**

### Image filters – 10 points

The minimum requirement for receiving full points from this section is the support of **at least three different filters**. **The program can run with multiple filters at once, applied in series** (for example rotate, scale and rotate again).

**It should be possible to easily add more filters if needed.**

Filters can be:

#### Rotate

The rotate filter rotates the ASCII image. Rotations dividable by 90 degrees are mandatory, rotations by any number of degrees are a bonus challenge.

The rotate argument is `--rotate degrees` – "degrees" parameter can be for example: `+90`, `90` (same as `+90`), `-180`, ...

#### Scale

Scale filter scales the ASCII image. The filter should support scaling by `0.25`, `1`, and `4`, which looks as follows:

``` plaintext
Original / Scale 1: 
AB
CD

Scale 0.25 (take one of those 4 symbols or calculate average):
A

Scale 4:
AABB
AABB
CCDD
CCDD
```

Other scales are a bonus challenge. The scale arguments is `--scale value`.

#### Invert

Invert filter inverts the greyscale value of pixels. Inversion is done as follows:

`Inverted greyscale = white - greyscale`, where white is usually 255

The invert argument is `--invert`.

*Note: This operation must be done on a greyscale value, not individual RGB channels.*

#### Flip

Flip filter flips the image on "y" or "x" axes.

``` plaintext
Original: 
AB
CD

Flip on x-axes:
CD
AB

Flip on y-axes:
BA
DC
```

The flip argument can be `--flip x` or `--flip y`.

*Note: User can input both `--flip x` and `--flip y` at once.*

Bonus challenge: Flip on diagonal axes.

#### Brightness

The brightness filter changes the greyscale value of pixels without losing any precision. Brightness is changed as follows:

The brightness argument is `--brightness value` – "value" parameter can be for example: `+1`, `1` (same as `+1`), `-5`, ...

If a pixel brightness / greyscale value gets below 0, it should be considered as 0. If the brightness gets above 255, it should be considered as 255.

*Note: This operation must be done on a greyscale value, not individual RGB channels.*

#### Font aspect ratio

The aspect ratio filter changes the aspect ratio of the output image according to a font's aspect ratio.

Fonts usually do not have an aspect ratio of 1:1. They are usually higher, which means the resulting image will probably be stretched out vertically. This filter should fix that.

Using parameter `--font-aspect-ratio x:y`, where `x:y` is the aspect ratio of a font character. We presume the usage of a monospaced font (all letters have the same width).

*Note: This filter is definitely the hardest to make and is intended for people that want the ASCII conversion to look good.*

### Save an image – 6 points

The resulting image can be **saved to a file, printed in the console, or both**. Printing in the console is done using the `--output-console` argument and saving in a file is done using the `--output-file "path"` argument. The file path can be relative or absolute.

Whenever you print, you should print only the ASCII text. It is not necessary to convert the ASCII representation into image formats such as png, jpg, and so on. Simple *dump* into a txt file is good enough, even preferred! An important property of ASCII art is that it's just a text.

**It should be possible to easily add more save targets, such as email, HTTP POST, and more.**
