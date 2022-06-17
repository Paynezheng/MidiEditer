# Debug Note

bug日志

## 2022/6/16

卡片3处理midi过后产生大量16分音符
时间: 2022-06-16 15:35 以上命令执行开始结束时间差(毫秒) 38
场景:

```shell
sudo /var/www/apps/MidiEditer/bin/Conventer /var/www/tomcat/upload_server/file/melody_1655364953.mid 3 
0
sudo /var/www/apps/MidiEditer/bin/ConventerSetBPM /var/www/tomcat/upload_server/file/melody_1655364953.mid 3 60
0
```

原因:

* 代码中第三个参数使用1表示八分音符量化, 使用2表示16分音符量化
* 需求如此, 遍历每个小节, 除了上一小节出现过的随机保留一个note
