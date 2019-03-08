all:
	gcc -o lem_in1 find_way.c list_add.c reader1.c reader2.c reader3.c list2.c main.c list3.c -L. libft.a
	gcc -o visual list_add.c reader1.c reader2.c reader3.c read_ant.c list2.c vizual.c list3.c -L. libft.a -lmlx -framework OpenGL -framework Appkit
	gcc -o cheker chek.c list_add.c list2.c list3.c reader1.c reader2.c reader3.c -L. libft.a