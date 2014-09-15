#!/bin/sh
version=1.0.1

libgdx_home=/home/kof/libgdx

#armeabi
platform=armeabi
rm -rf ./$platform
rm -rf ./gdx-platform-$version-natives-$platform.jar
cp -r $libgdx_home/dist/$platform/ .
cd $platform
jar cf gdx-platform-$version-natives-$platform.jar ./libgdx.so 
cd ..
mv ./$platform/gdx-platform-$version-natives-$platform.jar .

#armeabi-v7a
platform=armeabi-v7a
rm -rf ./$platform
rm -rf ./gdx-platform-$version-natives-$platform.jar
cp -r $libgdx_home/dist/$platform .
cd $platform
jar cf gdx-platform-$version-natives-$platform.jar ./libgdx.so 
cd ..
mv ./$platform/gdx-platform-$version-natives-$platform.jar .

#x86
platform=x86
rm -rf ./$platform
rm -rf ./gdx-platform-$version-natives-$platform.jar
cp -r $libgdx_home/dist/$platform .
cd $platform
jar cf gdx-platform-$version-natives-$platform.jar ./libgdx.so 
cd ..
mv ./$platform/gdx-platform-$version-natives-$platform.jar .
