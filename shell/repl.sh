#!/bin/sh

echo command interpreter
while :
do
    echo -n "> "
    read x y z
    case $x in
        (dir) 
            echo list directory contents...
            ls $y
            ;;
        (cd) 
            echo changing directory
            ;;
        (help)
            echo commands:
            echo dir
            echo cd
            echo help
            echo quit
            ;;
        (quit) 
            break
            ;;
        (*)
            echo "I don't understand $s"
            ;;
    esac
done
