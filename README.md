# TUIOReceiverAndSend
外部から受け取ったTUIOのバンドルを加工して、新たなOSCのメッセージとして送信する
また、TuioCursorのみを受信するようになっています。
送られるOSCのメッセージは以下の内容である。

/fillter/tuio add SessionID X Y
/fillter/tuio update SessionID X Y
/fillter/tuio remove SessionID
