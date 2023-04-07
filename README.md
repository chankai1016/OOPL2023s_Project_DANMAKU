# Bullet Hell (DANMAKU/弾幕系シューティング)

## 111-2 (Spring 2023) OOPL

This is an Object-Oriented Programming Labs (OOPL) team project being held at NTUT for the Spring semester 2023.

これは、2023年春学期に国立台北科技大学において開講される開催されるオブジェクト指向プログラミング実習(OOPL)のチームプロジェクトです。

## Team Members

- 107590059 CHAN, Jiauei (Kai)
- 109590061 TAKAHASHI, Tomohiro

## Summary (概要)

**Bullet Hell (DANMAKU)** (ja: 弾幕系シューティング / zh: 彈幕射擊遊戲)

> DANMAKU is a **2D scrolling shooting game** in which the player can avoid a large number of slow-moving bullets that are fired by the enemy. It is also called a *barrage shooter*, *Bullet Curtain*, *Manic Shooter*, etc.
>
> 弾幕系シューティングとは、**2Dスクロールシューティングゲーム**の中で、「大量で低速な弾（弾幕）を敵が放ち、その間に生まれるわずかな隙間をぬって回避する事ができるほどプレイヤーの当たり判定が小さい」事を特徴とするシューティングゲームを指す。欧米ではBullet Hell、Bullet Curtain、Manic Shooter、DANMAKUなどと呼ばれている。

### Features and Key Points (特徴とポイント)

> First, "barrage" in shooting games refers to a state in which enemy attacks appear in such large numbers that they fill the screen, and derives from the analogy of a "curtain" with a large number of "bullets" flying around.
> 
> 第一にシューティングゲームにおける「弾幕」とは、敵の攻撃が画面を埋め尽くすほど大量に出現している状態のことを指し、大量の「弾」が飛び交う様子を「幕」に例えたことに由来する。

> DANMAKU is a shooting game in which the player can easily avoid a large number of bullets (barrage) in order to pursue the exhilaration of "avoiding" two of the main elements of a shooting game, "shooting" and "avoiding".
> 
> 弾幕系シューティングは、シューティングゲームの柱となる二つの要素「撃つ」と「避ける」のうち、「避ける」の爽快感を追求するため「大量の弾（弾幕）を容易に回避できる」というシステムを盛り込んだシューティングゲームである。

### Reference

[Video](https://youtube.com/watch?v=cPHxL1JaFv0&feature=share)

---

## Project Plan & Progress (計画と進度)

目前進度：**30%**

### 計劃

**粗體字**代表目前正在進行。

#### 介面

- [ ] 初始畫面
  - [ ] 選單
- [ ] 框
  - [X] 顯示
  - [ ] 顯示分數
- [ ] 背景
  - [X] 顯示
  - [ ] **讓背景移動**

#### 角色功能

- [X] 顯示
- [ ] 動畫
  - [X] 執行動畫（4個圖片切換）
  - [ ] **切換動畫（以方向切換3種（前/左/右））**
- [ ] 移動
  - [X] 長按連續
  - [X] +`shift`鍵慢速移動
  - [X] 移動範圍限制
  - [ ] *其他功能...*
- [ ] 射擊功能
  - [X] 控制
    - [X] 按`z`鍵從角色左右發射
  - [X] 移動：向前發射
  - [ ] 消失
    - [ ] **彈幕到範圍外即消失**
    - [ ] 碰到敵方即消失

#### 敵方功能

- [ ] **顯示**
- [ ] 移動
- [ ] 動畫
  - [ ] 執行動畫
  - [ ] 切換動畫
- [ ] 射擊
  - [ ] 控制
  - [ ] 移動
  - [ ] 消失
    - [ ] 彈幕到範圍外即消失
    - [ ] 碰到角色即消失

#### 遊戲關卡

- [ ] 第一關
- [ ] 第二關
- [ ] 第三關

---

## 1st Demo Key Points (第1回中間デモ要点/第1次其中demo要點)

1. 目前做到哪一個進度點？
   - 介面
     - 框：顯示
     - 背景：顯示
   - 角色功能
     - 顯示
     - 動畫：執行動畫（4個圖片切換）
     - 移動
       - 長按連續
       - +`shift`鍵慢速移動
       - 移動範圍限制
     - 射擊功能
       - 控制：按`z`鍵從角色左右發射發射
       - 移動：向前發射

2. 目前正在進行哪一個工作點？
   
   目前射擊後的彈幕尚未處理（彈幕到範圍外即消失 或 碰到敵方即消失），且彈幕上限暫設爲`500`，爲減少電腦負擔，之後可能需實現「當彈幕`my_shot[n]`設爲消失狀態後，該`my_shot[n]`重新利用」。
   
    其他：

   - 介面
     - 初始畫面
     - 選單
     - 框：顯示分數等資訊
     - 背景：讓背景移動
   - 角色功能
     - 顯示
     - 動畫：切換動畫（以方向切換3種（前/左/右））
     - 射擊功能
       - 消失
         - 彈幕到範圍外即消失
         - 碰到敵方即消失
   - 敵方功能

3. 距離你預期遊戲完成的施工比例？

    30%

