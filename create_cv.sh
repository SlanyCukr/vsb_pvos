#!/bin/bash
folder_name="cv_"$1

mkdir $folder_name
cp Makefile $folder_name/Makefile
cp main.cpp $folder_name/main.cpp
cd $folder_name

code .
