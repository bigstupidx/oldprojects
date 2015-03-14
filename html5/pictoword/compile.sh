cocos compile -p web -m release --advanced

rm -rf publish/html5/libs
mkdir publish/html5/libs
cp -r ./libs publish/html5/

rm -rf publish/html5/txt
mkdir publish/html5/txt
cp -r ./txt publish/html5/

cp ./index-local.html ./publish/html5/index.html