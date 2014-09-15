#!/bin/sh

mvn deploy:deploy-file -DgroupId=aurelienribon.tweenengine \
-DartifactId=tweenengine \
-Dversion=6.3.3 \
-Dpackaging=jar \
-Dfile=./tween-engine-6.3.3.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository

mvn deploy:deploy-file -DgroupId=aurelienribon.tweenengine \
-DartifactId=tweenengine \
-Dversion=6.3.3 \
-Dpackaging=java-source \
-Dfile=./tween-engine-6.3.3-sources.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DgeneratePom=false

mvn deploy:deploy-file -DgroupId=com.umeng.sdk \
-DartifactId=analytics \
-Dversion=5.2.2 \
-Dpackaging=jar \
-Dfile=./umeng-sdk-analytics-5.2.2.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository

version=1.0.0

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx \
-Dversion=$version \
-Dpackaging=jar \
-Dfile=./gdx-$version.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx \
-Dversion=$version \
-Dpackaging=java-source \
-Dfile=./gdx-$version-sources.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DgeneratePom=false

version=1.0.1

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx-platform \
-Dversion=$version \
-Dpackaging=jar \
-Dfile=./gdx-platform-$version.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DpomFile=./gdx-platform-$version.pom

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx-platform \
-Dversion=$version \
-Dclassifier=natives-armeabi \
-Dpackaging=jar \
-Dfile=./gdx-platform-$version-natives-armeabi.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DgeneratePom=false

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx-platform \
-Dversion=$version \
-Dclassifier=natives-armeabi-v7a \
-Dpackaging=jar \
-Dfile=./gdx-platform-$version-natives-armeabi-v7a.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DgeneratePom=false

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx-platform \
-Dversion=$version \
-Dclassifier=natives-x86 \
-Dpackaging=jar \
-Dfile=./gdx-platform-$version-natives-x86.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DgeneratePom=false

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx-platform \
-Dversion=$version \
-Dclassifier=natives-desktop \
-Dpackaging=jar \
-Dfile=./gdx-platform-$version-natives-desktop.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DgeneratePom=false

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx-platform \
-Dversion=$version \
-Dclassifier=natives-ios \
-Dpackaging=jar \
-Dfile=./gdx-platform-$version-natives-ios.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DgeneratePom=false

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx \
-Dversion=$version \
-Dpackaging=jar \
-Dfile=./gdx-$version.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository

mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx \
-DartifactId=gdx \
-Dversion=$version \
-Dpackaging=java-source \
-Dfile=./gdx-$version-sources.jar \
-DrepositoryId=myRepository \
-Durl=file:./temp-repository \
-DgeneratePom=false

#beyond compare
bcompare ./temp-repository /home/kof/maven-libgdx