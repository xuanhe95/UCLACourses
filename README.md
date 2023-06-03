# UCLACourses
UCLA Courses

Peach Party

该游戏由C++编写，模仿了Mario Party的玩法。是一个大富翁类的游戏。

面向对象编程结构：

- Actor  
  - Character  
    - Player  
    - Baddie
      - Bowser
      - Boo
    - Vortex
  - Sqaure
    - BlueCoinSquare
    - RedCoinSquare
    - StarSquare
    - DirectionalSquare
    - BankSquare
    - EventSquare
    - DroppingSquare
    
- CentralBank

---

# 📦 Actor
Actor类是游戏内所有物体的夫类。两个子类分别为Character和Sqaure，分别负责游戏内动态物体及静态物体。
- isOverlap(Actor\*) 方法用来检测两个Actor是否重叠。

## 🎭 Character
Character类负责游戏内所有移动的物体，包括Player，Baddie和Vortex
- 由于Character需要处理移动关系，因此有许多方法来设置Sprite方向，处理移动方向等。
- swap(Character& other) 方法用于交换两个Character的位置。
- randomTeleport() 方法将Character的位置更新到一个随机Sqaure上

### 🦸 Player

Player类作为玩家，包括Peach和Yoshi
- Player需要记录ID来分辨 👸 Peach和 🦕 Yoshi。
- Player需要记录并维护 🪙 金币与 🌟 星星。
- Player需要记录是否持有 🚀 Vortex。
- Player需要能投掷🎲骰子。

### 🦹 Baddie

Baddie类作为敌人，当与玩家接触时会发生交互效果。
- Baddie会随机在地图上移动。
- Baddie在接触到 🚀 Vortex后调用impacted()方法。Baddie会被随机传送，并暂停行动。
- SetPauseCounter()方法用来维护Baddie的暂停计时器。

#### 👹 Bowser
- 库霸王接触到玩家时，玩家会丢失所有的 🪙 金币与 🌟 星星。
- 库霸王会随机将其他Sqaure变成 🪤 DroppingSqaure。

#### 👻 Boo
- 嘘嘘鬼接触到玩家时将会🎲随机与另一名玩家交换 🪙 金币或 🌟 星星。

### 🚀 Vortex
Vortex类在与Baddie接触时会发生交互效果，将Baddie随机传送到地图上的Sqaure上，并暂停其行动。
- Vortex激活时将朝向玩家面向的方向运动。
- 当Vortex接触到其他Character时，使用isImpactable()方法检查是否可以被impact。
- 如果可以则调用Character的impact()方法，同时将Vortex的Alive状态设置为false。

## ◽️ Sqaure
Sqaure类负责游戏内所有静态的物体，每个Square与Player都有不同的行为。
- Character与Square的交互有*经过*（Passing Through）和*停留*（Landed On）两种交互状态，因此需要方法对不同交互状态进行检测。

### 🟦 BlueCoinSquare & RedCoinSqaure 🟥

- 当玩家与CoinSqaure交互时将增加或减少3枚 🪙 金币。

### 🌟 StarSqaure

- 当玩家与StarSqaure交互时，如果玩家有超过二十枚 🪙 金币，将兑换成一颗 🌟 星星。

### ⬅️ DirectionSqaure

- 当玩家与DirectionSqaure交互时，将改变玩家的方向。

### 🏦 BankSqaure

- 如果玩家*经过*BankSqaure，则存5枚 🪙 金币到CentralBank。
- 如果玩家*停留*在BankSqaure，则CentralBank的所有金币归玩家所有。

### ❗️ EventSqaure

当玩家*停留*在EventSqaure时，将会在三种事件中选择一种：
- 传送到🎲随机位置。
- 交换两个玩家的位置。
- 得到 🚀 Vortex。

### 🪤 DroppingSqaure

Bowser可以将其他Sqaure变成DroppingSqaure。
- 当玩家*停留*在DroppingSqaure时，将失去10枚 🪙 金币或 失去一枚 🌟 星星。

---

## 🌍 StudentWorld

在StudentWorld类里实现了游戏的其他程序部分。
- init()方法实现游戏对象的初始化。
- move()方法负责调用移动的Character，并清理掉Active为false的游戏对象。
- move()方法同样负责更新比分指示板的显示。


