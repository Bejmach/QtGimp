# gimpRipofQtCompatibility

## Table of content
* [General info](#General-info)
* [Qt frontend](#Qt-frontend)
* [Cpp backend](#Cpp-backend)

### General info
Program is made from frontend in Qt, and backend written in pure cpp. backend supports image, layers, layer filters, pixels, and colors(RGB, HSV, HSI(this one is broken)). Frontend supports most of backend functions(with some exceptions).

### Qt frontend

#### File
![File](https://github.com/user-attachments/assets/d3827b23-ff30-4b67-973e-b373a7d4bb3d)
* open - select a file from disc and open it(supports ppm p3 and p6)
* save - saves selected file(supports ppm p3), remember to provide file extension(.ppm) in name of file
* cloce - closes all layers and leaves empty canvas

#### Image
![Image](https://github.com/user-attachments/assets/2e46ff10-2d01-45b5-a850-4d58e85b2a88)
* Resize to content - resize image to layer content

#### Effects
![Color](https://github.com/user-attachments/assets/5f341404-ff27-4b5d-b18c-9a6a1f97668f)
![Outline](https://github.com/user-attachments/assets/d14882c4-de2d-4bb8-ba9f-20476209bc66)
![Random](https://github.com/user-attachments/assets/555a0c26-2cfd-498d-8c5d-35380ccc29e6)
![Blur](https://github.com/user-attachments/assets/26642423-100b-461b-bc35-5c807ced50a0)
![Experimental](https://github.com/user-attachments/assets/293ddad6-e758-4d56-b15a-b8c51b9d7591)
![Sharpening](https://github.com/user-attachments/assets/b320609d-c459-477a-b484-4e39e35dbd75)

#### Effects ui
![Empty](https://github.com/user-attachments/assets/33cedc7d-c062-4699-bf5c-c51b5cfbd375)
![Double](https://github.com/user-attachments/assets/919c3f07-fce4-4379-968d-6adb2b147d60)
![Gaussian](https://github.com/user-attachments/assets/4c3d3488-f412-410d-8d97-752ec3b27672)
![Graph](https://github.com/user-attachments/assets/c572a4fb-8294-4fa6-acd7-d5a2d06e2192)



### Cpp backend
* Color - (RGB, HSV, HSI(broken))
* Pixel - RGB(the only one important)
* Layer - ***Pixel
* Image - *Layer
* LayerEditor - LE::Effect(Image*)
