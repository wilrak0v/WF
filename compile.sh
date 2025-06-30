gcc -Os -s -o trans transformeur.c
gcc -Os -s -o "exec" exe.c
strip "exec"
strip trans
[ -n "$2" ] && ./"trans"
[ -n "$1" ] && ./"exec"