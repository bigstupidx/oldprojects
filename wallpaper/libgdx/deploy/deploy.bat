call mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx ^
-DartifactId=gdx ^
-Dversion=1.0.1 ^
-Dpackaging=jar ^
-Dfile=./gdx-1.0.1.jar ^
-DrepositoryId=myRepository ^
-Durl=file://c://temp-repository

call mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx ^
-DartifactId=gdx ^
-Dversion=1.0.0 ^
-Dpackaging=jar ^
-Dfile=./gdx-1.0.0.jar ^
-DrepositoryId=myRepository ^
-Durl=file://c://temp-repository

call mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx ^
-DartifactId=gdx ^
-Dversion=1.0.1 ^
-Dpackaging=java-source ^
-Dfile=./gdx-1.0.1-sources.jar ^
-DrepositoryId=myRepository ^
-Durl=file://c://temp-repository ^
-DgeneratePom=false

call mvn deploy:deploy-file -DgroupId=com.badlogicgames.gdx ^
-DartifactId=gdx ^
-Dversion=1.0.0 ^
-Dpackaging=java-source ^
-Dfile=./gdx-1.0.0-sources.jar ^
-DrepositoryId=myRepository ^
-Durl=file://c://temp-repository ^
-DgeneratePom=false

call mvn deploy:deploy-file -DgroupId=aurelienribon.tweenengine ^
-DartifactId=tweenengine ^
-Dversion=6.3.3 ^
-Dpackaging=jar ^
-Dfile=./tween-engine-6.3.3.jar ^
-DrepositoryId=myRepository ^
-Durl=file://c://temp-repository

call mvn deploy:deploy-file -DgroupId=aurelienribon.tweenengine ^
-DartifactId=tweenengine ^
-Dversion=6.3.3 ^
-Dpackaging=java-source ^
-Dfile=./tween-engine-6.3.3-sources.jar ^
-DrepositoryId=myRepository ^
-Durl=file://c://temp-repository ^
-DgeneratePom=false

call mvn deploy:deploy-file -DgroupId=com.umeng.sdk ^
-DartifactId=analytics ^
-Dversion=5.2.2 ^
-Dpackaging=jar ^
-Dfile=./umeng-sdk-analytics-5.2.2.jar ^
-DrepositoryId=myRepository ^
-Durl=file://c://temp-repository