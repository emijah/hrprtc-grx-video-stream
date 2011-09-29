2011/01/04 ido追記

概要
====

カメラキャプチャサンプルRTC

ソースコード取得方法
google codeリポジトリから以下のコマンドによりチェックアウトします。
 term$ hg clone https://code.google.com/p/hrprtc-grx-video-stream/ 

ソースコードアップデート方法
上記ソースコード取得方法で再度取得しなおすか、
以下の方法でアップデートして下さい。
チェックアウト後(clone後)は、以下の手順で更新できます。
 term$ cd hrprtc-grx-video-stream
 term$ hg pull 
 term$ hg update -C
-Cはローカルでコードを修正している場合に必要になります。

リポジトリはmercurialというバージョン管理システムを利用しております。
詳しい利用方法はmercurialのサイトをご覧下さい。
 http://mercurial.selenic.com/wiki/JapaneseTutorial


コンパイル＆実行方法
 term1$ sudo apt-get install libcv-dev libcvaux-dev
 term1$ cd hrprtc-grx-video-stream
 term1$ ./make.sh
 term1$ ./exec.sh

 term2$ cd hrprtc-grx-video-stream
 term2$ ./sample.py


動作
=====

- VideoStream.conf
  camera_dev_id:0,1
  を修正する事で、取り扱うカメラの数を変更する．
  camera_type:uEye
  camera_type:uvc
  は，それぞれカメラの種類を指定している．
  頭部カメラは uEye，手先カメラは uvc を指定する．
  sample.py は，デフォルトで10秒間の連続キャプチャを行う．

- captureコマンド
  -- take_one_frame() : 静止画をoutportに出力する


注意事項
========

頭部カメラは，
camera_dev_id:0,1
という様に，2台のカメラを同時にキャプチャすることが可能だが，
手先カメラではこれができないので，
camera_dev_id:0
または
camera_dev_id:1
という様に，1台ずつキャプチャする必要がある．

