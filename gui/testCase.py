from itertools import permutations
import subprocess

def exe_execution(command : str):
    print(command)
    pi = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    for i in iter(pi.stdout.readline, 'b'):
        print(i.decode('gbk'))
    # 执行exe 获取输出
    # 如果进行对拍，那么分别保存运行结果
    # 进行文件对比 如果有区别 记录区别并输出

    return

def dll_execution():

    # 执行ddl 获取返回值
    # 对比返回值

    return

options = ["-n", "-w", "-m", "-c", "-h", "-t", "-r", "word_list.txt"]
alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
TEST_TYPE = ".EXE" # ".DLL"


if __name__ == '__main__':
    try:
        if TEST_TYPE == ".EXE":
            while 1:
                # 生成所有位置的排列
                l = permutations(range(8))
                for x in l:
                    h = -1
                    t = -1
                    for k in range(len(x)):
                        if x[k] == 5: # -h
                            h = k
                        elif x[k] == 6: # -t
                            t = k
                    head = ""
                    tail = ""
                    for mask in range(2**8):
                        if mask & (1 << h) and mask & (1 << t):
                            for i in range(26): #
                                for j in range(26): #
                                    cmd : str = "pair.exe"
                                    for idx in range(len(x)):
                                        if idx == h:
                                            cmd += " " + str(x[idx]) + " " + alphabet[i]
                                        elif idx == t:
                                            cmd += " " + str(x[idx]) + " " + alphabet[j]
                                        elif mask & (1 << idx):
                                            cmd += " " + str(x[idx])
                                    exe_execution(cmd)
                        elif mask & (1 << h):
                            for i in range(26):
                                cmd: str = "pair.exe"
                                for idx in range(len(x)):
                                    if idx == h:
                                        cmd += " " + str(x[idx]) + " " + alphabet[i]
                                    elif mask & (1 << idx):
                                        cmd += " " + str(x[idx])
                                exe_execution(cmd)
                        elif mask & (1 << t):
                            for i in range(26):
                                cmd: str = "pair.exe"
                                for idx in range(len(x)):
                                    if idx == t:
                                        cmd += " " + str(x[idx]) + " " + alphabet[i]
                                    elif mask & (1 << idx):
                                        cmd += " " + str(x[idx])
                                exe_execution(cmd)
                        else:
                            cmd: str = "word_list.exe"
                            for idx in range(len(x)):
                                if mask & (1 << idx):
                                    cmd += " " + str(x[idx])
                            exe_execution(cmd)
        elif TEST_TYPE == ".DLL":
            ""
    except:
        print("unknown exception occurs")
        pass

