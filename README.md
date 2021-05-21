# MakeNTU

## 組別資訊

2021_team07_吳限期支持明達增設烜炮澡堂

臺灣大學 電機三 吳沛林 b07901022
臺灣大學 電機三 李宇烜 b07901120
臺灣大學 電機三 謝明圜 b07901025

## 作品介紹

作品名稱：軌道異物入侵偵測系統
作品用途：軌道異物入侵偵測
DEMO影片連結：

### 運作方式

- 透過一對收發組偵測路徑上是否有異物入侵
- 嵌入式雙向溝通架構
  - 在此巧妙的架構下，對火車而言，只要左側的測站顯示異常，即表示前方數個側站有異物

### 如何實作

- 雷切快樂木工時間
- 偵測器快樂焊接時間
- 各種使用萬用貼土貼來貼去時間

### Dependencies / Requirements (用到哪些軟體、開發板、模組、工具...)

- 軟體
  - SparkFun_TB6612
- 開發板
  - STM32F103C8T6 - Blue Pill
  - Arduino Nano
- 模組及電料
  - 雷射模組
  - 光敏電阻
  - 馬達
  - 藍芽模組 HC-05
  - CP2105 - USB to TTL
  - LED燈
  - 電阻 - 150, 470 omega

## 工作分配

- 吳沛林
  - 組長，幫大家跑腿。
    - 編寫Demo小火車的程式
    - 及參與組裝、焊接、組裝
- 李宇烜
  - 設計Demo小火車外型
  - 雷切火車外殼及軌道
  - 焊接、組裝
- 謝明圜
  - 技術總監
  - 雷切火車外殼及軌道
  - 設計異物偵測支柱並編寫其中程式
  - 焊接、組裝
