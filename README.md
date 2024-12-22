# gimpRipofQtCompatibility

## Table of content
* [General info](#General-info)
* [Qt frontend](#Qt-frontend)
* [Cpp backend](#Cpp-backend)

### General info
Program is made from frontend in Qt, and backend written in pure cpp. backend supports image, layers, layer filters, pixels, and colors(RGB, HSV, HSI(this one is broken)). Frontend supports most of backend functions(with some exceptions).

### Qt frontend

#### File
!(File)[/Screenshots/File.png]
* open - select a file from disc and open it(supports ppm p3 and p6)
* save - saves selected file(supports ppm p3), remember to provide file extension(.ppm) in name of file
* cloce - closes all layers and leaves empty canvas

#### Image
!(Image)[/Screenshots/Image.png]
* Resize to content - resize image to layer content

#### Effects
!(Color)[/Screenshots/Color.png]
!(Outline)[/Screenshots/Outline.png]
!(Random)[/Screenshots/Random.png]
!(Blur)[/Screenshots/Blur.png]
!(Experimental)[/Screenshots/Experimental.png]
!(Sharpening)[/Screenshots/Sharpening.png]


### Cpp backend
* Color - (RGB, HSV, HSI(broken))
* Pixel - RGB(the only one important)
* Layer - ***Pixel
* Image - *Layer
* LayerEditor - LE::Effect(Image*)
