Midifile
=======================================

类图
----
![Class organization](https://user-images.githubusercontent.com/3487289/39109564-493bca94-4682-11e8-87c4-991a931ca41b.png)

Midifile: midi文件对象, 表现为MidiEvents的二维数组: 第一个维度是轨道列表，第二个维度是 MidiEvents 列表

MidiEventList: 包含一个轨道上的MidiEvent

MidiEvent: 主要存储单元，包含一个(相对或者绝对)时间戳和一个表示midi数据的字节向量(或者标准midi元数据)

MidiMessage： MidiEvents 的基类, 表示MIDI消息(或者元数据)的无符号字节的 STL vector

Binasc: MidiFile 的一个帮助类, 允许以(表示二进制MIDI标准的)ASCII格式读取/写入 MIDI 文件

Option: 从终端读取参数的一个辅助类

Others
______

TPQ: Ticks per quarter note.

BPM: Beat per minute.

TPQ表示事件/音符的位置, BPM表示音符/事件的速度. TPQ是MidiFile属性, BPM是MidiEvent属性.
