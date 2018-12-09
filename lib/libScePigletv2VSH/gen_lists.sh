#!/bin/sh

out_file=libScePigletv2VSH.def

echo "fun:" > $out_file

./preprocess_hdr.py ../../include/GLES2/gl2.h >> $out_file
echo >> $out_file

./preprocess_hdr.py ../../include/GLES2/gl2ext.h >> $out_file
echo >> $out_file

./preprocess_hdr.py ../../include/EGL/egl.h >> $out_file
echo >> $out_file

./preprocess_hdr.py ../../include/EGL/eglext.h >> $out_file
echo >> $out_file

echo "scePigletSetConfigurationVSH" >> $out_file

echo "eglPigletMemoryInfoSCE"  >> $out_file

echo "glOrbisTexImageCanvas2DSCE" >> $out_file
echo "glOrbisTexImageResourceSCE" >> $out_file
echo "glOrbisMapTextureResourceSCE" >> $out_file
echo "glOrbisUnmapTextureResourceSCE" >> $out_file

echo "glPigletGetShaderBinarySCE" >> $out_file
