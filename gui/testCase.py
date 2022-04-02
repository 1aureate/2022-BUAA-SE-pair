from itertools import permutations
options = ["-n", "-w", "-m", "-c", "-h", "-t", "-r", "word_list.txt"]
alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
try:
    while 1:
        # 生成所有位置的排列
        l = permutations(range(8))
        for x in l:
            for i in range(len(alphabet)):
                for j in range(len(alphabet)):
                    
except:
    pass

