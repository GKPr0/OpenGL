## SimpleEngine
This project contains simple 3D engine and exmaple application using it.
It is written in C++ and uses OpenGL.

- Features
  - 3D models loading and rendering (OBJ format)
  - Textures (supports transparent textures)
  - Shaders (verteg and fragment shaders)
  - Camera 
  - Point lights and directional lights
  - User input (keyboard and mouse)
  - User-object coliision detection
  - Simple audio (using build in windows audio library)
  - Simple particle system


### Example application
- Controls 
  - WSAD movement
  - Mouse wheel changes FOV
  - Mouse movement changes camera direction
  - R turn on/off flashlights
  - F changes window to fullscreen
  - ESC closes application

## SimpleTracker
This project contains simple object tracking application which marks center of object (HSV color based) with red cross.
It is written in C++ as multithreaded app and uses OpenCV.
One thread reads video from camera and processes it.
Second thread renders processed video.

## Build
- Requires opencv 4.6.0
- Requires system property called OPENCV_DIR pointing to /build opencv folder (ie. C:\opencv\build).
- Requires %OPENCV_DIR%\x64\vc15\bin in PATH.
- Other dependencies are included as part of the projects.
- If failed to run with message about missing glew32.dll or glfw3.dll, copy them from SipleEngine/bin to OpenGl/x64/{Debug/Release}