# Abstract
This is document about Eim editor.
Eim editor was maked by using gtkmm library in c++ language.

# eim editor
Express Inside Material Editor
like Vi IMproved

# 追加予定の機能
^n : 単語補完
^k : スニペット挿入
端末エミュレータ
シンタックスハイライト
コード折り畳み

# Requirement
use gtkmm.

# Usage
## Move mode
This mode is like normal mode in Vim.
You can go move mode by pressing ESC key in any mode.
Eim provide movement commands. For example h, j, k, l.
### movement commands.
- h and l
move left or right.
- j and k
move the top of previous line or next line.
- w
move the top of next word.
- b
move the top of previous word.

### edit command
- d
delete right character on cursor.
- x
delete left character on cursor.

## Edit mode
This mode is like insert mode in Vim.

## Command mode
This mode is like command mode in Vim.
You go this mode by pressing ^: key and you would return move key by
pressing ESC key or Enter key.
- q
quit the program.
- e filename
open the file.
- ^p or ^n
previous command history or next command history

# Install
make install

## Contribution

## License
MIT

## Author
Taichi Watanabe
