2011/01/04 ido追記

概要
====

カメラキャプチャサンプルRTC

コンパイル＆実行方法
term1$ sudo apt-get install libcv-dev libcvaux-dev
term1$ tar jxvf VideoStreamRTC.tar.bz2
term1$ cd ./VideoStreamRTC
term1$ ./make.sh
term1$ ./exec.sh

term2$ cd ./VideoStreamRTC
term2$ ./sample.py


動作
=====

- ひとまず、/opt/grx/include/rtm/idl/InterfaceDataTypes.idl で定義されているMultiCameraImagesを利用
- VideoStream.conf
  camera_dev_id:0,1
  を修正する事で、取り扱うカメラの数を変更する．
  camera_type:uEye
  camera_type:uvc
  は，それぞれカメラの種類を指定している．
  頭部カメラは uEye，手先カメラは uvc を指定する．
  sample.py は，デフォルトで10秒間の連続キャプチャを行う．

- captureコマンド
  -- capture(-1)：キャプチャ開始
  -- capture(0)：キャプチャ終了
  -- capture(n>0)：n回キャプチャ


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

