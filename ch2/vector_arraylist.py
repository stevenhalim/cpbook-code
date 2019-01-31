def main():	
	arr = [7, 7, 7]							# Initial value [7, 7, 7]
	
	print("arr[2] = {}".format(arr[2]))		# 7

	for i in range(3):
		arr[i] = i;

	print("arr[2] = {}".format(arr[2]))		# 2

	# arr[5] = 5;	# index out of range error generated as index 5 does not exist
	# uncomment the line above to see the error

	arr.append(5)							# list will resize itself after appending
	print("arr[3] = {}".format(arr[3]))		# 5

main()