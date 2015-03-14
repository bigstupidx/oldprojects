call cocos compile -p web -m release --advanced

call rd publish\html5\libs /s /q
call md publish\html5\libs
call xcopy .\libs publish\html5\libs\

call rd publish\html5\txt /s /q
call md publish\html5\txt
call xcopy .\txt publish\html5\txt\

call copy .\index-local.html .\publish\html5\index.html