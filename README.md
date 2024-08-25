# Announcement
* 如果有想要協作的學長姐學弟妹，請通過 issue 或 fork

# Advanced algorithm
* 104、110 期中檔案整理已完成
* 2021/12/01 更新 110 學年度高等演算法期中考
* 2021/12/02 新增 Exercise 3 hexagram chessboard cpp source code
* 2022/01/20 新增 110 學年度期末考

# Introduction of Artificial Intelligence
## Program 1
* RBFS algo referential code: https://github.com/NiloofarShahbaz/8-puzzle-search-implementation/blob/master/RBFS_search.py
* RBFS為參考毅翔的，要找時間改
* Astar算出來並不是最短路徑，要找一下bug
* IDS 目前算法僅保證不會走回父節點，但可能要改成不要走回 distance 較高的路徑，if current state distance < stored state distance, update visit[khash(state)] and run DFS

# Algorithm
* Visual Studio Community 會無法編譯成功，因為它認不得 Mingw 的 bits/stdc++.h，請將需要的小標頭檔自己 #include 進來（如 iostream, vector, iomanip, ...）





