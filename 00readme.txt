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

 頭部カメラを起動する場合
 term1$ ./exec_head.sh


動作
=====

- VideoStream.conf (手先カメラ用設定ファイル)
   camera_type:uvc
   camera_dev_id:0
  
 *usbインタフェースボードを追加した場合は２つ同時に利用可能。
  その場合はcamera_dev_idを以下のように指定する。
   camera_dev_id:0

- VideoStream_head.conf (頭部カメラ用設定ファイル)
  camera_type:uEye
  camera_dev_id:0
  #camera_dev_id:0,0
  #camera_dev_id:1,2

 *インストール直後はcamera id が全て1のままであり、camera_dev_idには0しか指定できない。
　2つ同時に利用する場合は0,0と指定する。
  QuEyeCameraManagerによりidは変更可能。
  ueyeカメラドライバのreadmeにあるueyesetidはモニタ機能しかつかえない(ver3.7にて確認)。
  <<ueyesetid の実行例>>
  vision@VisionPC$ ueyesetid -d
  libueye_api.so Version 3.71.0002
  uEye camera list dump
  2 devices found
  +------+----------+---------+--------+----------------------+--------------+
  |Device|Device id |Camera id| in use |    Camera Model      |  Serial No.  |
  +------+----------+---------+--------+----------------------+--------------+
  |   1  |      1   |    1    |   no   | UI155xSE-C           | 4002778200   |
  |   2  |      2   |    2    |   no   | UI155xSE-C           | 4002778199   |
  +------+----------+---------+--------+----------------------+--------------+

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

