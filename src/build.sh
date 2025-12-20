#!/bin/sh -x

B2D_INC="-I$(brew --prefix box2d)/include/"
B2D_LIB="-L$(brew --prefix box2d)/lib/ -lbox2d"

FLTK_INC="-I$(brew --prefix fltk)/include"
FLTK_LIB="-L$(brew --prefix fltk)/lib -lfltk"

OPENGL_LIB="-framework OpenGL -lfltk_gl"

for i in *.cpp; do
c++ -c ${i} -std=c++2c ${B2D_INC} ${FLTK_INC}
done

c++ *.o -o dice_roll ${B2D_LIB} ${FLTK_LIB} ${OPENGL_LIB}
