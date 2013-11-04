# OBJViewer

## Stupid viewer for obj files

This project was developed as part of a Computer Graphics class assignment.

It loads obj files - along with referenced materials and ppm textures and
displays the described model, with some basic vertex/face editing capabilities.
It doens't play well if you obj/mtl files are not formated properly, so you may
run into problems. It also segfaults randomly sometimes when starting up, so be
aware of that.

This app was developed using OpenGL 2 and GLUT. I don't do CMake, so the
Makefile works for OS X only; if you want to run it on linux you have to change
OpenGL/GLUT include directives accordingly.

## License

Everything MIT'd. Check [LICENSE.md](LICENSE.md) for more info.
