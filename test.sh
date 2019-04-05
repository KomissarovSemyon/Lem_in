# ARG=$(ls map | grep err)
# for map in $ARG
# do
# 	echo $map
# 	# cat map/$map | ./lem-in
# 	valgrind --leak-check=full ./lem-in map/$map 2>&1 | grep -E 'definitely|indirectly'
# done

echo err_3_coordinates.map
valgrind --leak-check=full ./lem-in map/err_3_coordinates.map 2>&1 | grep -E 'definitely|indirectly'
echo err_duplicate.map
valgrind --leak-check=full ./lem-in map/err_duplicate.map 2>&1 | grep -E 'definitely|indirectly'
echo err_empty.map
valgrind --leak-check=full ./lem-in map/err_empty.map 2>&1 | grep -E 'definitely|indirectly'
echo err_letter_in_coordinate.map
valgrind --leak-check=full ./lem-in map/err_letter_in_coordinate.map 2>&1 | grep -E 'definitely|indirectly'
echo err_link_to_unknown_room.map
valgrind --leak-check=full ./lem-in map/err_link_to_unknown_room.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_ants.map
valgrind --leak-check=full ./lem-in map/err_no_ants.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_ants2.map
valgrind --leak-check=full ./lem-in map/err_no_ants2.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_ants3.map
valgrind --leak-check=full ./lem-in map/err_no_ants3.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_end.map
valgrind --leak-check=full ./lem-in map/err_no_end.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_end2.map
valgrind --leak-check=full ./lem-in map/err_no_end2.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_links.map
valgrind --leak-check=full ./lem-in map/err_no_links.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_path.map
valgrind --leak-check=full ./lem-in map/err_no_path.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_rooms.map
valgrind --leak-check=full ./lem-in map/err_no_rooms.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_start.map
valgrind --leak-check=full ./lem-in map/err_no_start.map 2>&1 | grep -E 'definitely|indirectly'
echo err_no_start2.map
valgrind --leak-check=full ./lem-in map/err_no_start2.map 2>&1 | grep -E 'definitely|indirectly'
echo err_start_end_same.map
valgrind --leak-check=full ./lem-in map/err_start_end_same.map 2>&1 | grep -E 'definitely|indirectly'
echo err_start_end_same1.map
valgrind --leak-check=full ./lem-in map/err_start_end_same1.map 2>&1 | grep -E 'definitely|indirectly'
echo err_too_few_ants.map
valgrind --leak-check=full ./lem-in map/err_too_few_ants.map 2>&1 | grep -E 'definitely|indirectly'
echo err_too_intmax.map
valgrind --leak-check=full ./lem-in map/err_too_intmax.map 2>&1 | grep -E 'definitely|indirectly'
echo err_too_many_ants.map
valgrind --leak-check=full ./lem-in map/err_too_many_ants.map 2>&1 | grep -E 'definitely|indirectly'
echo err_two_end.map
valgrind --leak-check=full ./lem-in map/err_two_end.map 2>&1 | grep -E 'definitely|indirectly'
echo err_two_start.map
valgrind --leak-check=full ./lem-in map/err_two_start.map 2>&1 | grep -E 'definitely|indirectly'
echo 1.map
valgrind --leak-check=full ./lem-in map/1.map 2>&1 | grep -E 'definitely|indirectly'
echo 10.map
valgrind --leak-check=full ./lem-in map/10.map 2>&1 | grep -E 'definitely|indirectly'
echo 100K.map
valgrind --leak-check=full ./lem-in map/100K.map 2>&1 | grep -E 'definitely|indirectly'
echo 10K.map
valgrind --leak-check=full ./lem-in map/10K.map 2>&1 | grep -E 'definitely|indirectly'
echo 10_lots_of_comments.map
valgrind --leak-check=full ./lem-in map/10_lots_of_comments.map 2>&1 | grep -E 'definitely|indirectly'
echo 2.map
valgrind --leak-check=full ./lem-in map/2.map 2>&1 | grep -E 'definitely|indirectly'
echo 20.map
valgrind --leak-check=full ./lem-in map/20.map 2>&1 | grep -E 'definitely|indirectly'
echo 5.map
valgrind --leak-check=full ./lem-in map/5.map 2>&1 | grep -E 'definitely|indirectly'
echo 9_path_depth_10_ants.map
valgrind --leak-check=full ./lem-in map/9_path_depth_10_ants.map 2>&1 | grep -E 'definitely|indirectly'
echo 9_path_depth_1_ants.map
valgrind --leak-check=full ./lem-in map/9_path_depth_1_ants.map 2>&1 | grep -E 'definitely|indirectly'
echo 9_path_depth_2_ants.map
valgrind --leak-check=full ./lem-in map/9_path_depth_2_ants.map 2>&1 | grep -E 'definitely|indirectly'
echo 9_path_depth_4_ants.map
valgrind --leak-check=full ./lem-in map/9_path_depth_4_ants.map 2>&1 | grep -E 'definitely|indirectly'
echo 9_path_depth_8_ants.map
valgrind --leak-check=full ./lem-in map/9_path_depth_8_ants.map 2>&1 | grep -E 'definitely|indirectly'
echo 9_path_depth_9_ants.map
valgrind --leak-check=full ./lem-in map/9_path_depth_9_ants.map 2>&1 | grep -E 'definitely|indirectly'