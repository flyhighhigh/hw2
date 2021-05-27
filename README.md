## 吳昇程設（二）- 資料結構比較（作業）

### 支援的參數
- `-d N` （欲 **產生** 幾筆資料，N=`1e4`,`1e5`,`1e6`）
- `-q M` （欲 **查詢** 幾筆資料，M=`1e3`,`1e4`,`1e5`）
- `-arr` （測量 **陣列** 的建立和查詢時間）
- `-bs`  （測量 **陣列** 搭配 **Binary Search** 的建立和查詢時間）
- `-ll`  （測量 **Linked List** 的建立和查詢時間）
- `-bst` （測量 **Binary Search Tree** 的建立和查詢時間）
- `-hash`（測量 **Hash Table** 的建立和查詢時間）

### 範例

- 輸入：
```
make
./a.out -d 1e4 -q 1e3 -arr -bs -ll -bst -hash
```
- 輸出：
```
datacnt  10000
querycnt 1000
optcnt   5
create finish

ll:
building time = 0.000305 sec
query time = 0.020641 sec

arr:
building time = 0.000050 sec
query time = 0.018159 sec

bs:
building time = 0.001758 sec
query time = 0.000230 sec

bst:
building time = 0.003417 sec
query time = 0.000307 sec

hash:
building time = 0.000866 sec
query time = 0.000082 sec
```